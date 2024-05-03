#pragma once

#ifdef _WIN32
#ifdef YuriTea_DLL
#define YuriTea_DLL_API __declspec(dllexport)
#else
#define YuriTea_DLL_API __declspec(dllimport)
#endif
#endif

template <typename T> struct YuriTea_DLL_API Vector2D {
  T w;
  T h;
};
