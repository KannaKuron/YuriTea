#include "YuriTea/Core/window.hpp"

#ifdef YuriTea_Platform_Windows
#include "YuriTea/Platform/Windows/windowsWindow.hpp"
#endif

namespace YuriTea {

Scope<Window> Window::Create(const WindowProps &props) {
#ifdef YuriTea_Platform_Windows
  return CreateScope<WindowsWindow>(std::move(props));
#else
  YT_CORE_ERROR("Unknown platform!");
#error Unknown platform!
#endif

  return nullptr;
}

} // namespace YuriTea
