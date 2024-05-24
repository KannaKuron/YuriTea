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
                  uint32 timeStamp, uint32 state, uint32 keyMod)
      : m_Position(x, y), m_LastPosition(lastX, lastY), m_TimeStamp(timeStamp),
        m_State(state), m_KeyMod(keyMod) {}
  MouseMovedEvent(Vector2<float32> position, Vector2<float32> lastPosition,
                  uint32 timeStamp, uint32 state, uint32 keyMod)
      : m_Position(position), m_LastPosition(lastPosition),
        m_TimeStamp(timeStamp), m_State(state), m_KeyMod(keyMod) {}

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

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << m_Position.x << "," << m_Position.y;
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
};

class YURITEA_API MouseScrolledEvent : public Event {
public:
  MouseScrolledEvent(float32 positionX, float32 positionY, float32 offsetX,
                    float32 offsetY, uint32 timeStamp, KeyMod modifiers)
  : m_Position(positionX, positionY), m_Offset(offsetX, offsetY), m_TimeStamp(timeStamp), m_Modifiers(modifiers) {}
 
  ~MouseScrolledEvent() = default;

  inline const float32 &GetHorizontalOffset() const { return m_Offset.x; }
  inline const float32 &GetVerticalOffset() const { return m_Offset.y; }
  inline const Vector2<float32> &GetOffset() const { return m_Offset; }
  inline const float32 &GetX() const { return m_Position.x; }
  inline const float32 &GetY() const { return m_Position.y; }
  inline const Vector2<float32> &GetPosition() const { return m_Position; }
  inline const uint32 &GetTimeStamp() const { return m_TimeStamp; }
  inline const KeyMod &GetModifiers() const { return m_Modifiers; }


  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << m_Offset.x << "," << m_Offset.y;
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
  
};

class YURITEA_API MouseButtonEvent : public Event {
public:
  MouseButtonEvent(MouseCode button, KeyMod modifiers , float32 x, float32 y, uint32 timeStamp)
      : m_Button(button), m_Modifiers(modifiers), m_Position(x, y), m_TimeStamp(timeStamp) {}

  ~MouseButtonEvent() = default;

  inline const MouseCode &GetButton() const { return m_Button; }
  inline const KeyMod &GetModifiers() const { return m_Modifiers; }
  inline const Vector2<float32> &GetPosition() const { return m_Position; }
  inline const uint32 &GetTimeStamp() const { return m_TimeStamp; }
  inline const float32 &GetX() const { return m_Position.x; }
  inline const float32 &GetY() const { return m_Position.y; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonEvent: " << m_Button;
    return ss.str();
  }

  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouseButton |
                       EventCategory::EventCategoryInput)

protected:
  MouseCode m_Button;
  KeyMod m_Modifiers;
  Vector2<float32> m_Position;
  uint32 m_TimeStamp;
};

class YURITEA_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
  MouseButtonPressedEvent(MouseCode button, KeyMod modifiers, uint32 repeatCount, float32 x, float32 y, uint32 timeStamp)
      : MouseButtonEvent(button, modifiers, x, y, timeStamp), m_RepeatCount(repeatCount) {}

  ~MouseButtonPressedEvent() = default;

  inline const uint8 &GetRepeatCount() const { return m_RepeatCount; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << m_Button << " (" << m_RepeatCount
       << " repeats)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::MouseButtonPressed)

protected:
  uint8 m_RepeatCount;
  
};

class YURITEA_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  MouseButtonReleasedEvent(MouseCode button, KeyMod modifiers, float32 x, float32 y, uint32 timeStamp)
      : MouseButtonEvent(button, modifiers, x, y, timeStamp) {}

  ~MouseButtonReleasedEvent() = default;

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << m_Button;
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
};

} // namespace YuriTea
