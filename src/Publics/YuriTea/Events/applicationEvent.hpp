#pragma once
#include "YuriTea/Core/base.hpp"
#include "YuriTea/Events/event.hpp"


namespace YuriTea {

class YURITEA_API WindowResizeEvent : public Event {
public:
  WindowResizeEvent(uint32 width, uint32 height ,uint32 windowID)
      : m_Size{width,height} , m_WindowID(windowID) {}
  WindowResizeEvent(const Vector2<uint32> &size, uint32 windowID)
      : m_Size(size) , m_WindowID(windowID) {}
  WindowResizeEvent(const SDL_Event &event)
      : m_Size(event.window.data1, event.window.data2) , m_WindowID(event.window.windowID) {}

  virtual ~WindowResizeEvent() = default;

  inline const uint32 &GetWidth() const { return m_Size.x; }
  inline const uint32 &GetHeight() const { return m_Size.y; }

  inline const Vector2<uint32> &GetSize() const { return m_Size; }
  inline const uint32 &GetWindowID() const { return m_WindowID; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << m_Size.x << "," << m_Size.y << ",WindowID: " << m_WindowID;
    return ss.str();
}

  EVENT_CLASS_TYPE(EventType::WindowResize)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)

private:
  Vector2<uint32> m_Size;
  uint32 m_WindowID;
};

class YURITEA_API WindowCloseEvent : public Event {
public:
  WindowCloseEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowCloseEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}
  virtual ~WindowCloseEvent() = default;
  inline const uint32 &GetWindowID() const { return m_WindowID; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowCloseEvent  ,WindowID:" << m_WindowID;
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::WindowClose)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)

private:
  uint32 m_WindowID;
};

class YURITEA_API WindowFocusEvent : public Event {
public:
  WindowFocusEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowFocusEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}
  virtual ~WindowFocusEvent() = default;
  inline const uint32 &GetWindowID() { return m_WindowID; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowFocusEvent  ,WindowID:" << m_WindowID;
    return ss.str();
      
  }
  
  EVENT_CLASS_TYPE(EventType::WindowFocus)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
private:
  uint32 m_WindowID;
};

class YURITEA_API WindowLostFocusEvent : public Event {
public:
  WindowLostFocusEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowLostFocusEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}
  virtual ~WindowLostFocusEvent() = default;
  inline const uint32 &GetWindowID() const { return m_WindowID; }
  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowLostFocusEvent" << m_WindowID;
    return ss.str();
  }
  
  EVENT_CLASS_TYPE(EventType::WindowLostFocus)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
private:
  uint32 m_WindowID;
};

class YURITEA_API WindowMovedEvent : public Event {
  public:
    WindowMovedEvent(uint32 x, uint32 y, uint32 windowID)
        : m_Position{x,y} , m_WindowID(windowID) {}
    WindowMovedEvent(const Vector2<uint32> &&position, uint32 windowID)
        : m_Position(position) , m_WindowID(windowID) {}
  WindowMovedEvent(const SDL_Event &event)
      : m_Position(event.window.data1, event.window.data2) , m_WindowID(event.window.windowID) {}
  virtual ~WindowMovedEvent() = default;
  inline const uint32 &GetX() const { return m_Position.x; }
  inline const uint32 &GetY() const { return m_Position.y; }
  inline const Vector2<uint32> &GetPosition() const { return m_Position; }
  inline const uint32 &GetWindowID() const { return m_WindowID; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowMovedEvent: " << m_Position.x << "," << m_Position.y << "WindowID: " << m_WindowID;
    return ss.str();
  }
  EVENT_CLASS_TYPE(EventType::WindowMoved)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
protected:
  Vector2<uint32> m_Position;
  uint32 m_WindowID;
};

class YURITEA_API WindowMinimizedEvent : public Event {
public:
  WindowMinimizedEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowMinimizedEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}
  virtual ~WindowMinimizedEvent() = default;
  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowMinimizedEvent" << ",WindowID: " << m_WindowID << std::endl;
    return ss.str();
      
  }
  inline const uint32 &GetWindowID() const { return m_WindowID; }
  
  EVENT_CLASS_TYPE(EventType::WindowMinimized)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
