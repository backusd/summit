#pragma once
#include "Core.h"
#include "SummitException.h"




//namespace summit
//{
//enum class Protocol
//{
//	TCP,
//	UDP
//};
//
//
//
//struct HttpRequest
//{
//	enum class RequestType { GET, POST, PUT };
//	enum class HttpVersion { HTTP_1_1 };
//	enum class ConnectionType { KEEP_ALIVE, CLOSE };
//
//	HttpRequest(std::string_view url, RequestType type = RequestType::GET, ConnectionType connection = ConnectionType::CLOSE, HttpVersion version = HttpVersion::HTTP_1_1);
//	HttpRequest(const HttpRequest&) = default;
//	HttpRequest(HttpRequest&&) = default;
//	HttpRequest& operator=(const HttpRequest&) = default;
//	HttpRequest& operator=(HttpRequest&&) = default;
//
//	ND inline std::string Get() const noexcept
//	{
//		return std::format(
//			"{0} {1} {2}\r\n"
//			"Connection: {3}\r\n"
//			"Host: {4}\r\n"
//			"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36\r\n"
//			"\r\n",
//			Type, Target, Version,
//			Connection,
//			Host
//		);
//	}
//
//	RequestType Type;
//	std::string Target;
//	HttpVersion Version;
//	ConnectionType Connection;
//	std::string Host;
//	std::string HttpStr;
//};
//
//struct HttpResponse
//{
//	unsigned int StatusCode;
//	std::string Body;
//};
//
//class Socket
//{
//public:
//	enum class Type
//	{
//		STREAM = 1,
//		DGRAM = 2,
//		RAW = 3,
//		RDM = 4,
//		SEQPACKET = 5
//	};
//	Socket(Socket::Type type, Protocol protocol);
//	~Socket();
//
//	void SendRequest(const HttpRequest& request) const;
//
//#ifdef SUMMIT_PLATFORM_WINDOWS
//	ND inline SOCKET Get() const noexcept { return m_socket; }
//#elif defined SUMMIT_PLATFORM_LINUX
//	inline void Get() const noexcept {}
//#endif
//
//private:
//	// No use case yet for these
//	Socket(const Socket&) = delete;
//	Socket(Socket&&) = delete;
//	Socket& operator=(const Socket&) = delete;
//	Socket& operator=(Socket&&) = delete;
//
//
//#ifdef SUMMIT_PLATFORM_WINDOWS
//	SOCKET m_socket = 0;
//#endif
//};
//
//class Http
//{
//public:
//	ND static inline HttpResponse Get(std::string_view url) { return Instance().GetImpl(url); }
//
//private:
//	static inline Http& Instance()
//	{
//		static Http http{};
//		return http;
//	}
//	Http();
//	Http(const Http&) = delete;
//	Http(Http&&) = delete;
//	Http& operator=(const Http&) = delete;
//	Http& operator=(Http&&) = delete;
//	~Http();
//
//
//	ND HttpResponse GetImpl(std::string_view url) const;
//
//
//};
//}
//
//
//template <>
//struct std::formatter<summit::Socket::Type> : std::formatter<std::string> {
//	auto format(summit::Socket::Type type, format_context& ctx) const
//	{
//		std::string s;
//		switch (type)
//		{
//		case summit::Socket::Type::STREAM:      s = "STREAM"; break;
//		case summit::Socket::Type::DGRAM:       s = "DGRAM"; break;
//		case summit::Socket::Type::RAW:         s = "RAW"; break;
//		case summit::Socket::Type::RDM:         s = "RDM"; break;
//		case summit::Socket::Type::SEQPACKET:   s = "SEQPACKET"; break;
//		default:
//			s = "(Unknown)"; 
//			break;
//		}
//
//		return formatter<string>::format(s, ctx);
//	}
//};
//
//template <>
//struct std::formatter<summit::Protocol> : std::formatter<std::string> {
//	auto format(summit::Protocol proto, format_context& ctx) const
//	{
//		std::string s;
//		switch (proto)
//		{
//		case summit::Protocol::TCP: s = "TCP"; break;
//		case summit::Protocol::UDP: s = "UDP"; break;
//		default:
//			s = "(Unknown)";
//			break;
//		}
//
//		return formatter<string>::format(s, ctx);
//	}
//};
//
//template <>
//struct std::formatter<summit::HttpRequest> : std::formatter<std::string> {
//	auto format(summit::HttpRequest req, format_context& ctx) const
//	{
//		return formatter<string>::format(req.Get(), ctx);
//	}
//};
//template <>
//struct std::formatter<summit::HttpRequest::RequestType> : std::formatter<std::string> {
//	auto format(summit::HttpRequest::RequestType type, format_context& ctx) const
//	{
//		std::string s;
//		switch (type)
//		{
//		case summit::HttpRequest::RequestType::GET:		s = "GET"; break;
//		case summit::HttpRequest::RequestType::POST:	s = "POST"; break;
//		case summit::HttpRequest::RequestType::PUT:		s = "PUT"; break;
//		default:
//			throw EXCEPTION("Uknown HttpRequest Type");
//		}
//
//		return formatter<string>::format(s, ctx);
//	}
//};
//template <>
//struct std::formatter<summit::HttpRequest::HttpVersion> : std::formatter<std::string> {
//	auto format(summit::HttpRequest::HttpVersion version, format_context& ctx) const
//	{
//		std::string s;
//		switch (version)
//		{
//		case summit::HttpRequest::HttpVersion::HTTP_1_1: s = "HTTP/1.1"; break;
//		default:
//			throw EXCEPTION("Uknown HttpVersion");
//		}
//
//		return formatter<string>::format(s, ctx);
//	}
//};
//template <>
//struct std::formatter<summit::HttpRequest::ConnectionType> : std::formatter<std::string> {
//	auto format(summit::HttpRequest::ConnectionType type, format_context& ctx) const
//	{
//		std::string s;
//		switch (type)
//		{
//		case summit::HttpRequest::ConnectionType::KEEP_ALIVE: s = "keep-alive"; break;
//		case summit::HttpRequest::ConnectionType::CLOSE: s = "close"; break;
//		default:
//			throw EXCEPTION("Uknown HttpVersion");
//		}
//
//		return formatter<string>::format(s, ctx);
//	}
//};