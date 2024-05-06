#include "pch.h"
#include "Http.h"
#include "Logger.h"
#include "SummitException.h"
#include "utils/String.h"


namespace summit
{
#ifdef SUMMIT_PLATFORM_WINDOWS
void PrintAddrInfoDetails(addrinfo* addrInfo) noexcept
{
    LOG_INFO("\tFlags: {0}", addrInfo->ai_flags);
    switch (addrInfo->ai_family)
    {
    case AF_UNSPEC:
        LOG_INFO("\tFamily: Unspecified");
        break;
    case AF_INET:
    {
        struct sockaddr_in* sockaddr_ipv4 = (struct sockaddr_in*)addrInfo->ai_addr;
        LOG_INFO("\tFamily: AF_INET (IPv4)");
        LOG_INFO("\tIPv4 address {0}", inet_ntoa(sockaddr_ipv4->sin_addr));
        break;
    }
    case AF_INET6:
    {
        LPSOCKADDR sockaddr_ip;
        wchar_t ipstringbuffer[46];
        DWORD ipbufferlength = 46;

        LOG_INFO("\tFamily: AF_INET6 (IPv6)");
        // the InetNtop function is available on Windows Vista and later
        // sockaddr_ipv6 = (struct sockaddr_in6 *) addrInfo->ai_addr;
        // LOG_INFO("\tIPv6 address %s",
        //    InetNtop(AF_INET6, &sockaddr_ipv6->sin6_addr, ipstringbuffer, 46) );

        // We use WSAAddressToString since it is supported on Windows XP and later
        sockaddr_ip = (LPSOCKADDR)addrInfo->ai_addr;
        // The buffer length is changed by each call to WSAAddresstoString
        // So we need to set it for each iteration through the loop for safety
        ipbufferlength = 46;
        int iRetval = WSAAddressToString(sockaddr_ip, (DWORD)addrInfo->ai_addrlen, NULL, ipstringbuffer, &ipbufferlength);
        if (iRetval)
            LOG_ERROR("\tWSAAddressToString failed with {0}", WSAGetLastError());
        else
        {
            std::wstring ipsb(ipstringbuffer);
            LOG_INFO("\tIPv6 address {0}", ws2s(ipsb));
        }
        break;
    }
    case AF_NETBIOS:
        LOG_INFO("\tFamily: AF_NETBIOS (NetBIOS)");
        break;
    default:
        LOG_INFO("\tFamily: Other {0}", addrInfo->ai_family);
        break;
    }

    switch (addrInfo->ai_socktype)
    {
    case 0:
        LOG_INFO("\tSocket type: Unspecified");
        break;
    case SOCK_STREAM:
        LOG_INFO("\tSocket type: SOCK_STREAM (stream)");
        break;
    case SOCK_DGRAM:
        LOG_INFO("\tSocket type: SOCK_DGRAM (datagram) ");
        break;
    case SOCK_RAW:
        LOG_INFO("\tSocket type: SOCK_RAW (raw) ");
        break;
    case SOCK_RDM:
        LOG_INFO("\tSocket type: SOCK_RDM (reliable message datagram)");
        break;
    case SOCK_SEQPACKET:
        LOG_INFO("\tSocket type: SOCK_SEQPACKET (pseudo-stream packet)");
        break;
    default:
        LOG_INFO("\tSocket type: Other {0}", addrInfo->ai_socktype);
        break;
    }

    switch (addrInfo->ai_protocol)
    {
    case 0:
        LOG_INFO("\tProtocol: Unspecified");
        break;
    case IPPROTO_TCP:
        LOG_INFO("\tProtocol: IPPROTO_TCP (TCP)");
        break;
    case IPPROTO_UDP:
        LOG_INFO("\tProtocol: IPPROTO_UDP (UDP) ");
        break;
    default:
        LOG_INFO("\tProtocol: Other {0}", addrInfo->ai_protocol);
        break;
    }
    LOG_INFO("\tLength of this sockaddr: {0}", addrInfo->ai_addrlen);
    LOG_INFO("\tCanonical name: {0}", addrInfo->ai_canonname);
}
#endif

// ==========================================================================================
// Socket
Socket::Socket(Socket::Type type, Protocol protocol) :
    m_socket{}
{
#ifdef SUMMIT_PLATFORM_WINDOWS
    int _af = AF_INET;
    int _type, _protocol;

    switch (type)
    {
    case Socket::Type::STREAM:      _type = SOCK_STREAM; break;
    case Socket::Type::DGRAM:       _type = SOCK_DGRAM; break;
    case Socket::Type::RAW:         _type = SOCK_RAW; break;
    case Socket::Type::RDM:         _type = SOCK_RDM; break;
    case Socket::Type::SEQPACKET:   _type = SOCK_SEQPACKET; break;
    default:
        throw EXCEPTION(std::format("Uknown socket type: {0}", type));
    }

    switch (protocol)
    {
    case Protocol::TCP: _protocol = IPPROTO_TCP; break;
    case Protocol::UDP: _protocol = IPPROTO_UDP; break;
    default:
        throw EXCEPTION(std::format("Uknown protocol type: {0}", type));
    }

    m_socket = socket(_af, _type, _protocol);
#endif
}

Socket::~Socket()
{
#ifdef SUMMIT_PLATFORM_WINDOWS
    closesocket(m_socket);
#endif
}

// ==========================================================================================
// Http
Http::Http()
{
#ifdef SUMMIT_PLATFORM_WINDOWS
	WSADATA wsaData = {};
    int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (err != 0)
        throw EXCEPTION(std::format("WSAStartup failed with error: {0}", err));

    // Confirm that the WinSock DLL supports 2.2.
    // Note that if the DLL supports versions greater   
    // than 2.2 in addition to 2.2, it will still return
    // 2.2 in wVersion since that is the version we     
    // requested.                                       
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) 
    {
        // Could not find a usable WinSock DLL.     
        WSACleanup();
        throw EXCEPTION("Could not find a usable version of Winsock.dll");
    }
#endif
}
Http::~Http()
{
#ifdef SUMMIT_PLATFORM_WINDOWS
    WSACleanup();
#endif
}

