#include "YuriTea/Core/application.hpp"
#include "YuriTea/Core/basicstruct.hpp"

namespace YuriTea {
Scope<Application> Application::m_App = nullptr;

Application::Application() {
  m_App.reset(this);
  
  // 构造函数实现
  WindowProps props;
  m_Window = Window::Create(props);
  m_LayerStack.reset(new LayerStack());
  m_Running = true;

  m_Window->SetEventCallback(YT_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() {
  // 析构函数实现
  YT_CORE_INFO("Application Call Back Destructor 正在析构Application类");
  m_Window.reset();
  m_LayerStack.reset();

}

void Application::OnEvent(Event &e) {
  // 事件处理函数实现
  YT_CORE_INFO("Application Call Back OnEvent ,the Event :{0}",e.ToString());
  EventDispatcher dispatcher(e);
  if( dispatcher.Dispatch<WindowCloseEvent>(YT_BIND_EVENT_FN(Application::OnWindowClose)))
    return;

  // 逆序遍历LayerStack ,处理事件 保证先处理Overlay再处理Layer
  for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();) {
    (*--it)->OnEvent(e);
    if (e.IsHandled()) {
      break;
    }
  }
}


void Application::Run() {
  YT_CORE_INFO("Application Loop now is Running");
  YT_CORE_INFO("m_Running {0}",m_Running);
  while (m_Running) {
    // 一直循环
    for (Layer *layer : *m_LayerStack) {
      layer->OnUpdate();
    }
    m_Window->OnUpdate();
  }
}
void Application::Start(Application *app) {
  m_App.reset(app);
  m_App->Run();
}

int32 Application::Close(){
  //循环检查m_AllQuit是否为true 否则一直循环

  m_App.reset();
  return 0;
}


bool Application::OnWindowClose(WindowCloseEvent & e){
  m_Running = false;
  return true;
}

void Application::PushLayer(Layer *layer){
  m_LayerStack->PushLayer(layer);

}

void Application::PushOverlay(Layer *overlay){
  m_LayerStack->PushOverlay(overlay);

}


Application *CreateApplication() { 
  return new Application();
}
} // namespace YuriTea
