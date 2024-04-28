#pragma once

#include "basic.hpp"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <memory>

class YTWindow final {
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
