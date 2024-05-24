#pragma once
#include "YuriTea/Core/core.hpp"
#include "YuriTea/Core/layer.hpp"

namespace YuriTea {

class YURITEA_API LayerStack {
public:
  LayerStack(); // 构造函数
  ~LayerStack(); // 析构函数

  void PushLayer(Layer* layer); // 添加一个Layer
  void PushOverlay(Layer* overlay); // 添加一个Overlay 
  void PopLayer(Layer* layer); // 移除一个Layer
  void PopOverlay(Layer* overlay); // 移除一个Overlay

  std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
  std::vector<Layer*>::iterator end() { return m_Layers.end(); }

protected:
  std::vector<Layer*> m_Layers;
  uint32 m_LayerInsertIndex = 0;

    
};

}

