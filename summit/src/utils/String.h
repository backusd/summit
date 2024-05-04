#pragma once
#include "../Core.h"

namespace summit
{
ND std::wstring s2ws(const std::string& str) noexcept;
ND std::wstring s2ws(std::string_view str) noexcept;
ND std::string ws2s(const std::wstring& wstr) noexcept;
ND bool ends_with(std::string_view str, std::string_view suffix) noexcept;
}