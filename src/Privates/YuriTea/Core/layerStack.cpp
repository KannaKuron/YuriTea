#include "YuriTea/Core/layerStack.hpp"
#include "YuriTea/Core/log.hpp"

namespace YuriTea {

LayerStack::LayerStack() : m_LayerInsertIndex(0)  {
  m_Layers = std::vector<Scope<Layer>>();
  m_Layers.reserve(0);
}

LayerStack::~LayerStack() {
  for(Scope<Layer>& layer : m_Layers) {
    layer->OnDetach();
    layer.reset();
  }
    
}

void LayerStack::PushLayer(Layer*&& layer) {

    Scope<Layer> temp(layer);
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(temp));
    m_LayerInsertIndex++;
    layer->OnAttach();
}

void LayerStack::PushOverlay(Layer*&& overlay) {
  Scope<Layer> temp(overlay);
  m_Layers.emplace_back(std::move(temp));
  overlay->OnAttach();
}

void LayerStack::PopLayer(Layer*&& layer) {
  const auto& it = std::find_if(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex,
                                [layer](const Scope<Layer>& l) { return l.get() == layer; } );
  if(it != m_Layers.begin() + m_LayerInsertIndex) {
    layer->OnDetach();
    m_Layers.erase(it);
    m_LayerInsertIndex--;
  }
  else {
    // Layer not found
    YT_CORE_WARN("Layer not found in LayerStack");
  }
}

void LayerStack::PopOverlay(Layer*&& overlay) {
  auto it = std::find_if(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), 
                         [overlay](const Scope<Layer>& l) { return l.get() == overlay; } );
  if(it != m_Layers.end()) {
    overlay->OnDetach();
    m_Layers.erase(it);
  }
  else {
    // Overlay not found
    YT_CORE_WARN("Overlay not found in LayerStack");
  }
}



}

