#pragma once
#include "YuriTea/Core/base.hpp"

namespace YuriTea {

namespace Mouse {

#define YuriTea_BUTTON(X) (1 << ((X) - 1))

enum MouseCode : uint16 {
  // from sdl2
  
  BUTTON_LEFT = 1, // 鼠标左键
  BUTTON_MIDDLE = 2, // 鼠标中键
  BUTTON_RIGHT = 3, // 鼠标右键
  BUTTON_X1 = 4, // 鼠标X1键 
  BUTTON_X2 = 5, // 鼠标X2键
  BUTTON_LMASK = YuriTea_BUTTON(BUTTON_LEFT), // 鼠标左键掩码
  BUTTON_MMASK = YuriTea_BUTTON(BUTTON_MIDDLE), // 鼠标中键掩码
  BUTTON_RMASK = YuriTea_BUTTON(BUTTON_RIGHT), // 鼠标右键掩码
  BUTTON_X1MASK = YuriTea_BUTTON(BUTTON_X1), // 鼠标X1键掩码
  BUTTON_X2MASK = YuriTea_BUTTON(BUTTON_X2) // 鼠标X2键掩码

};

} // namespace Mouse

} // namespace YuriTea
