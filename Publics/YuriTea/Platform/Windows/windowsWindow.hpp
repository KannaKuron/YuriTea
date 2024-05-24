#pragma once
#include "YuriTea/Core/window.hpp"
#include <sdl2/SDL.h>

namespace YuriTea {
static bool s_SDLInitialized = false;

class YURITEA_API WindowsWindow : public Window {
  public:
  struct WindowData {
    std::string Title;
    Vector2<uint32> WindowSize;
    bool VSync; // 垂直同步
    bool Fullscreen; // 全屏
    bool CursorVisible; // 鼠标可见
    EventCallbackFn EventCallback; // 事件回调函数
    
  };

public:
  WindowsWindow(const WindowProps &props);
  ~WindowsWindow();                        // 析构函数

  virtual void OnUpdate() override;

  virtual const uint32 &GetWidth() const override { return m_Data.WindowSize.x; }
  virtual const uint32 &GetHeight() const override { return m_Data.WindowSize.y; }
  virtual const Vector2<uint32> &GetSize() const override { return m_Data.WindowSize; }
  

  // Window attributes
  virtual void SetEventCallback(const EventCallbackFn &callback) override{ m_Data.EventCallback = callback; }
  virtual void SetVSync(bool enabled) override;
  virtual bool IsVSync() const override;
  virtual void SetFullscreen(bool enabled) override;
  virtual bool IsFullscreen() const override;
  virtual void SetSize(const Vector2<uint32> &size) override;
  virtual void SetSize(const uint32 &width, const uint32 &height) override;
  virtual void SetTitle(const std::string &title) override;
  virtual void SetCursorVisible(bool visible) override;
  virtual bool IsCursorVisible() const override;

  virtual void *GetNativeWindow() const override { return m_Window; }

private:
  void Init(const WindowProps &props);
  void Shutdown();
  void SetEventFilters();
  void SetEventWatchs();

private:
  SDL_Window *m_Window; // SDL窗口
  SDL_GLContext m_Context; // OpenGL上下文
  WindowData m_Data;
};

} // namespace YuriTea
