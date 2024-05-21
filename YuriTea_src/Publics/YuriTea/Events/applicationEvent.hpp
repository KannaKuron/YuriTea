#pragma once
#include "YuriTea/Core/base.hpp"
#include "YuriTea/Core/core.hpp"
#include "YuriTea/Events/event.hpp"


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
