#pragma once
#include "Core.h"





namespace summit
{
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

#ifdef SUMMIT_PLATFORM_WINDOWS
	void PrintAddrInfoDetails(addrinfo* addrInfo) const noexcept;
#endif
};
}