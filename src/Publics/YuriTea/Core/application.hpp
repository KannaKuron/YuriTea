#pragma once
#include "YuriTea/Core/core.hpp"
#include "YuriTea/Core/window.hpp"
#include "YuriTea/Events/applicationEvent.hpp"
#include "YuriTea/Events/keyEvent.hpp"
#include "YuriTea/Events/mouseEvent.hpp"
#include "YuriTea/Core/layerStack.hpp"



namespace YuriTea {

class YURITEA_API Application {
  friend Application *CreateApplication();
public:
  virtual ~Application(); // 析构函数

  static void Start(Application *);
  static int32 Close();
  static Application *Get() { return m_App.get(); }

  Window* GetWindow() { return m_Window.get(); }

  void Run();
  void OnEvent(Event &);


  void PushLayer(Layer *&& layer);
  void PushOverlay(Layer *&& overlay);

protected:
    Application();          // 构造函数
private:
  bool OnWindowClose(WindowCloseEvent &);


private:
  static Scope<Application> m_App;
  Scope<Window> m_Window;
  Scope<LayerStack> m_LayerStack;
  bool m_Running = true;
};

Application *CreateApplication();

} // namespace YuriTea
