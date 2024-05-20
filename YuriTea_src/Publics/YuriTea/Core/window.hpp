#pragma once
#include "YuriTea/Events/event.hpp"

namespace YuriTea {

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
  using EventCallbackFn = std::function<void(Event &)>;
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

  virtual void *GetNativeWindow() const = 0;

  static Scope<Window> Create(const WindowProps &props = WindowProps());
};

} // namespace YuriTea
