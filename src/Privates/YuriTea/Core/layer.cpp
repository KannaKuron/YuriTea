#include "YuriTea/Core/layer.hpp"

namespace YuriTea {

Layer::Layer(const std::string& name): m_DebugName(name) {
  // 构造函数实现
  YT_CORE_INFO("Layer Call Back Constructor 正在构造Layer类 ,Layer Name:{0}",m_DebugName);
    

}

Layer::~Layer() {
  // 析构函数实现
  YT_CORE_INFO("Layer Call Back Destructor 正在析构Layer类 ,Layer Name:{0}",m_DebugName);
    
    
    
}

}

