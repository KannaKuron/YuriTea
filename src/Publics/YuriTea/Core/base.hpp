#pragma once

#include "YuriTea/Core/basicstruct.hpp" 

#ifdef YuriTea_Platform_Windows
  #ifdef  YuriTea_BUILD_DLL
    #define YURITEA_API __declspec(dllexport)
  #else 
    #define YURITEA_API __declspec(dllimport)
  #endif 
#else 
  //linux or other platform
  //#error YuriTea only supports Windows!
  #ifdef  YuriTea_BUILD_DLL
    #define YURITEA_API 
  #else 
    #define YURITEA_API 
  #endif 
#endif // YuriTea_Platform_Windows





#define BIT(x) (1 << x) // Bitwise shift operator
#define YT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) // 只能绑定使用了这个宏的类的方法



#ifdef YuriTea_ENABLE_ASSERTS
#define YT_ASSERT(x, ...) { if(!(x)) { YT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define YT_CORE_ASSERT(x, ...) { if(!(x)) { YT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define YT_ASSERT(x, ...)
#define YT_CORE_ASSERT(x, ...)
#endif

template<typename T>
const char* __ToBits(const T& x){
  int32 size = sizeof(x) *8;
  char buf[size+1];
  for (int i = 0 ;i < size; i++){
    buf[i] = x & BIT(i) ? '1' : '0';
  }
  buf[size] = '\0';
  return buf;
}

#define YT_TOBITS(x) __ToBits(x)
