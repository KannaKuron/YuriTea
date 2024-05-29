#pragma once

#include "YuriTea/Core/core.hpp"
#include "YuriTea/Core/layer.hpp"


namespace YuriTea {

class YURITEA_API ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach() override; // 当Layer被添加到LayerStack时调用
  void OnDetach() override; // 当Layer从LayerStack中移除时调用

  void OnUpdate() override; // 每帧调用
  void OnEvent(Event& event) override; // 事件处理

  
  

private:
  ImGuiIO* io; 
  float32 m_Time = 0.0f;



};

}
