#pragma once
#include "YuriTea/Core/base.hpp"
#include "YuriTea/Core/keyCodes.hpp"
#include "YuriTea/Events/event.hpp"

namespace YuriTea {

class YURITEA_API ControllerEvent : public Event {
public:
  ControllerEvent() = default;
  virtual ~ControllerEvent() = default;
  
  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "ControllerEvent";
    return ss.str();
  }

  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryGameController |
                       EventCategory::EventCategoryInput)
};


class YURITEA_API ControllerAddedEvent : public ControllerEvent {
public:
  ControllerAddedEvent() = default;
  virtual ~ControllerAddedEvent() = default;

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "ControllerAddedEvent";
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::ControllerDeviceAdded)

};

class YURITEA_API ControllerRemovedEvent : public ControllerEvent {
public:
  ControllerRemovedEvent() = default;
  virtual ~ControllerRemovedEvent() = default;

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "ControllerRemovedEvent";
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::ControllerDeviceRemoved)
};


} // namespace YuriTea
