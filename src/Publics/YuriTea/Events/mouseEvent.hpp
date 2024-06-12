#pragma once

#include "YuriTea/Core/keyCodes.hpp"
#include "YuriTea/Core/mouseCodes.hpp"
#include "YuriTea/Events/event.hpp"

using namespace YuriTea::Mouse;
using namespace YuriTea::Key;

namespace YuriTea {
class YURITEA_API MouseMovedEvent : public Event {
public:
  MouseMovedEvent(float32 x, float32 y, float32 lastX, float32 lastY,
                  uint32 timeStamp, uint32 state, uint32 keyMod , bool isMousemotion, uint32 windowID)
      : m_Position(x, y), m_LastPosition(lastX, lastY), m_TimeStamp(timeStamp),
        m_State(state), m_KeyMod(keyMod) , m_MouseMoved(isMousemotion) , m_WindowID(windowID) {}
  MouseMovedEvent(Vector2<float32> position, Vector2<float32> lastPosition,
                  uint32 timeStamp, uint32 state, uint32 keyMod, bool isMousemotion , uint32 windowID)
      : m_Position(position), m_LastPosition(lastPosition),
        m_TimeStamp(timeStamp), m_State(state), m_KeyMod(keyMod) , m_MouseMoved(isMousemotion) , m_WindowID(windowID) {}
  MouseMovedEvent(const SDL_Event &event ,KeyMod keyMod)
      : m_Position(event.motion.x, event.motion.y),
        m_LastPosition(event.motion.xrel, event.motion.yrel),
        m_TimeStamp(event.motion.timestamp), m_State(event.motion.state),
        m_MouseMoved(true) , m_WindowID(event.motion.windowID), m_KeyMod(keyMod) {}
  ~MouseMovedEvent() = default;

  inline const float32 &GetX() const { return m_Position.x; }
  inline const float32 &GetY() const { return m_Position.y; }
  inline const Vector2<float32> &GetPosition() const { return m_Position; }
  inline const float32 &GetLastX() const { return m_LastPosition.x; }
  inline const float32 &GetLastY() const { return m_LastPosition.y; }
  inline const Vector2<float32> &GetLastPosition() const {
    return m_LastPosition;
  }
  inline const uint32 &GetTimeStamp() const { return m_TimeStamp; }
  inline const uint32 &GetState() const { return m_State; }
  inline const uint32 &GetKeyMod() const { return m_KeyMod; }
  inline const uint32 &GetWindowID() const { return m_WindowID; }

  inline void SetMouseMoved(bool moved) { m_MouseMoved = moved; }
  inline const bool &IsMouseMotion() const { return m_MouseMoved; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << m_Position.x << "," << m_Position.y << ",WindowID: " << m_WindowID <<
    "\nKeyMod: " << m_KeyMod;

    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::MouseMoved)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse |
                       EventCategory::EventCategoryInput)

protected:
  Vector2<float32> m_Position;
  Vector2<float32> m_LastPosition;
  uint32 m_TimeStamp;
  uint32 m_State;
  uint32 m_KeyMod;
  bool m_MouseMoved = true;
  uint32 m_WindowID;
};

class YURITEA_API MouseScrolledEvent : public Event {
public:
  MouseScrolledEvent(float32 positionX, float32 positionY, float32 offsetX,
                    float32 offsetY, uint32 timeStamp, KeyMod modifiers ,bool isMousemotion, uint32 windowID)
  : m_Position(positionX, positionY), m_Offset(offsetX, offsetY), m_TimeStamp(timeStamp)
    , m_Modifiers(modifiers), m_MouseMoved(isMousemotion) , m_WindowID(windowID) {}
  MouseScrolledEvent(const SDL_Event &event, KeyMod modifiers)
      : m_Position(event.wheel.x, event.wheel.y),
        m_Offset(event.wheel.x, event.wheel.y), m_TimeStamp(event.wheel.timestamp),
        m_Modifiers(modifiers), m_MouseMoved(true) , m_WindowID(event.wheel.windowID) {}
 
  ~MouseScrolledEvent() = default;

  inline const float32 &GetHorizontalOffset() const { return m_Offset.x; }
  inline const float32 &GetVerticalOffset() const { return m_Offset.y; }
  inline const Vector2<float32> &GetOffset() const { return m_Offset; }
  inline const float32 &GetX() const { return m_Position.x; }
  inline const float32 &GetY() const { return m_Position.y; }
  inline const Vector2<float32> &GetPosition() const { return m_Position; }
  inline const uint32 &GetTimeStamp() const { return m_TimeStamp; }
  inline const KeyMod &GetModifiers() const { return m_Modifiers; }
  inline const uint32 &GetWindowID() const { return m_WindowID; }

