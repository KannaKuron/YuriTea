#include "YuriTea/Core/application.hpp"
#include "YuriTea/Events/applicationEvent.hpp"

namespace YuriTea {
Scope<Application> Application::m_App = nullptr;

Application::Application() {
  m_App.reset(this);
  m_Windows.resize(1);
  
  // 构造函数实现
  WindowProps props;
  m_Windows[0] = Window::Create(props);
  m_LayerStack.reset(new LayerStack());
  m_Running = true;

  m_Windows[0]->SetEventCallback(YT_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() {
  // 析构函数实现
  for(auto& window : m_Windows){
    window.reset();
  }
  m_LayerStack.reset();

}

void Application::OnEvent(Event &e) {
  // 事件处理函数实现
  YT_CORE_TRACE("{0}", e.ToString());
  EventDispatcher dispatcher(e);
  if( dispatcher.Dispatch<WindowCloseEvent>(YT_BIND_EVENT_FN(Application::OnWindowClose))){
    YT_CORE_ERROR("The Error is {0}",SDL_GetError());
    return;
  }
  if( dispatcher.Dispatch<AppTerminateEvent>(YT_BIND_EVENT_FN(Application::OnAppTerminate))){
    YT_CORE_ERROR("The Error is {0}",SDL_GetError());
    return;
  }


  // 逆序遍历LayerStack ,处理事件 保证先处理Overlay再处理Layer
  for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();) {
    (*--it)->OnEvent(e);
    if (e.IsHandled()) {
      break;
    }
  }
}


void Application::Run() {
  while (m_Running) {
    // 一直循环

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for(const auto& layer : *m_LayerStack)
      layer.get()->OnUpdate();
    m_Windows[0]->OnUpdate();
  }
}

void Application::Start(Application *app) {
  m_App->Run();
}

int32 Application::Close(){
  //循环检查m_AllQuit是否为true 否则一直循环
  YT_CORE_WARN("Application Closeing...");

  if(m_App != nullptr) m_App.reset();

  return 0;
}


bool Application::OnWindowClose(WindowCloseEvent & e){
  if(e.GetWindowID() == 1){
    m_Running = false;
    return true;
  }
  return true;
}

bool Application::OnAppTerminate(AppTerminateEvent& e) {

  m_Running = false;
  return true;
}

void Application::PushLayer(Layer*&& layer){
  m_LayerStack->PushLayer(std::move(layer));
}

void Application::PushOverlay(Layer*&& overlay){
  m_LayerStack->PushOverlay(std::move(overlay));
}


Application *CreateApplication() { 
  return new Application();
}
} // namespace YuriTea
