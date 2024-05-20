#include "YuriTea/Core/application.hpp"
#include "YuriTea/Core/core.hpp"

namespace YuriTea {

Application::Application() {
  // 构造函数实现
}

Application::~Application() {
  // 析构函数实现
}

void Application::Run() {
  while (true) {
    // 一直循环
    YT_INFO("Application Running");
    YT_ERROR("Application Running Error");
  }
}

} // namespace YuriTea
