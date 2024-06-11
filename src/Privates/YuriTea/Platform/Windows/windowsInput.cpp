#include "YuriTea/Core/input.hpp"

namespace YuriTea {

bool Input::IsKeyPressed(const KeyCode& key){
  //检测键盘按键是否被按下
  const uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[static_cast<SDL_Scancode>(SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(key)))]){
    return true;
  }
  return false;
}


bool Input::IsMouseButtonPressed(const MouseCode& button){
  const uint32 state = SDL_GetMouseState(nullptr, nullptr);
  if (state & SDL_BUTTON(button)){
    return true;
  }
  return false;
}

KeyMod Input::GetKeyMods(){
  return static_cast<KeyMod>(SDL_GetModState());
}

Vector2<float> Input::GetMousePosition(){
  int32 x, y;
  std::ignore = SDL_GetMouseState(&x, &y);
  return {static_cast<float>(x), static_cast<float>(y)};
}


float Input::GetMouseX(){
  int32 x;
  std::ignore = SDL_GetMouseState( &x, nullptr);
  return static_cast<float>(x);
}


float Input::GetMouseY(){
  int32 y;
  std::ignore = SDL_GetMouseState(nullptr, &y);
  return static_cast<float>(y);
}


}

