#pragma once
#include "YuriTea/Core/core.hpp"
#include "YuriTea/Core/layer.hpp"

namespace YuriTea {

class YURITEA_API LayerStack {
public:
  LayerStack(); // 构造函数
  ~LayerStack(); // 析构函数

  // 禁止复制构造函数和复制赋值操作符 ,意思是不能用左值初始化和赋值
  LayerStack(const LayerStack&) = delete;
  LayerStack& operator=(const LayerStack&) = delete;

  // 移动构造函数和移动赋值操作符,意思是可以用右值初始化和赋值
  LayerStack(LayerStack&&) = default;
  LayerStack& operator=(LayerStack&&) = default;
  
  void PushLayer(Layer*&& layer); // 添加一个Layer
  void PushOverlay(Layer*&& overlay); // 添加一个Overlay 
  void PopLayer(Layer*&& layer); // 移除一个Layer
  void PopOverlay(Layer*&& overlay); // 移除一个Overlay

  auto begin() { return m_Layers.begin(); }
  auto end() { return m_Layers.end(); }

protected:
  std::vector<Scope<Layer>> m_Layers;
  uint32 m_LayerInsertIndex = 0;

    
};

}

