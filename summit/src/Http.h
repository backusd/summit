#pragma once
#include "Core.h"





namespace summit
{
enum class Protocol
{
	TCP,
	UDP
};

class Socket
{
public:
	enum class Type
	{
		STREAM = 1,
		DGRAM = 2,
		RAW = 3,
		RDM = 4,
		SEQPACKET = 5
	};
	Socket(Socket::Type type, Protocol protocol);
	~Socket();


#ifdef SUMMIT_PLATFORM_WINDOWS
	ND inline SOCKET Get() const noexcept { return m_socket; }
#elif defined SUMMIT_PLATFORM_LINUX
	inline void Get() const noexcept {}
#endif

private:
	// No use case yet for these
	Socket(const Socket&) = delete;
	Socket(Socket&&) = delete;
	Socket& operator=(const Socket&) = delete;
	Socket& operator=(Socket&&) = delete;
	

#ifdef SUMMIT_PLATFORM_WINDOWS
	SOCKET m_socket = 0;
#endif
};

class Http
{
public:
	ND static inline std::string Get(std::string_view url) { return Instance().GetImpl(url); }

private:
	static inline Http& Instance()
	{
		static Http http{};
		return http;
	}
	Http();
	Http(const Http&) = delete;
	Http(Http&&) = delete;
	Http& operator=(const Http&) = delete;
	Http& operator=(Http&&) = delete;
	~Http();


	ND std::string GetImpl(std::string_view url) const;
};
}


template <>
struct std::formatter<summit::Socket::Type> : std::formatter<std::string> {
	auto format(summit::Socket::Type type, format_context& ctx) const
	{
		std::string s;
		switch (type)
		{
		case summit::Socket::Type::STREAM:      s = "STREAM"; break;
		case summit::Socket::Type::DGRAM:       s = "DGRAM"; break;
		case summit::Socket::Type::RAW:         s = "RAW"; break;
		case summit::Socket::Type::RDM:         s = "RDM"; break;
		case summit::Socket::Type::SEQPACKET:   s = "SEQPACKET"; break;
		default:
			s = "(Unknown)"; 
			break;
		}

		return formatter<string>::format(s, ctx);
	}
};

template <>
struct std::formatter<summit::Protocol> : std::formatter<std::string> {
	auto format(summit::Protocol proto, format_context& ctx) const
	{
		std::string s;
		switch (proto)
		{
		case summit::Protocol::TCP: s = "TCP"; break;
		case summit::Protocol::UDP: s = "UDP"; break;
		default:
			s = "(Unknown)";
			break;
		}

		return formatter<string>::format(s, ctx);
	}
};