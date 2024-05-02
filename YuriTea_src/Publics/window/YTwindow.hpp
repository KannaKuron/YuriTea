#ifndef YTWINDOW_HPP
#define YTWINDOW_HPP

#define EXPORT_DLL __declspec(dllexport)

#include "basic/basic.hpp"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <memory>
#include <rttr/registration_friend.h>

class EXPORT_DLL YTWindow final {
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

#endif // YTWINDOW_HPP
