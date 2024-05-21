#include "YuriTea/Core/log.hpp"
#include "spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <fcntl.h>

namespace YuriTea {
std::shared_ptr<spdlog::logger> Log::s_CoreLogger =
    std::shared_ptr<spdlog::logger>(nullptr);

std::shared_ptr<spdlog::logger> Log::s_ClientLogger =
    std::shared_ptr<spdlog::logger>(nullptr);

void Log::Init() {

  spdlog::info("Log System Initialing");
  SetConsoleOutputCP(CP_UTF8);
  _setmode(_fileno(stdout), _O_U8TEXT);

  spdlog::set_pattern(
      "%^[%T] %n: %v%$"); // 设置日志格式 分别是 时间 logger名字 日志内容
  s_CoreLogger = spdlog::stdout_color_mt("YURITEA");
  s_CoreLogger->set_level(spdlog::level::trace);

  s_ClientLogger = spdlog::stdout_color_mt("APP");
  s_ClientLogger->set_level(spdlog::level::trace);

  // log to console
  YT_CORE_TRACE("Log System Initialized");
}
} // namespace YuriTea
