#pragma once
#include "YuriTea/Core/core.hpp"

namespace YuriTea {

class YURITEA_API Log {
public:
  ~Log() = default;
  static void Init(); // 初始化

  inline static spdlog::logger &GetCoreLogger() {
    return *s_CoreLogger;
  }
  inline static spdlog::logger &GetClientLogger() {
    return *s_ClientLogger;
  }

  void Flush_Core(){s_CoreLogger->flush();}
  void Flush_Client(){s_ClientLogger->flush();}

private:
  Log() = default;

  static Ref<spdlog::logger> s_CoreLogger;
  static Ref<spdlog::logger> s_ClientLogger;

};

} // namespace YuriTea

#ifdef YuriTea_DEBUG
#define YT_CORE_TRACE(...) ::YuriTea::Log::GetCoreLogger().trace(__VA_ARGS__)
#define YT_CORE_INFO(...) ::YuriTea::Log::GetCoreLogger().info(__VA_ARGS__)
#define YT_CORE_WARN(...) ::YuriTea::Log::GetCoreLogger().warn(__VA_ARGS__)
#define YT_CORE_ERROR(...) ::YuriTea::Log::GetCoreLogger().error(__VA_ARGS__)

#define YT_TRACE(...) ::YuriTea::Log::GetClientLogger().trace(__VA_ARGS__)
#define YT_INFO(...) ::YuriTea::Log::GetClientLogger().info(__VA_ARGS__)
#define YT_WARN(...) ::YuriTea::Log::GetClientLogger().warn(__VA_ARGS__)
#define YT_ERROR(...) ::YuriTea::Log::GetClientLogger().error(__VA_ARGS__)
#define YT_TRACE(...) ::YuriTea::Log::GetClientLogger().trace(__VA_ARGS__)

#define YT_CORE_FLUSH() ::YuriTea::Log::GetCoreLogger().flush()
#define YT_FLUSH() ::YuriTea::Log::GetClientLogger().flush()

#else
#define YT_CORE_TRACE(...)
#define YT_CORE_INFO(...)
#define YT_CORE_WARN(...)
#define YT_CORE_ERROR(...)
#define YT_TRACE(...)
#define YT_INFO(...)
#define YT_WARN(...)
#define YT_ERROR(...)
#define YT_CORE_FLUSH() 
#define YT_FLUSH() 

#endif
