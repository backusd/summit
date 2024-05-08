#include "pch.h"
#include "Http.h"
#include "Logger.h"
#include "utils/String.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>


namespace summit
{
HttpResponse Http::GetImpl(const std::string& url) const
{
	HttpResponse hr{};

	std::string headers;
	auto HeaderCallback = [&headers](char* ptr, size_t size, size_t nmemb)
		{
			int totalSize = static_cast<int>(size * nmemb);
			headers += std::string(ptr, totalSize);
			return totalSize;
		};

	// Request to be sent.
	curlpp::Easy request{};

	// Set the URL.
	request.setOpt<curlpp::options::Url>(url);

	// Set a callback so we can store the response headers in a separate string
	// than the response body
	request.setOpt(curlpp::options::HeaderFunction(HeaderCallback));

	// Send request and get a result. Put the result in an ostringstream
	std::ostringstream os;
	curlpp::options::WriteStream ws(&os);
	request.setOpt(ws);
	request.perform();

	hr.ResponseCode = curlpp::infos::ResponseCode::get(request);
	
	// 308 - Permanent redirect
	if (hr.ResponseCode == 308)
	{
		std::string redirectUrl;

		size_t location = headers.find("\nLocation:");
		if (location == std::string::npos)
			throw EXCEPTION(std::format("Received return code 308 (Permanent Redirect) but no redirect location for URL: {0}", url));

		location = headers.find_first_not_of(" \t", location + 10);
		if (location == std::string::npos)
			throw EXCEPTION(std::format("Received return code 308 (Permanent Redirect) and saw 'Location:' in header but the value could not be parsed for URL: {0}", url));

		size_t last = headers.find_first_of("\r\n", location);
		if (last == std::string::npos)
			redirectUrl = headers.substr(location, headers.size() - location);
		else
			redirectUrl = headers.substr(location, last - location);

		if (redirectUrl.compare(url) == 0)
			throw EXCEPTION(std::format("Received return code 308 (Permanent Redirect) but redirect URL was the exact same - URL: {0}", url));

		LOG_WARN("Received 308 (Permanent Redirect) for URL: {0}", url);
		LOG_WARN("    Redirecting to: {0}", redirectUrl);

		hr = GetImpl(redirectUrl);
	}
	else
	{
		hr.Body = os.str();
	}

	return hr;
}

}