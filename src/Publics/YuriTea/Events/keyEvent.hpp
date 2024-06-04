#pragma once
#include "YuriTea/Core/base.hpp"
#include "YuriTea/Core/keyCodes.hpp"
#include "YuriTea/Events/event.hpp"

using namespace YuriTea::Key;

namespace YuriTea {

class YURITEA_API KeyEvent : public Event {
public:
  inline const KeyCode &GetKeyCode() const { return m_KeyCode; }
  inline const KeyMod &GetMod() const { return m_Mod; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyEvent: " << m_KeyCode;
    return ss.str();
  }

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

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_KeyCode << " ,KeyModif: " << m_Mod << " ("
       << m_RepeatCount << " repeats)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::KeyPressed)

private:
  uint32 m_RepeatCount{0};
};

class YURITEA_API KeyReleasedEvent : public KeyEvent {
public:
  KeyReleasedEvent(KeyCode code, KeyMod mod) : KeyEvent(code, mod) {}
  ~KeyReleasedEvent() = default;

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_KeyCode << "KeyModif: " << m_Mod;
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::KeyReleased)
protected:
};


class YURITEA_API TextInputEvent : public Event {
public:
  TextInputEvent(const std::string &text) : m_Text(text) {}
  ~TextInputEvent() = default;
  const  std::string& GetText() const { return m_Text; }
  std::string ToString() const override {
    std::stringstream ss;
    ss << "TextInputEvent: " << m_Text;
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::TextInput)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard |
                      EventCategory::EventCategoryInput | EventCategory::EventCategoryTextInput)

protected:
  std::string m_Text;
};

class YURITEA_API TextEditingEvent : public Event {
public:
    TextEditingEvent(const std::string &text, int start, int length)
        : m_Text(text), m_Start(start), m_Length(length) {}
    ~TextEditingEvent() = default;
    const std::string &GetText() const { return m_Text; }
    const int &GetStart() const { return m_Start; }
    const int &GetLength() const { return m_Length; }
    std::string ToString() const override {
      std::stringstream ss;
      ss << "TextEditingEvent: " << m_Text << " Start: " << m_Start
         << " Length: " << m_Length;
      return ss.str();
    }
    EVENT_CLASS_TYPE(EventType::TextEditing)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard |
                        EventCategory::EventCategoryInput | EventCategory::EventCategoryTextInput)

protected:
    std::string m_Text;
    int m_Start;
    int m_Length;

};

class YURITEA_API ClipboardChangedEvent : public Event {
public:
    ClipboardChangedEvent(const std::string &text, int start, int length)
      : m_Text(text), m_Start(start), m_Length(length) {}
    ~ClipboardChangedEvent() = default;
    const std::string &GetText() const { return m_Text; }
    const int &GetStart() const { return m_Start; }
    const int &GetLength() const { return m_Length; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "ClipboardChangedEvent";
      return ss.str();
    }
    EVENT_CLASS_TYPE(EventType::ClipboardChanged)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryTextInput)
protected:
  std::string m_Text;
  int m_Start;
  int m_Length;

  

};


} // namespace YuriTea
