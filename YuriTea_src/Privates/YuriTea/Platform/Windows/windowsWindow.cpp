#include "YuriTea/Core/core.hpp"
#include "YuriTea/Platform/Windows/windowsWindow.hpp"

namespace YuriTea {

void WindowsWindow::OnUpdate(){

}

WindowsWindow::WindowsWindow(const WindowProps &props){ 

  Init(props);
}

WindowsWindow::~WindowsWindow() {
  //析构函数实现
  Shutdown();
  m_Window = nullptr;
  m_Context = nullptr;
    
}


void WindowsWindow::Init(const WindowProps &props){
  // 初始化函数实现
  m_Data.Title = props.Title;
  m_Data.WindowSize = props.Size;
  m_Data.VSync = false;
  m_Data.Fullscreen = false;
  m_Data.CursorVisible = true;

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


  m_Window = SDL_CreateWindow(m_Data.Title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              m_Data.WindowSize.x,
                              m_Data.WindowSize.y,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
  if (m_Window == nullptr) {
    YT_CORE_ERROR("SDL窗口创建失败: {0}", SDL_GetError());
    YT_CORE_ASSERT(false, "SDL窗口创建失败");
    return;
  }else{
    YT_CORE_INFO("SDL窗口创建成功");
  }


  SetFullscreen(m_Data.Fullscreen);
  SetCursorVisible(m_Data.CursorVisible);
  SetVSync(m_Data.VSync);
  

  m_Context = SDL_GL_CreateContext(m_Window);

  if (m_Context == nullptr) {
    YT_CORE_ERROR("OpenGL上下文创建失败: {0}", SDL_GetError());
    YT_CORE_ASSERT(false, "OpenGL上下文创建失败");
    return;
  }


  
}


void WindowsWindow::Shutdown(){
  // 关闭函数实现

  SDL_GL_DeleteContext(m_Context);
  SDL_DestroyWindow(m_Window);
  SDL_Quit();

}

void WindowsWindow::SetVSync(bool enabled){
  // 垂直同步函数实现
  m_Data.VSync = enabled;
  if (m_Data.VSync) {
    SDL_GL_SetSwapInterval(1);
  } else {
    SDL_GL_SetSwapInterval(0);
  }
}


bool WindowsWindow::IsVSync() const{
  return m_Data.VSync;
}

void WindowsWindow::SetFullscreen(bool enabled){
  // 全屏函数实现
  m_Data.Fullscreen = enabled;
  if (m_Data.Fullscreen) {
    SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
  } else {
    SDL_SetWindowFullscreen(m_Window, 0);
  }
}

bool WindowsWindow::IsFullscreen() const{
  return m_Data.Fullscreen;
}


void WindowsWindow::SetSize(const Vector2<uint32> &size){
  m_Data.WindowSize = size;
  SDL_SetWindowSize(m_Window, m_Data.WindowSize.x, m_Data.WindowSize.y);

}


void WindowsWindow::SetSize(const uint32 &width, const uint32 &height){
  m_Data.WindowSize = {width, height};
  SDL_SetWindowSize(m_Window, m_Data.WindowSize.x, m_Data.WindowSize.y);
}


void WindowsWindow::SetTitle(const std::string &title){
  m_Data.Title = title;
  SDL_SetWindowTitle(m_Window, m_Data.Title.c_str());
}


void WindowsWindow::SetCursorVisible(bool visible){
  m_Data.CursorVisible = visible;
  if (m_Data.CursorVisible) {
    SDL_ShowCursor(SDL_ENABLE);
  } else {
    SDL_ShowCursor(SDL_DISABLE);
  }
}


bool WindowsWindow::IsCursorVisible() const {
  return m_Data.CursorVisible;
}


}

