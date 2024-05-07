#include "pch.h"
#include "Logger.h"
#include "SummitException.h"
#include "Http.h"


#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <Windows.h>

void work()
{
//	LOG_TRACE("World");
//	LOG_TRACE("Eat some {0}", 69);
//	LOG_INFO("Info {0} {1}", 69, "no thanks");
//	LOG_WARN("Warn {0}", true);
//	LOG_ERROR("Error - you suck");
//
//	LOG_TRACE("Eat some {0}", 69);
//	LOG_INFO("Info {0} {1}", 69, "no thanks");
//	LOG_WARN("Warn {0}", true);
//	LOG_ERROR("Error - you suck");

	LOG_TRACE("You suck!");
	LOG_TRACE("Hi there {0}", 123);

	//std::string url = "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/2023-01-09/2023-01-09?adjusted=true&sort=asc&limit=120&apiKey=pOxlGL_Bie97aO1B9C3lcNF9tyMgbc0D";
	////std::string url = "";
	////std::string url = "https://example.com/";
	//summit::HttpResponse response = summit::Http::Get(url);
	//LOG_INFO("Website:\nStatus: {0}\nBody: {1}", response.StatusCode, response.Body);
	//LOG_INFO("URL:  {0}", url);

	// That's all that is needed to do cleanup of used resources (RAII style).
	curlpp::Cleanup myCleanup;

	// Our request to be sent.
	curlpp::Easy myRequest{};

	// Set the URL.
	myRequest.setOpt<curlpp::options::Url>("http://example.com");

	// Send request and get a result.
	// By default the result goes to standard output.
	myRequest.perform();
}



int main(int argc, char** argv)
{
	try
	{
		work();
	}
	catch (curlpp::RuntimeError& e)
	{
		LOG_ERROR("Caught curlpp::RuntimeError: {}", e.what());
	}
	catch (curlpp::LogicError& e)
	{
		LOG_ERROR("Caught curlpp::LogicError: {}", e.what());
	}
	catch (const summit::SummitExceptionWithData<int>& e)
	{
		LOG_ERROR("Caught SummitException: {}", e);
	}
	catch (const summit::SummitException& e)
	{
		LOG_ERROR("Caught SummitException: {}", e);
	}
	catch (const std::exception& e)
	{
		LOG_ERROR("Caught exception: {}", e.what());
	}
	catch (...)
	{
		LOG_ERROR("Caught unknown exception");
	}

	return 0;
}