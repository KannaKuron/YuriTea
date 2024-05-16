#pragma once
#include "YuriTea/Core/Core.hpp"
#include <spdlog/spdlog.h>

namespace YuriTea {

class YURITEA_API Application {
public:
  Application();          // 构造函数
  virtual ~Application(); // 析构函数

  void Run();
};

// To be defined in CLIENT
Application *CreateApplication();

} // namespace YuriTea
