#pragma once
#include "YuriTea/Core/core.hpp"

namespace YuriTea {

class YURITEA_API Input {
public:
  
  static bool IsKeyPressed(const KeyCode&);
  static bool IsMouseButtonPressed(const MouseCode&);
  static KeyMod GetKeyMods();

  static Vector2<float> GetMousePosition();
  static float GetMouseX();
  static float GetMouseY();
    
};

}

