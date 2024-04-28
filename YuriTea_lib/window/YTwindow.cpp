#include "basicStructs.hpp"
#include <YTwindow.hpp>
#include <memory>

std::unique_ptr<YTWindow> YTWindow::_instance = nullptr;
Vector2D<int> YTWindow::_windowSize = {1000, 800};

void YTWindow::InitWindow() {
  if (_instance == nullptr)
    _instance.reset(new YTWindow());
}

void YTWindow::QuitWindow() { _instance.reset(nullptr); }

void YTWindow::Start(int argc, char *argv[]) {}
