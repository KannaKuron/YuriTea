#include <iostream>
#include <window/window.hpp>

#ifdef _WIN32
#define MAIN wmain
#else
#define MAIN main
#endif

int MAIN() {
  // 加载动态链接库

  YTWindow::InitWindow();

  YTWindow::GetYTWindow();
  std::cout << "Hello, YuriTea!";

  YTWindow::QuitWindow();

  return 0;
}
