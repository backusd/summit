#pragma once
#include "Core.h"


// For Windows, see: https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences

namespace summit
{
class Logger
{
public:
	template<typename... T>
	static void CoreTrace(std::string_view msg, T... args) noexcept { Get().CoreTraceImpl(msg, std::forward<T>(args)...); }
	template<typename... T>
	static void CoreInfo(std::string_view msg, T... args) noexcept { Get().CoreInfoImpl(msg, std::forward<T>(args)...); }
	template<typename... T>
	static void CoreWarn(std::string_view msg, T... args) noexcept { Get().CoreWarnImpl(msg, std::forward<T>(args)...); }
	template<typename... T>
	static void CoreError(std::string_view msg, T... args) noexcept { Get().CoreErrorImpl(msg, std::forward<T>(args)...); }

	template<typename... T>
	static void Trace(std::string_view msg, T... args) noexcept { Get().TraceImpl(msg, std::forward<T>(args)...); }
	template<typename... T>
	static void Info(std::string_view msg, T... args) noexcept { Get().InfoImpl(msg, std::forward<T>(args)...); }
	template<typename... T>
	static void Warn(std::string_view msg, T... args) noexcept { Get().WarnImpl(msg, std::forward<T>(args)...); }
	template<typename... T>
	static void Error(std::string_view msg, T... args) noexcept { Get().ErrorImpl(msg, std::forward<T>(args)...); }
		

private:
	static inline Logger& Get()
	{
		static Logger am{};
		return am;
	}
	Logger() noexcept;
	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger& operator=(Logger&&) = delete;

	static ND std::string CurrentTimeAndDate() noexcept;

	template<typename... T>
	void CoreTraceImpl(std::string_view msg, T... args) noexcept
	{
		if constexpr (sizeof...(T) == 0)
			std::println("\x1b[37m[TRACE {0}] CORE - {1}", CurrentTimeAndDate(), msg);
		else
		{
			std::print("\x1b[37m[TRACE {0}] CORE - ", CurrentTimeAndDate());
			std::vprint_nonunicode(std::cout, msg, std::make_format_args(std::forward<T>(args)...));
			std::println("");
		}
	}
	template<typename... T>
	void CoreInfoImpl(std::string_view msg, T... args) noexcept
	{
		if constexpr (sizeof...(T) == 0)
			std::println("\x1b[32m[INFO {0}] CORE - {1}", CurrentTimeAndDate(), msg);
		else
		{
			std::print("\x1b[32m[INFO {0}] CORE - ", CurrentTimeAndDate());
			std::vprint_nonunicode(std::cout, msg, std::make_format_args(std::forward<T>(args)...));
			std::println("");
		}
	}
	template<typename... T>
	void CoreWarnImpl(std::string_view msg, T... args) noexcept
	{
		if constexpr (sizeof...(T) == 0)
			std::println("\x1b[33m[WARN {0}] CORE - {1}", CurrentTimeAndDate(), msg);
		else
		{
			std::print("\x1b[33m[WARN {0}] CORE - ", CurrentTimeAndDate());
			std::vprint_nonunicode(std::cout, msg, std::make_format_args(std::forward<T>(args)...));
			std::println("");
		}
	}
	template<typename... T>
	void CoreErrorImpl(std::string_view msg, T... args) noexcept
	{
		if constexpr (sizeof...(T) == 0)
			std::println("\x1b[31m[ERROR {0}] CORE - {1}", CurrentTimeAndDate(), msg);
		else
		{
			std::print("\x1b[31m[ERROR {0}] CORE - ", CurrentTimeAndDate());
			std::vprint_nonunicode(std::cout, msg, std::make_format_args(std::forward<T>(args)...));
			std::println("");
		}
	}

	template<typename... T>
	void TraceImpl(std::string_view msg, T... args) noexcept
	{
		if constexpr (sizeof...(T) == 0)
			std::println("\x1b[37m[TRACE {0}] {1}", CurrentTimeAndDate(), msg);
		else
		{
			std::print("\x1b[37m[TRACE {0}] ", CurrentTimeAndDate());
			std::vprint_nonunicode(std::cout, msg, std::make_format_args(std::forward<T>(args)...));
			std::println("");
		}
	}
	template<typename... T>
	void InfoImpl(std::string_view msg, T... args) noexcept
	{
		if constexpr (sizeof...(T) == 0)
			std::println("\x1b[32m[INFO {0}] {1}", CurrentTimeAndDate(), msg);
		else
		{
			std::print("\x1b[32m[INFO {0}] ", CurrentTimeAndDate());
			std::vprint_nonunicode(std::cout, msg, std::make_format_args(std::forward<T>(args)...));
			std::println("");
		}
	}
	template<typename... T>
	void WarnImpl(std::string_view msg, T... args) noexcept
	{
		if constexpr (sizeof...(T) == 0)
			std::println("\x1b[33m[WARN {0}] {1}", CurrentTimeAndDate(), msg);
		else
		{
			std::print("\x1b[33m[WARN {0}] ", CurrentTimeAndDate());
			std::vprint_nonunicode(std::cout, msg, std::make_format_args(std::forward<T>(args)...));
			std::println("");
		}
	}
	template<typename... T>
	void ErrorImpl(std::string_view msg, T... args) noexcept
	{
		if constexpr (sizeof...(T) == 0)
			std::println("\x1b[31m[ERROR {0}] {1}", CurrentTimeAndDate(), msg);
		else
		{
			std::print("\x1b[31m[ERROR {0}] ", CurrentTimeAndDate());
			std::vprint_nonunicode(std::cout, msg, std::make_format_args(std::forward<T>(args)...));
			std::println("");
		}
	}
};

}	// namespace summit

// Disable logging for distribution builds
#ifdef SUMMIT_DIST 

#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)

#elif SUMMIT_CORE // If building the core library, use CORE logging

#define LOG_TRACE(...) ::summit::Logger::CoreTrace(__VA_ARGS__)
#define LOG_INFO(...) ::summit::Logger::CoreInfo(__VA_ARGS__)
#define LOG_WARN(...) ::summit::Logger::CoreWarn(__VA_ARGS__)
#define LOG_ERROR(...) ::summit::Logger::CoreError(__VA_ARGS__)

#else // If building the client application, use basic logging

#define LOG_TRACE(...) ::summit::Logger::Trace(__VA_ARGS__)
#define LOG_INFO(...) ::summit::Logger::Info(__VA_ARGS__)
#define LOG_WARN(...) ::summit::Logger::Warn(__VA_ARGS__)
#define LOG_ERROR(...) ::summit::Logger::Error(__VA_ARGS__)

#endif
