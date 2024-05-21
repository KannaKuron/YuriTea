#pragma once
#include "YuriTea/Core/base.hpp"
#include "YuriTea/Core/core.hpp"
#include "YuriTea/Events/event.hpp"
#include <winbase.h>


namespace YuriTea {

class YURITEA_API WindowResizeEvent : public Event {
public:
  WindowResizeEvent(uint32 width, uint32 height)
      : m_Size{width,height} {}
  WindowResizeEvent(const Vector2<uint32> &&size)
      : m_Size(size) {}
  virtual ~WindowResizeEvent() = default;

  inline const uint32 &GetWidth() const { return m_Size.x; }
  inline const uint32 &GetHeight() const { return m_Size.y; }

  inline const Vector2<uint32> &GetSize() const { return m_Size; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << m_Size.x << "," << m_Size.y;
    return ss.str();
}

  EVENT_CLASS_TYPE(EventType::WindowResize)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

private:
  Vector2<uint32> m_Size;
};

class YURITEA_API WindowCloseEvent : public Event {
  public:
    WindowCloseEvent() = default;
    virtual ~WindowCloseEvent() = default;

  std::string ToString() const override {
    return "WindowCloseEvent";
  }

  EVENT_CLASS_TYPE(EventType::WindowClose)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API AppTerminateEvent : public Event {
  public:
    AppTerminateEvent() = default;
    virtual ~AppTerminateEvent() = default;
  std::string ToString() const override {
    return "AppTerminateEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::APPTERMINATE)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API AppTickEvent : public Event {
  public:
    AppTickEvent() = default;
    virtual ~AppTickEvent() = default;

  std::string ToString() const override {
    return "AppTickEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::AppTick)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

};


class YURITEA_API AppUpdateEvent : public Event {
  public:
    AppUpdateEvent() = default;
    virtual ~AppUpdateEvent() = default;

  std::string ToString() const override {
    return "AppUpdateEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::AppUpdate)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API WindowFocusEvent : public Event {
  public:
    WindowFocusEvent() = default;
    virtual ~WindowFocusEvent() = default;
  std::string ToString() const override {
    return "WindowFocusEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::WindowFocus)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API WindowLostFocusEvent : public Event {
  public:
    WindowLostFocusEvent() = default;
    virtual ~WindowLostFocusEvent() = default;
  std::string ToString() const override {
    return "WindowLostFocusEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::WindowLostFocus)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API WindowMovedEvent : public Event {
  public:
    WindowMovedEvent(uint32 x, uint32 y)
        : m_Position{x,y} {}
    WindowMovedEvent(const Vector2<uint32> &&position)
        : m_Position(position) {}
    virtual ~WindowMovedEvent() = default;
  inline const uint32 &GetX() const { return m_Position.x; }
  inline const uint32 &GetY() const { return m_Position.y; }
  inline const Vector2<uint32> &GetPosition() const { return m_Position; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowMovedEvent: " << m_Position.x << "," << m_Position.y;
    return ss.str();
  }
  EVENT_CLASS_TYPE(EventType::WindowMoved)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
protected:
  Vector2<uint32> m_Position;
};

class YURITEA_API WindowMinimizedEvent : public Event {
  public:
    WindowMinimizedEvent() = default;
    virtual ~WindowMinimizedEvent() = default;
  std::string ToString() const override {
    return "WindowMinimizedEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::WindowMinimized)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};



class YURITEA_API WindowMaximizedEvent : public Event {
  public:
    WindowMaximizedEvent() = default;
    virtual ~WindowMaximizedEvent() = default;
  std::string ToString() const override {
    return "WindowMaximizedEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::WindowMaximized)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API WindowShowEvent : public Event {
  public:
    WindowShowEvent() = default;
    virtual ~WindowShowEvent() = default;
  std::string ToString() const override {
    return "WindowShowEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::WindowShown)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API WindowHideEvent : public Event {
  public:
    WindowHideEvent() = default;
    virtual ~WindowHideEvent() = default;
  std::string ToString() const override {
    return "WindowHideEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::WindowHidden)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API WindowEnterEvent : public Event {
  public:
    WindowEnterEvent() = default;
    virtual ~WindowEnterEvent() = default;
  std::string ToString() const override {
    return "WindowEnterEvent";
  }
  EVENT_CLASS_TYPE(EventType::WindowEnter)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API WindowLeaveEvent : public Event {
  public:
    WindowLeaveEvent() = default;
    virtual ~WindowLeaveEvent() = default;
  std::string ToString() const override {
    return "WindowLeaveEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::WindowLeave)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};


class YURITEA_API WindowExposedEvent : public Event {
  public:
    WindowExposedEvent() = default;
    virtual ~WindowExposedEvent() = default;
  std::string ToString() const override {
    return "WindowExposedEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::WindowExposed)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API WindowRestoredEvent : public Event {
  public:
    WindowRestoredEvent() = default;
    virtual ~WindowRestoredEvent() = default;
  std::string ToString() const override {
    return "WindowRestoredEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::WindowRestored)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};


class YURITEA_API AppRenderEvent : public Event {
  public:
    AppRenderEvent() = default;
    virtual ~AppRenderEvent() = default;
  std::string ToString() const override {
    return "AppRenderEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::AppRender)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};


} // namespace YuriTea
