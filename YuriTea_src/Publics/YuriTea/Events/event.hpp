#pragma once

#include "YuriTea/Core/core.hpp"

namespace YuriTea {

enum class EventType : uint16 {
  None = 0,
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowMoved,
  AppTick,
  AppUpdate,
  AppRender,
  KeyPressed,
  KeyReleased,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled
};

enum EventCategory : uint8 {
  None = 0,
  EventCategoryApplication = BIT(0), // BIT(0) = 00000001
  EventCategoryInput = BIT(1),       // BIT(1) = 00000010
  EventCategoryKeyboard = BIT(2),    // BIT(2) = 00000100
  EventCategoryMouse = BIT(3),       // BIT(3) = 00001000
  EventCategoryMouseButton = BIT(4)  // BIT(4) = 00010000
};

#define EVENT_CLASS_TYPE(type)                                                 \
  static EventType GetStaticType() { return type; }                            \
  virtual EventType GetEventType() const override { return GetStaticType(); }  \
  virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                         \
  virtual uint32_t GetCategoryFlags() const override { return category; }

class YURITEA_API Event {
  friend class EventDispatcher; // 事件分发器

public:
  virtual EventType GetEventType() const = 0;
  virtual uint32_t GetCategoryFlags() const = 0;
  virtual const char *GetName() const = 0;
  virtual std::string ToString() const { return GetName(); }

  inline bool IsInCategory(const EventCategory &category) {
    return GetCategoryFlags() & category;
  }

  inline bool IsInCategory(const EventCategory &&category) {
    return GetCategoryFlags() & category;
  }

public:
  Event() = default;          // 默认构造函数
  virtual ~Event() = default; // 默认析构函数

protected:
  bool m_Handled = false;
};

class EventDispatcher {
  template <typename T> using EventFn = std::function<bool(T &)>;

public:
  EventDispatcher(Event &event) : m_Event(event) {}

  template <typename T> bool Dispatch(EventFn<T> func) {
    if (m_Event.GetEventType() == T::GetStaticType()) {
      m_Event.m_Handled = func(*(T *)&m_Event);
      return true;
    }
    return false;
  }

private:
  Event &m_Event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e) {
  return os << e.ToString();
}

} // namespace YuriTea
