#include "YuriTea/Core/application.hpp"
#include <YuriTea/glad/glad.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace YuriTea {

Application::Application() {
  // 构造函数实现
  WindowProps props;
  m_Window = Window::Create(props);
  m_Running = true;

  m_Window->SetEventCallback(YT_BIND_EVENT_FN(Application::OnEvent));
}

void Application::OnEvent(Event &e) {
  // 事件处理函数实现
  YT_CORE_INFO("Application Call Back OnEvent ,the Event :{0}",e.ToString());
  if (e.GetEventType() == EventType::WindowClose) {
    m_Running = false;
  }


}

Application::~Application() {
  // 析构函数实现
}

void Application::Run() {
  YT_CORE_INFO("Application Loop now is Running");
  while (m_Running) {
    // 一直循环
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    SDL_Window *window = static_cast<SDL_Window *>(m_Window->GetNativeWindow());
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    m_Window->OnUpdate();
    SDL_PumpEvents(); // 更新事件
  }
}


Application *CreateApplication() { return new Application(); }
} // namespace YuriTea
