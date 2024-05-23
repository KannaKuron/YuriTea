#pragma once
#include "YuriTea/Core/core.hpp"
#include "YuriTea/Events/event.hpp"



namespace YuriTea {

class YURITEA_API Layer {
public:
  Layer(const std::string& name = "Layer"); // 构造函数
  virtual ~Layer(); // 析构函数
    
  virtual void OnAttach() {}; // 当Layer被添加到LayerStack时调用
  virtual void OnDetach() {}; // 当Layer从LayerStack中移除时调用
  virtual void OnUpdate() {}; // 每帧调用
  virtual void OnEvent(Event& event) {}; // 事件处理

  inline const std::string& GetName() const { return m_DebugName; } // 获取Layer的名字
    
protected:
  std::string m_DebugName;
  bool m_Enabled = false;
    
};

}

