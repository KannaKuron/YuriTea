#pragma once
#include "YuriTea/Core/keyCodes.hpp"
#include "YuriTea/Events/event.hpp"

using namespace YuriTea::Key;

namespace YuriTea {

class YURITEA_API KeyEvent : public Event {
public:
  inline const KeyCode &GetKeyCode() const { return m_KeyCode; }
  inline const KeyMod &GetMod() const { return m_Mod; }

#ifdef YuriTea_DEBUG
  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyEvent: " << m_KeyCode;
    return ss.str();
  }
#endif // !YuriTea_DEBUG

  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard |
                       EventCategory::EventCategoryInput)
protected:
  KeyEvent(KeyCode code, KeyMod mod) : m_KeyCode(code), m_Mod(mod) {}
  virtual ~KeyEvent() = default;

  KeyCode m_KeyCode{YRT_UNKNOWN};
  KeyMod m_Mod{YRT_KMOD_NONE};
};

class YURITEA_API KeyPressedEvent : public KeyEvent {
public:
  KeyPressedEvent(KeyCode code, KeyMod mod, uint32 repeatCount)
      : KeyEvent(code, mod), m_RepeatCount(repeatCount) {}
  ~KeyPressedEvent() = default;

  inline const uint32 &GetRepeatCount() const { return m_RepeatCount; }

#ifdef YuriTea_DEBUG
  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_KeyCode << "KeyModif: " << m_Mod << " ("
       << m_RepeatCount << " repeats)";
    return ss.str();
  }
#endif

  EVENT_CLASS_TYPE(EventType::KeyPressed)

private:
  uint32 m_RepeatCount{0};
};

class YURITEA_API KeyReleasedEvent : public KeyEvent {
public:
  KeyReleasedEvent(KeyCode code, KeyMod mod) : KeyEvent(code, mod) {}
  ~KeyReleasedEvent() = default;

#ifdef YuriTea_DEBUG
  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_KeyCode << "KeyModif: " << m_Mod;
    return ss.str();
  }
#endif

  EVENT_CLASS_TYPE(EventType::KeyReleased)
protected:
};

} // namespace YuriTea
