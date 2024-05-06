#include "pch.h"
#include "Logger.h"
#include "SummitException.h"
#include "Http.h"




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

	std::string website = summit::Http::Get("http://www.example.com");
	LOG_INFO("Website: {0}", website);

}



int main(int argc, char** argv)
{
	try
	{
		work();
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