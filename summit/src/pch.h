#ifndef SUMMIT_PCH
#define SUMMIT_PCH


#include <algorithm> 
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <concepts>
#include <deque>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iterator>
#include <iostream>
#include <memory>
#include <numbers>
#include <optional>

// Can't use until we are on clang 18 (currently on 17)
//#include <print>

#include <queue>
#include <source_location>
#include <span>
#include <stack>
#include <stacktrace>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>



#ifdef SUMMIT_PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
// #define NONLS			// --> Causes build to fail - undeclared identifier
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#define NOMINMAX

#define STRICT

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#endif // TOPO_PLATFORM_WINDOWS


#endif // SUMMIT_PCH
