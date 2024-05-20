#include "YuriTea/Core/application.hpp"
#include "YuriTea/Core/core.hpp"

namespace YuriTea {

Application::Application() {
  // 构造函数实现
  WindowProps props;
  m_Window = Window::Create(props);
}

Application::~Application() {
  // 析构函数实现
}

void Application::Run() {
  YT_INFO("Application Running");
  while (m_Running) {
    // 一直循环
    m_Window->OnUpdate();
  }
}

Application *CreateApplication() { return new Application(); }
} // namespace YuriTea
