#pragma once
#include "YuriTea/Core/window.hpp"
#include <spdlog/spdlog.h>

namespace YuriTea {

class YURITEA_API Application {
public:
  Application();          // 构造函数
  virtual ~Application(); // 析构函数

  void Run();

private:
  Scope<Window> m_Window;
  bool m_Running = true;
};

// To be defined in CLIENT
Application *CreateApplication();

} // namespace YuriTea
