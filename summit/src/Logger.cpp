#include "pch.h"
#include "Logger.h"

namespace summit
{
	Logger::Logger() noexcept
	{
//#ifdef SUMMIT_PLATFORM_WINDOWS
//		// Set output mode to handle virtual terminal sequences
//		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//		if (hOut == INVALID_HANDLE_VALUE)
//		{
//			return;// GetLastError();
//		}
//
//		DWORD dwMode = 0;
//		if (!GetConsoleMode(hOut, &dwMode))
//		{
//			return;// GetLastError();
//		}
//
//		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
//		if (!SetConsoleMode(hOut, dwMode))
//		{
//			return;// GetLastError();
//		}
//#endif
	}


	std::string Logger::CurrentTimeAndDate() noexcept
	{
		try
		{
			auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
			return std::format("{:%X}", time);
		}
		catch (const std::runtime_error& e)
		{
			return std::format("Caught runtime error: {}", e.what());
		}
		catch (const std::exception& e)
		{
			return std::format("Caught exception: {}", e.what());
		}
		catch (...)
		{
			return "Caught unknown exception";
		}

		return "ERROR";
	}
}