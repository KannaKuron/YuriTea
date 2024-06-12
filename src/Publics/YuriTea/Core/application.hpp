#pragma once
#include "YuriTea/Core/basicstruct.hpp"
#include "YuriTea/Core/core.hpp"
#include "YuriTea/Core/layerStack.hpp"



namespace YuriTea {

class YURITEA_API Application {
  friend Application *CreateApplication();
public:
  virtual ~Application(); // 析构函数

  static void Start(Application *);
  static int32 Close();

  static const Application *Get() { return m_App.get(); }

  Window* GetWindow() const { return m_Windows[0].get(); }

  void Run();
  void OnEvent(Event &);


  void PushLayer(Layer *&& layer);
  void PushOverlay(Layer *&& overlay);

protected:
    Application();          // 构造函数
private:
  bool OnWindowClose(WindowCloseEvent &);
  bool OnAppTerminate(AppTerminateEvent&);


private:
  static Scope<Application> m_App;
  std::vector<Scope<Window>> m_Windows;
  Scope<LayerStack> m_LayerStack;
  bool m_Running = true;
};

Application *CreateApplication();

} // namespace YuriTea
