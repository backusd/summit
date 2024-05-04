#pragma once
#include "Core.h"
#include "utils/Concepts.h"

#define EXCEPTION(message) ::summit::SummitException(message)
#define EXCEPTION_WITH_DATA(message, data) ::summit::SummitExceptionWithData(message, data)

namespace summit
{
class SummitException
{
public:
    SummitException(const std::string& errorMessage, const std::source_location& loc = std::source_location::current(), std::stacktrace trace = std::stacktrace::current()) :
        m_errorMessage(errorMessage),
        m_location{ loc },
        m_stacktrace{ trace }
    {}
    SummitException(std::string&& errorMessage, const std::source_location& loc = std::source_location::current(), std::stacktrace trace = std::stacktrace::current()) :
        m_errorMessage(std::move(errorMessage)),
        m_location{ loc },
        m_stacktrace{ trace }
    {}

    std::string& what() { return m_errorMessage; }
    const std::string& what() const noexcept { return m_errorMessage; }
    const std::source_location& where() const { return m_location; }
    const std::stacktrace& stack() const { return m_stacktrace; }

protected:
    std::string m_errorMessage;
    const std::source_location m_location;
    const std::stacktrace m_stacktrace;
};


template<HasFormatterSpecialization DATA_T>
class SummitExceptionWithData : public SummitException
{
public:
    SummitExceptionWithData(const std::string& errorMessage, const DATA_T& data, const std::source_location& loc = std::source_location::current(), std::stacktrace trace = std::stacktrace::current()) :
        SummitException(errorMessage, loc, trace),
        m_data(data)
    {}
    SummitExceptionWithData(const std::string& errorMessage, DATA_T&& data, const std::source_location& loc = std::source_location::current(), std::stacktrace trace = std::stacktrace::current()) :
        SummitException(errorMessage, loc, trace),
        m_data(data)
    {}
    SummitExceptionWithData(std::string&& errorMessage, const DATA_T& data, const std::source_location& loc = std::source_location::current(), std::stacktrace trace = std::stacktrace::current()) :
        SummitException(errorMessage, loc, trace),
        m_data(std::move(data))
    {}
    SummitExceptionWithData(std::string&& errorMessage, DATA_T&& data, const std::source_location& loc = std::source_location::current(), std::stacktrace trace = std::stacktrace::current()) :
        SummitException(errorMessage, loc, trace),
        m_data(std::move(data))
    {}

    DATA_T& data() { return m_data; }
    const DATA_T& data() const noexcept { return m_data; }
    std::string dataAsString() const noexcept { return std::format("{0}", m_data); }

private:
    DATA_T m_data;
};

}

template <>
struct std::formatter<summit::SummitException> : std::formatter<std::string> {
auto format(summit::SummitException e, format_context& ctx) const
{
    auto& location = e.where();

    std::string s = std::format("SummitException:\n\nWHAT: {0}\n", e.what());
    s += std::format("WHERE: {0}({1}:{2}), `function` {3}\nSTACK TRACE:\n", location.file_name(), location.line(), location.column(), location.function_name());
    for (auto iter = e.stack().begin(); iter != (e.stack().end() - 3); ++iter)
        s += std::format("\t{0}({1}) : {2}\n", iter->source_file(), iter->source_line(), iter->description());

    return formatter<string>::format(s, ctx);
}
};

template <typename T>
struct std::formatter<summit::SummitExceptionWithData<T>> : std::formatter<std::string> {
    auto format(summit::SummitExceptionWithData<T> e, format_context& ctx) const
    {
        auto& location = e.where();

        std::string s = std::format("SummitExceptionWithData:\n\nWHAT: {0}\n", e.what());
        s += std::format("DATA: {0}\n", e.dataAsString());
        s += std::format("WHERE: {0}({1}:{2}), `function` {3}\nSTACK TRACE:\n", location.file_name(), location.line(), location.column(), location.function_name());
        for (auto iter = e.stack().begin(); iter != (e.stack().end() - 3); ++iter)
            s += std::format("\t{0}({1}) : {2}\n", iter->source_file(), iter->source_line(), iter->description());

        return formatter<string>::format(s, ctx);
    }
};