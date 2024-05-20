#pragma once
#include "YuriTea/Core/core.hpp"
#include "YuriTea/Events/Event.hpp"

#ifdef YuriTea_DEBUG
#include <sstream>
#endif

namespace YuriTea {

class YURITEA_API WindowResizeEvent : public Event {
public:
  WindowResizeEvent(uint32 width, uint32 height)
      : m_Size{width,height} {}
  virtual ~WindowResizeEvent() = default;

  inline const uint32 &GetWidth() const { return m_Size.x; }
  inline const uint32 &GetHeight() const { return m_Size.y; }

  inline const Vector2<uint32> &GetSize() const { return m_Size; }

#ifdef YuriTea_DEBUG
  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << m_Size.x << "," << m_Size.y;
    return ss.str();
  }
#endif

EVENT_CLASS_TYPE(EventType::WindowResize)
EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

private:
  Vector2<uint32> m_Size;
};

class YURITEA_API WindowCloseEvent : public Event {
  public:
    WindowCloseEvent() = default;
    virtual ~WindowCloseEvent() = default;

#ifdef YuriTea_DEBUG
  std::string ToString() const override {
    return "WindowCloseEvent";
  }
#endif

  EVENT_CLASS_TYPE(EventType::WindowClose)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class YURITEA_API AppTickEvent : public Event {
  public:
    AppTickEvent() = default;
    virtual ~AppTickEvent() = default;

  #ifdef YuriTea_DEBUG
  std::string ToString() const override {
    return "AppTickEvent";
  }
  #endif
  
  EVENT_CLASS_TYPE(EventType::AppTick)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

};


class YURITEA_API AppUpdateEvent : public Event {
  public:
    AppUpdateEvent() = default;
    virtual ~AppUpdateEvent() = default;

  #ifdef YuriTea_DEBUG
  std::string ToString() const override {
    return "AppUpdateEvent";
  }
  #endif
  
  EVENT_CLASS_TYPE(EventType::AppUpdate)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};



class YURITEA_API AppRenderEvent : public Event {
  public:
    AppRenderEvent() = default;
    virtual ~AppRenderEvent() = default;
  #ifdef YuriTea_DEBUG
  std::string ToString() const override {
    return "AppRenderEvent";
  }
  #endif
  
  EVENT_CLASS_TYPE(EventType::AppRender)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};


} // namespace YuriTea
