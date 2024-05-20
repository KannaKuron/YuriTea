#pragma once

#include "YuriTea/Core/keyCodes.hpp"
#include "YuriTea/Core/mouseCodes.hpp"
#include "YuriTea/Events/event.hpp"

using namespace YuriTea::Mouse;
using namespace YuriTea::Key;

namespace YuriTea {
class YURITEA_API MouseMovedEvent : public Event {
public:
  MouseMovedEvent(float32 x, float32 y) : m_Position(x, y) {}
  ~MouseMovedEvent() = default;

  inline const float32 &GetX() const { return m_Position.x; }
  inline const float32 &GetY() const { return m_Position.y; }
  inline const Vector2<float32> &GetPosition() const { return m_Position; }

#ifdef YuriTea_DEBUG
  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << m_Position.x << "," << m_Position.y;
    return ss.str();
  }
#endif

  EVENT_CLASS_TYPE(EventType::MouseMoved)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse |
                       EventCategory::EventCategoryInput)

protected:
  Vector2<float32> m_Position;
};

class YURITEA_API MouseScrolledEvent : public Event {
public:
  MouseScrolledEvent(float32 xOffset, float32 yOffset)
      : m_Offset(xOffset, yOffset) {}
  ~MouseScrolledEvent() = default;

  inline const float32 &GetXOffset() const { return m_Offset.x; }
  inline const float32 &GetYOffset() const { return m_Offset.y; }
  inline const Vector2<float32> &GetOffset() const { return m_Offset; }

#ifdef YuriTea_DEBUG
  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << m_Offset.x << "," << m_Offset.y;
    return ss.str();
  }
#endif

  EVENT_CLASS_TYPE(EventType::MouseScrolled)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse |
                       EventCategory::EventCategoryInput)

protected:
  Vector2<float32> m_Offset;
};

class YURITEA_API MouseButtonEvent : public Event {
public:
  MouseButtonEvent(MouseCode button, KeyMod modifiers)
      : m_Button(button), m_Modifiers(modifiers) {}
  ~MouseButtonEvent() = default;

  inline const MouseCode &GetButton() const { return m_Button; }
  inline const KeyMod &GetModifiers() const { return m_Modifiers; }

#ifdef YuriTea_DEBUG
  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonEvent: " << m_Button;
    return ss.str();
  }
#endif

  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse |
                       EventCategory::EventCategoryInput)

protected:
  MouseCode m_Button;
  KeyMod m_Modifiers;
};

class YURITEA_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
  MouseButtonPressedEvent(MouseCode button, KeyMod modifiers,
                          uint32 repeatCount)
      : MouseButtonEvent(button, modifiers), m_RepeatCount(repeatCount) {}

  inline const uint32 &GetRepeatCount() const { return m_RepeatCount; }

#ifdef YuriTea_DEBUG
  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << m_Button << " (" << m_RepeatCount
       << " repeats)";
    return ss.str();
  }
#endif

  EVENT_CLASS_TYPE(EventType::MouseButtonPressed)

protected:
  uint32 m_RepeatCount;
};

class YURITEA_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  MouseButtonReleasedEvent(MouseCode button, KeyMod modifiers)
      : MouseButtonEvent(button, modifiers) {}
  ~MouseButtonReleasedEvent() = default;

#ifdef YuriTea_DEBUG
  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << m_Button;
    return ss.str();
  }
#endif

  EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
};

} // namespace YuriTea
