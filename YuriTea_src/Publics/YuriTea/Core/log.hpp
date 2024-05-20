#pragma once
#include "YuriTea/Core/core.hpp"
#include "spdlog/spdlog.h"
#include <memory>

namespace YuriTea {

class YURITEA_API Log {
public:
  ~Log() = default;
  static void Init(); // 初始化

  inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
    return s_CoreLogger;
  }
  inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
    return s_ClientLogger;
  }

private:
  Log() = default;

  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

} // namespace YuriTea

#define YT_CORE_TRACE(...) ::YuriTea::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define YT_CORE_INFO(...) ::YuriTea::Log::GetCoreLogger()->info(__VA_ARGS__)
#define YT_CORE_WARN(...) ::YuriTea::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define YT_CORE_ERROR(...) ::YuriTea::Log::GetCoreLogger()->error(__VA_ARGS__)

#define YT_TRACE(...) ::YuriTea::Log::GetClientLogger()->trace(__VA_ARGS__)
#define YT_INFO(...) ::YuriTea::Log::GetClientLogger()->info(__VA_ARGS__)
#define YT_WARN(...) ::YuriTea::Log::GetClientLogger()->warn(__VA_ARGS__)
#define YT_ERROR(...) ::YuriTea::Log::GetClientLogger()->error(__VA_ARGS__)
