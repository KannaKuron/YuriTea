#pragma once
#include "YuriTea/Core/window.hpp"
#include "YuriTea/Events/applicationEvent.hpp"
#include "YuriTea/Events/keyEvent.hpp"
#include "YuriTea/Events/mouseEvent.hpp"
#include "YuriTea/Core/layerStack.hpp"
#include <spdlog/spdlog.h>



namespace YuriTea {

class YURITEA_API Application {
public:
  Application();          // 构造函数
  virtual ~Application(); // 析构函数

  void Run();
  void OnEvent(Event &);

  void PushLayer(Layer *layer);
  void PushOverlay(Layer *overlay);

private:
  bool OnWindowClose(WindowCloseEvent &);


private:
  Scope<Window> m_Window;
  Scope<LayerStack> m_LayerStack;
  bool m_Running = true;
};

// To be defined in CLIENT
Application *CreateApplication();

} // namespace YuriTea
