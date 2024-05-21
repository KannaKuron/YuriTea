#pragma once
#include "YuriTea/Core/basicstruct.hpp"

#ifdef YuriTea_Platform_Windows
#ifdef YuriTea_DLL
#define YURITEA_API __declspec(dllexport)
#else // YuriTea_DLL
#define YURITEA_API __declspec(dllimport)
#endif // YuriTea_DLL
#else // YuriTea_Platform_Windows
#error YuriTea only supports Windows!
#endif // YuriTea_Platform_Windows



#define BIT(x) (1 << x) // Bitwise shift operator
#define YT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)



#ifdef YuriTea_ENABLE_ASSERTS
#define YT_ASSERT(x, ...) { if(!(x)) { YT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define YT_CORE_ASSERT(x, ...) { if(!(x)) { YT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define YT_ASSERT(x, ...)
#define YT_CORE_ASSERT(x, ...)
#endif
