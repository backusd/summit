#pragma once
#include "Core.h"
#include "SummitException.h"


namespace summit
{
struct HttpResponse
{
	unsigned int ResponseCode;
	std::string Body;
};

class Http
{
public:
	ND static inline HttpResponse Get(const std::string& url) { return Instance().GetImpl(url); }

private:
	static inline Http& Instance()
	{
		static Http http{};
		return http;
	}

	ND HttpResponse GetImpl(const std::string& url) const;


};


} // namespace summit