  inline void SetMouseMoved(bool moved) { m_MouseMoved = moved; }
  inline const bool &IsMouseMotion() const { return m_MouseMoved; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << m_Offset.x << "," << m_Offset.y << ",WindowID: " << m_WindowID;
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::MouseScrolled)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse |
                       EventCategory::EventCategoryInput)

protected:
  Vector2<float32> m_Position; // mouse position
  Vector2<float32> m_Offset; // scroll offset x is horizontal, y is vertical x 是水平 y 是垂直
  uint32 m_TimeStamp;
  KeyMod m_Modifiers;
  bool m_MouseMoved = true;
  uint32 m_WindowID;
  
};

class YURITEA_API MouseButtonEvent : public Event {
public:
  MouseButtonEvent(MouseCode button, KeyMod modifiers , float32 x, float32 y, uint32 timeStamp ,bool isMousemotion, uint32 windowID = 0)
      : m_Button(button), m_Modifiers(modifiers), m_Position(x, y), m_TimeStamp(timeStamp) ,m_MouseMoved(isMousemotion), m_WindowID(windowID) {}
  MouseButtonEvent(const SDL_Event &event, KeyMod modifiers)
      : m_Button(static_cast<MouseCode>(event.button.button)),
        m_Modifiers(modifiers), m_Position(event.button.x, event.button.y),
        m_TimeStamp(event.button.timestamp), m_WindowID(event.button.windowID) {}

  ~MouseButtonEvent() = default;

  inline const MouseCode &GetButton() const { return m_Button; }
  inline const KeyMod &GetModifiers() const { return m_Modifiers; }
  inline const Vector2<float32> &GetPosition() const { return m_Position; }
  inline const uint32 &GetTimeStamp() const { return m_TimeStamp; }
  inline const float32 &GetX() const { return m_Position.x; }
  inline const float32 &GetY() const { return m_Position.y; }
  inline void SetMouseMoved(bool moved) { m_MouseMoved = moved; }
  inline const bool &IsMouseMotion() const { return m_MouseMoved; }
  inline const uint32 &GetWindowID() const { return m_WindowID; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonEvent: " << m_Button << " (" << m_Position.x << ", "
      << m_Position.y << ")" << "WindowID: " << m_WindowID;
    return ss.str();
  }

  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouseButton |
                       EventCategory::EventCategoryInput)

protected:
  MouseCode m_Button;
  KeyMod m_Modifiers;
  Vector2<float32> m_Position;
  uint32 m_TimeStamp; 
  bool m_MouseMoved = true;
  mutable uint32 m_WindowID;
};

class YURITEA_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
  MouseButtonPressedEvent(MouseCode button, KeyMod modifiers, uint32 repeatCount,
                          float32 x, float32 y, uint32 timeStamp,bool isMousemotion , uint32 windowID)
      : MouseButtonEvent(button, modifiers, x, y, timeStamp ,isMousemotion,windowID), m_RepeatCount(repeatCount) {}
  MouseButtonPressedEvent(const SDL_Event &event, KeyMod modifiers)
      :MouseButtonEvent(event, modifiers), m_RepeatCount(event.button.clicks) {}

  ~MouseButtonPressedEvent() = default;

  inline const uint8 &GetRepeatCount() const { return m_RepeatCount; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << m_Button << " (" << m_RepeatCount
      << " repeats)" << " (" << m_Position.x << ", " << m_Position.y << ")" << "WindowID: " << m_WindowID;
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::MouseButtonPressed)

protected:
  uint8 m_RepeatCount;
  
};

class YURITEA_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  MouseButtonReleasedEvent(MouseCode button, KeyMod modifiers, float32 x, float32 y, uint32 timeStamp,bool isMousemotion, uint32 windowID)
      : MouseButtonEvent(button, modifiers, x, y, timeStamp,isMousemotion, windowID) {}
  MouseButtonReleasedEvent(const SDL_Event &event, KeyMod modifiers)
      : MouseButtonEvent(event, modifiers) {}
  ~MouseButtonReleasedEvent() = default;

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << m_Button << " (" << m_Position.x
      << ", " << m_Position.y << ")" << "WindowID: " << m_WindowID;
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
};

} // namespace YuriTea
