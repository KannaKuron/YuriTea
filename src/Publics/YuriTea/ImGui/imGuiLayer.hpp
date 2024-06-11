#pragma once

#include "YuriTea/Core/core.hpp"
#include "YuriTea/Core/layer.hpp"


namespace YuriTea {

class YURITEA_API ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer() = default;

  virtual void OnAttach() override; // 当Layer被添加到LayerStack时调用
  virtual void OnDetach() override; // 当Layer从LayerStack中移除时调用

  virtual void OnEvent(Event& event) override;

  virtual void OnUpdate() override;



  virtual void Begin();
  virtual void End();

  uint32 GetActiveWidgetID() const;
  
	void SetDarkThemeColors();
  
  void BlockEvents(bool block) { m_BlockEvents = block; }

private:
  bool m_BlockEvents = true;



};

}