std::string Http::GetImpl(std::string_view url) const
{
    std::string result;
    result.reserve(10000);

    std::string prefix(url.substr(0, 7));
    if (prefix.compare("http://") != 0)
        throw EXCEPTION(std::format("Invalid URL '{0}' - Must start with 'http://'", url));

    size_t dotcomOffset = url.find(".com") + 4;
    std::string host(url.substr(7, dotcomOffset - 7)); // Do not include 'http://' in the host name
    std::string_view path = (url.size() == dotcomOffset) ? "/" : url.substr(dotcomOffset, url.size());
    std::string request = std::format(
        "GET {0} HTTP/1.1\r\n"
        "Connection: close\r\n"
        "Host: {1}\r\n"
        "\r\n",
        path, host);

    LOG_INFO("Request: {0}", request);

#ifdef SUMMIT_PLATFORM_WINDOWS
    //--------------------------------
    // Setup the hints address info structure
    // which is passed to the getaddrinfo() function
    struct addrinfo hints; 
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    //--------------------------------
    // Call getaddrinfo(). If the call succeeds,
    // the result variable will hold a linked list
    // of addrinfo structures containing response
    // information
    struct addrinfo* addrInfo = NULL;
    DWORD dwRetval = getaddrinfo(host.c_str(), "http", &hints, &addrInfo);  
    if (dwRetval != 0)
        throw EXCEPTION(std::format("getaddrinfo failed for URL '{0}' with error: {1}", url, dwRetval));

    struct addrinfo* ptr = NULL;
    sockaddr* sockaddr_ipv4 = nullptr;
    for (ptr = addrInfo; ptr != NULL; ptr = ptr->ai_next) 
    {
        if (ptr->ai_flags != 0)
        {
            LOG_WARN("getaddrinfo returned unexpected response with a non-zero flags value ({0})", ptr->ai_flags);
            LOG_WARN("Dumping all addrinfo details:");
            PrintAddrInfoDetails(ptr);
        }

        switch (ptr->ai_family) 
        {
        case AF_INET:
            sockaddr_ipv4 = ptr->ai_addr;
            break;

        default:
            LOG_WARN("getaddrinfo returned response with unexpected AI_FAMILY value");
            LOG_WARN("Dumping all addrinfo details:"); 
            PrintAddrInfoDetails(ptr);
            break;
        }

        switch (ptr->ai_socktype) 
        {
        case SOCK_STREAM:
            break;

        default:
            LOG_WARN("getaddrinfo returned response with unexpected AI_SOCKTYPE value");
            LOG_WARN("Dumping all addrinfo details:");
            PrintAddrInfoDetails(ptr);
            break;
        }

        switch (ptr->ai_protocol) 
        {
        case IPPROTO_TCP:
            break;

        default:
            LOG_WARN("getaddrinfo returned response with unexpected AI_PROTOCOL value");
            LOG_WARN("Dumping all addrinfo details:");
            PrintAddrInfoDetails(ptr);
            break;
        }
    }

    Socket sock(Socket::Type::STREAM, Protocol::TCP);
    if (connect(sock.Get(), sockaddr_ipv4, sizeof(sockaddr_in)) != 0)
        throw EXCEPTION(std::format("Failed to connect to: {0}.\r\nWSAGetLastError: {1}", url, WSAGetLastError()));

    size_t sent = 0;
    int remaining = static_cast<int>(request.size());
    while (remaining > 0)
    {
        const char* data = request.c_str() + sent;
        auto result = send(sock.Get(), data, remaining, 0);
        if (result == SOCKET_ERROR)
            throw EXCEPTION(std::format("Failed to send all data to: {0}.\r\nWSAGetLastError: {1}", url, WSAGetLastError()));
        sent += result;
        remaining -= result;
    }

    char buffer[10000];

    int nDataLength;
    while ((nDataLength = recv(sock.Get(), buffer, 10000, 0)) > 0)
    {
        // TODO: There has to be a better method here than push_back
        for (int iii = 0; iii < nDataLength; ++iii)
            result.push_back(buffer[iii]);
    }

    // NOTE: We are throwing exceptions above and not calling these functions - implement RAII
    freeaddrinfo(addrInfo);

#endif
    return result;
}


}