#include "YuriTea/Platform/Windows/windowsWindow.hpp"
#include "YuriTea/Core/keyCodes.hpp"
#include "YuriTea/Events/applicationEvent.hpp"
#include "YuriTea/Events/keyEvent.hpp"
#include "YuriTea/Events/mouseEvent.hpp"
#include "YuriTea/Core/core.hpp"

namespace YuriTea {

void WindowsWindow::OnUpdate() {

  SDL_PumpEvents(); // 更新事件
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(m_Window);

}

void WindowsWindow::SetEventFilters(){
  // 设置关闭窗口事件
  SDL_SetEventFilter([](void * data_t,SDL_Event* event)->int{
    auto callBack = static_cast<WindowData*>(data_t)->EventCallback;
    switch (event->type) {
      case SDL_QUIT: {
        WindowCloseEvent e;
        callBack(e);
        return 0;
      }
      case SDL_APP_TERMINATING :{
        AppTerminateEvent e;
        callBack(e);
        return 0;
      }

      // * Keyboard Events * //
      case SDL_KEYDOWN :{
        //  KeyPressedEvent(KeyCode code, KeyMod mod, uint32 repeatCount)
        KeyPressedEvent e(static_cast<KeyCode>(event->key.keysym.sym),
                          static_cast<KeyMod>(event->key.keysym.mod),
                          event->key.repeat);
        callBack(e);
        return 0;
      }
      case SDL_KEYUP :{
        KeyReleasedEvent e(static_cast<KeyCode>(event->key.keysym.sym),
                      static_cast<KeyMod>(event->key.keysym.mod));
        callBack(e);
        return 0;
      }

      // * Mouse Events * //
      case SDL_MOUSEMOTION :{
        //  MouseMovedEvent(Vector2<float32> position, Vector2<float32> lastPosition,uint32 timeStamp, uint32 state, uint32 keyMod)
        // 这时候的键盘状态
        auto mod = SDL_GetModState();
        MouseMovedEvent e(event->motion.x, event->motion.y,
                          event->motion.xrel, event->motion.yrel,
                          event->motion.timestamp,
                          event->motion.state,
                          static_cast<KeyMod>(mod));
        callBack(e);
        return 0;
      }
      case SDL_MOUSEBUTTONDOWN :{
        //  MouseButtonPressedEvent(MouseCode button, KeyMod modifiers, uint32 repeatCount, float32 x, float32 y, uint32 timeStamp)
        auto mod = SDL_GetModState();
        MouseButtonPressedEvent e(static_cast<MouseCode>(event->button.button),
                            static_cast<KeyMod>(mod),
                            event->button.clicks,
                            static_cast<float32>(event->button.x), static_cast<float32>(event->button.y),
                            event->button.timestamp);
        callBack(e);
        return 0;
      }
      case SDL_MOUSEBUTTONUP :{
        //  MouseButtonReleasedEvent(MouseCode button, KeyMod modifiers, float32 x, float32 y, uint32 timeStamp)
        auto mod = SDL_GetModState();
        MouseButtonReleasedEvent e(static_cast<MouseCode>(event->button.button),
                      static_cast<KeyMod>(mod),
                      static_cast<float32>(event->button.x), static_cast<float32>(event->button.y),
                      event->button.timestamp);
        callBack(e);
        return 0;
      }
      case SDL_MOUSEWHEEL :{
        //MouseScrolledEvent(float32 positionX, float32 positionY, float32 offsetX, float32 offsetY, uint32 timeStamp, KeyMod modifiers)
        auto mod = SDL_GetModState();
        MouseScrolledEvent e(static_cast<float32>(event->wheel.mouseX),static_cast<float32>( event->wheel.mouseY),
                            static_cast<float32>(event->wheel.x),static_cast<float32>(event->wheel.y),
                            event->wheel.timestamp, static_cast<KeyMod>(mod));
        callBack(e);
        return 0;
      }

      // * Window Events * //
      case SDL_WINDOWEVENT: {
        switch (event->window.event) {
          case SDL_WINDOWEVENT_RESIZED: { // 窗口大小改变
            WindowResizeEvent e(Vector2<uint32>{static_cast<uint32>(event->window.data1), static_cast<uint32>(event->window.data2)});
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_MOVED : { // 窗口移动
            WindowMovedEvent e(Vector2<uint32>{static_cast<uint32>(event->window.data1), static_cast<uint32>(event->window.data2)});
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_FOCUS_LOST: { // 窗口失去焦点
            WindowFocusEvent e;
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_FOCUS_GAINED: { // 窗口获得焦点
            WindowLostFocusEvent e;
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_CLOSE: { // 窗口关闭
            WindowCloseEvent e;
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_SHOWN: {  // 窗口显示
            WindowShowEvent e;
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_HIDDEN: { // 窗口隐藏
            WindowHideEvent e;
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_MAXIMIZED: { // 窗口最大化
            WindowMaximizedEvent e;
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_MINIMIZED: { // 窗口最小化
            WindowMinimizedEvent e;
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_ENTER: { // 鼠标窗口进入
            WindowEnterEvent e;
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_LEAVE: { // 鼠标窗口离开
            WindowLeaveEvent e;
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_EXPOSED: { // 窗口暴露
            WindowExposedEvent e;
            callBack(e);
            return 0;
          }
          case SDL_WINDOWEVENT_RESTORED: { // 窗口恢复
            WindowRestoredEvent e;
            callBack(e);
            return 0;
          }
          default: {
            UnKnownEvent e;
            callBack(e);
            YT_CORE_WARN("未知窗口事件{0}", event->window.event);
            return 0;
          }
        }
        break;
    }
    // * Text Input * //
    case SDL_TEXTINPUT: {
      TextInputEvent e(event->text.text);
      callBack(e);
      return 0;
    }
    case SDL_TEXTEDITING: {
      TextEditingEvent e(event->edit.text, event->edit.start, event->edit.length);
      callBack(e);
      return 0;
    }
    case SDL_CLIPBOARDUPDATE: {
      ClipboardChangedEvent e;
      callBack(e);
      return 0;
    }
    default: {
      UnKnownEvent e;
      YT_CORE_WARN("未知事件{0}", event->type);
      callBack(e);
      return 0;
    }
  }
  return 0;}, &m_Data );
}

#define DontUseEventWatch

void WindowsWindow::SetEventWatchs(){
  #ifndef DontUseEventWatch
  SDL_AddEventWatch([](void * data_t,SDL_Event* event)->int{
    auto callBack = static_cast<WindowData*>(data_t)->EventCallback;




    return 0; // 返回值会被忽略
  }, &m_Data );
#endif
}




WindowsWindow::WindowsWindow(const WindowProps &props) { 
  Init(props); 
  auto resl = gladLoadGLLoader(SDL_GL_GetProcAddress);
  if (!resl) {
    YT_CORE_ERROR("Glad加载失败");
    YT_CORE_ASSERT(false, "Glad加载失败");
  }
}

WindowsWindow::~WindowsWindow() {
  // 析构函数实现
  Shutdown();
  m_Context = nullptr;
  m_Window = nullptr;

}

void WindowsWindow::Init(const WindowProps &props) {
  // 初始化函数实现
  m_Data.Title = props.Title;
  m_Data.WindowSize = props.Size;
  m_Data.VSync = false;
  m_Data.Fullscreen = false;
  m_Data.CursorVisible = true;

  YT_CORE_INFO("创建窗口 {0} ({1}, {2})", m_Data.Title, m_Data.WindowSize.x,
               m_Data.WindowSize.y);

  // 初始化SDL 全部子系统
  if (!s_SDLInitialized) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      YT_CORE_ERROR("SDL初始化失败: {0}", SDL_GetError());
      YT_CORE_ASSERT(false, "SDL初始化失败");
      return;
    }
    s_SDLInitialized = true;
    YT_CORE_INFO("SDL初始化成功");
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);



  m_Window = SDL_CreateWindow(m_Data.Title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, m_Data.WindowSize.x,
                              m_Data.WindowSize.y,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                                  SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
  if (m_Window == nullptr) {
    YT_CORE_ERROR("SDL窗口创建失败: {0}", SDL_GetError());
    SDL_Quit();
    YT_CORE_ASSERT(false, "SDL窗口创建失败");

    return;
  } else {
    YT_CORE_INFO("SDL窗口创建成功");
  }

  SDL_SetWindowData(m_Window, "YuRiTea-Main-Window", &m_Data);

  m_Context = SDL_GL_CreateContext(m_Window);

  if (m_Context == nullptr) {
    YT_CORE_ERROR("OpenGL上下文创建失败: {0}", SDL_GetError());
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
    YT_CORE_ASSERT(false, "OpenGL上下文创建失败");
    return;
  } else {
    YT_CORE_INFO("OpenGL上下文创建成功");
  }

  // 设置事件回调函数
  SetEventFilters();
  SetEventWatchs();

  SetFullscreen(m_Data.Fullscreen);
  SetCursorVisible(m_Data.CursorVisible);
  SetVSync(m_Data.VSync);
}




void WindowsWindow::Shutdown() {
  // 关闭函数实现
  YT_CORE_INFO("关闭窗口 {0} ({1}, {2})", m_Data.Title, m_Data.WindowSize.x,
               m_Data.WindowSize.y);

  SDL_GL_DeleteContext(m_Context);
  SDL_DestroyWindow(m_Window);
  SDL_Quit();
}

void WindowsWindow::SetVSync(bool enabled) {
  // 垂直同步函数实现
  m_Data.VSync = enabled;
  if (m_Data.VSync) {
    SDL_GL_SetSwapInterval(1);
  } else {
    SDL_GL_SetSwapInterval(0);
  }
}

bool WindowsWindow::IsVSync() const { return m_Data.VSync; }

void WindowsWindow::SetFullscreen(bool enabled) {
  // 全屏函数实现
  m_Data.Fullscreen = enabled;
  if (m_Data.Fullscreen) {
    SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
  } else {
    SDL_SetWindowFullscreen(m_Window, 0);
  }
}

bool WindowsWindow::IsFullscreen() const { return m_Data.Fullscreen; }

void WindowsWindow::SetSize(const Vector2<uint32> &size) {
  m_Data.WindowSize = size;
  SDL_SetWindowSize(m_Window, m_Data.WindowSize.x, m_Data.WindowSize.y);
}

void WindowsWindow::SetSize(const uint32 &width, const uint32 &height) {
  m_Data.WindowSize = {width, height};
  SDL_SetWindowSize(m_Window, m_Data.WindowSize.x, m_Data.WindowSize.y);
}

void WindowsWindow::SetTitle(const std::string &title) {
  m_Data.Title = title;
  SDL_SetWindowTitle(m_Window, m_Data.Title.c_str());
}

void WindowsWindow::SetCursorVisible(bool visible) {
  m_Data.CursorVisible = visible;
  if (m_Data.CursorVisible) {
    SDL_ShowCursor(SDL_ENABLE);
  } else {
    SDL_ShowCursor(SDL_DISABLE);
  }
}

bool WindowsWindow::IsCursorVisible() const { return m_Data.CursorVisible; }

} // namespace YuriTea
