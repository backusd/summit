#include "pch.h"
#include "Logger.h"
#include "SummitException.h"
#include "Http.h"
#include "PolygonAPI.h"

#include <curlpp/Exception.hpp>

#include <json.hpp>
using json = nlohmann::json;

void work()
{
//	std::string url = "https://api.polygon.io/v2/aggs/ticker/AAPL/range/1/day/2023-01-09/2023-01-09?adjusted=true&sort=asc&limit=120&apiKey=pOxlGL_Bie97aO1B9C3lcNF9tyMgbc0D";
//	//std::string url = "https://example.com/";
//	summit::HttpResponse response = summit::Http::Get(url);
//	LOG_INFO("URL:  {0}", url);
//	LOG_INFO("Response: {0} - {1}", response.ResponseCode, response.Body);
//
//	auto j = json::parse(response.Body.c_str());
//	LOG_TRACE("JSON:\n{0}", j.dump(4));

	summit::TickerType tt1("CS");
	summit::TickerType tt2("CS");
	LOG_INFO("Ticker Type 1: {0}", tt1);
	LOG_INFO("Ticker Type 2: {0}", tt2);
	LOG_INFO("Equality1    : {0}", tt1 == tt2);
	LOG_INFO("Equality2    : {0}", tt1 == "CS");
	LOG_INFO("Equality3    : {0}", summit::TickerType::ADRC == summit::TickerType::CS);
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