private:
  uint32 m_WindowID;
};



class YURITEA_API WindowMaximizedEvent : public Event {
public:
  WindowMaximizedEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowMaximizedEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}

  virtual ~WindowMaximizedEvent() = default;
  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowMaximizedEvent" << ",WindowID: " << m_WindowID << std::endl;
    return ss.str();
  }
  inline const uint32 &GetWindowID() const { return m_WindowID; }
  
  EVENT_CLASS_TYPE(EventType::WindowMaximized)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
private:
  uint32 m_WindowID;
};

class YURITEA_API WindowShowEvent : public Event {
public:
  WindowShowEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowShowEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}
  virtual ~WindowShowEvent() = default;
  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowShowEvent  ,WindowID:" << m_WindowID;
    return ss.str();
  }
  inline const uint32 &GetWindowID() const { return m_WindowID; }
  
  EVENT_CLASS_TYPE(EventType::WindowShown)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
private:
  uint32 m_WindowID;
};

class YURITEA_API WindowHideEvent : public Event {
public:
  WindowHideEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowHideEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}
  virtual ~WindowHideEvent() = default;
  inline const uint32 &GetWindowID() const { return m_WindowID; }
  std::string ToString() const override {
    std::stringstream ss{};
    ss << "WindowHideEvent  ,WindowID: " << m_WindowID;
    return ss.str();
      
  }
  
  EVENT_CLASS_TYPE(EventType::WindowHidden)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
private:
  uint32 m_WindowID;
};

class YURITEA_API WindowEnterEvent : public Event {
public:
  WindowEnterEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowEnterEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}
  virtual ~WindowEnterEvent() = default;
  inline const uint32 &GetWindowID() const { return m_WindowID; }
  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowEnterEvent ,WindowID:" << m_WindowID;
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::WindowEnter)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
private:
  uint32 m_WindowID;
};

class YURITEA_API WindowLeaveEvent : public Event {
public:
  WindowLeaveEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowLeaveEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}
  virtual ~WindowLeaveEvent() = default;
  inline const uint32 &GetWindowID() const { return m_WindowID; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowLeaveEvent ,WindowID:" << m_WindowID;
    return ss.str();
  }
  
  EVENT_CLASS_TYPE(EventType::WindowLeave)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
private:
  uint32 m_WindowID;
};


class YURITEA_API WindowExposedEvent : public Event {
public:
  WindowExposedEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowExposedEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}
  virtual ~WindowExposedEvent() = default;
  inline const uint32 &GetWindowID() const { return m_WindowID; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowExposedEvent  ,WindowID:" << m_WindowID;
    return ss.str();
  }
  EVENT_CLASS_TYPE(EventType::WindowExposed)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
private:
  uint32 m_WindowID;
};

class YURITEA_API WindowRestoredEvent : public Event {
public:
  WindowRestoredEvent(uint32 windowID)
      : m_WindowID(windowID) {}
  WindowRestoredEvent(const SDL_Event &event)
      : m_WindowID(event.window.windowID) {}
  virtual ~WindowRestoredEvent() = default;
  inline const uint32 &GetWindowID() const { return m_WindowID; }
  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowRestoredEvent  ,WindowID:" << m_WindowID;
    return ss.str();
  }
  
  EVENT_CLASS_TYPE(EventType::WindowRestored)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryWindow)
private:
  uint32 m_WindowID;
};


class YURITEA_API DisplayEvent : public Event{
public:
  DisplayEvent(const SDL_Event& event){}
  ~DisplayEvent(){}

  std::string ToString() const override{
    return "DisplayEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::DisplayEvent)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryDisplay)


protected:

  
};


class YURITEA_API AppTerminateEvent : public Event { // 事件类 AppTerminateEvent 意思是 App 终止事件
public:
  AppTerminateEvent() = default;
  virtual ~AppTerminateEvent() = default;
  std::string ToString() const override {
    return "AppTerminateEvent";
  }
  
  EVENT_CLASS_TYPE(EventType::AppTerminate)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication | EventCategory::EventCategoryWindow)
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
