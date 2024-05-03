#pragma once

#ifdef _WIN32
#ifdef YuriTea_DLL
#define YuriTea_DLL_API __declspec(dllexport)
#else
#define YuriTea_DLL_API __declspec(dllimport)
#endif
#endif

#include "basic/basic.hpp"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <memory>
#include <rttr/registration_friend.h>

class YuriTea_DLL_API YTWindow final {
public:
  static void InitWindow();
  static void QuitWindow();

  static YTWindow &GetYTWindow() { return *_instance; }

  void Start(int argc, char *argv[]);

  ~YTWindow() = default;

private:
  YTWindow() = default;

  static std::unique_ptr<YTWindow> _instance;
  static Vector2D<int> _windowSize;
};
