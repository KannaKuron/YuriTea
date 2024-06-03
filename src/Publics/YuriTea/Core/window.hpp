#pragma once
#include "YuriTea/Core/core.hpp"
#include "YuriTea/Events/event.hpp"

namespace YuriTea {
using EventCallbackFn = std::function<void(Event &)>;
struct WindowData {
  // 利用一个uint8来记录图形api类型 vulkan 还是 opengl
  uint8 GraphicsAPI;
  uint32 APIVersion;
  std::string Title;
  Vector2<uint32> WindowSize;
  bool VSync; // 垂直同步
  bool Fullscreen; // 全屏
  bool CursorVisible; // 鼠标可见
  bool WindowResizeable; // 窗口可调整大小
  EventCallbackFn EventCallback; // 事件回调函数
    
  };

struct WindowProps {
  std::string Title;
  Vector2<uint32> Size;

  WindowProps(const std::string &title = "YuriTea Engine", uint32 width = 1280,
              uint32 height = 720)
      : Title(title), Size(width, height) {}
};

// interface representing a desktop system based Window
class YURITEA_API Window {
public:
  Window() = default;
  virtual ~Window() = default;

  virtual void OnUpdate() = 0;

  virtual const uint32 &GetWidth() const = 0;
  virtual const uint32 &GetHeight() const = 0;
  virtual const Vector2<uint32> &GetSize() const = 0;

  // Window attributes
  virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
  virtual void SetVSync(bool enabled) = 0;
  virtual bool IsVSync() const = 0;
  virtual void SetFullscreen(bool enabled) = 0;
  virtual bool IsFullscreen() const = 0;
  virtual void SetSize(const Vector2<uint32> &size) = 0;
  virtual void SetSize(const uint32 &width, const uint32 &height) = 0;
  virtual void SetTitle(const std::string &title) = 0;
  virtual void SetCursorVisible(bool visible) = 0;
  virtual bool IsCursorVisible() const = 0;
  virtual void SetWindowResizeable(bool resizeable) = 0;
  virtual bool IsWindowResizeable() const = 0;
  

  virtual void *GetNativeWindow() const = 0;
  virtual void *GetNativeContext() const = 0;
  virtual void *GetNativeData() const = 0;

  static Scope<Window> Create(const WindowProps &props = WindowProps());
};

} // namespace YuriTea
