#include "YTwindow.hpp"
#include <glad/glad.h>
#include <iostream>

int main(int argc, char **argv) {
  YTWindow::InitWindow();

  YTWindow::GetYTWindow().Start(argc, argv);

  YTWindow::QuitWindow();
  return 0;
}
