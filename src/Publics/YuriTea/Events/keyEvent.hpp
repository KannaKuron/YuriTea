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
  inline const uint32 &GetWindowID() const { return m_WindowID; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyEvent: " << m_KeyCode;
    return ss.str();
  }

  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard |
                       EventCategory::EventCategoryInput)
protected:
  KeyEvent(KeyCode code, KeyMod mod ,uint32 ID) : m_KeyCode(code), m_Mod(mod), m_WindowID(ID) {}
  virtual ~KeyEvent() = default;

  KeyCode m_KeyCode{YRT_UNKNOWN};
  KeyMod m_Mod{YRT_KMOD_NONE};
  uint32 m_WindowID{0};
};

class YURITEA_API KeyPressedEvent : public KeyEvent {
public:
  KeyPressedEvent(const SDL_Event& event)
      : KeyEvent(static_cast<KeyCode>(event.key.keysym.sym), static_cast<KeyMod>(event.key.keysym.mod),event.key.windowID) , m_RepeatCount(event.key.repeat) {}
  KeyPressedEvent(KeyCode code, KeyMod mod, uint32 repeatCount ,uint32 windowID)
      : KeyEvent(code, mod,windowID), m_RepeatCount(repeatCount) {}
  ~KeyPressedEvent() = default;

  inline const uint32 &GetRepeatCount() const { return m_RepeatCount; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_KeyCode << " ,KeyModif: " << m_Mod << " ("
      << m_RepeatCount << " repeats)" << " (" << m_WindowID << " windowID)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::KeyPressed)

private:
  uint32 m_RepeatCount{0};
};

class YURITEA_API KeyReleasedEvent : public KeyEvent {
public:
  KeyReleasedEvent(KeyCode code, KeyMod mod ,uint32 windowID) : KeyEvent(code, mod,windowID) {}
  KeyReleasedEvent(const SDL_Event& event)
      : KeyEvent(static_cast<KeyCode>(event.key.keysym.sym), static_cast<KeyMod>(event.key.keysym.mod),event.key.windowID) {}
  ~KeyReleasedEvent() = default;

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_KeyCode << "KeyModif: " << m_Mod << " ("
       << m_WindowID << " windowID)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::KeyReleased)
protected:
};


class YURITEA_API TextInputEvent : public Event {
public:
  TextInputEvent(const std::string &text ,uint32 windowID) : m_Text(text), m_WindowID(windowID) {}
  TextInputEvent(const SDL_Event& event)
      : m_Text(event.text.text), m_WindowID(event.text.windowID) {}
  ~TextInputEvent() = default;
  inline const std::string& GetText() const { return m_Text; }
  inline const uint32& GetWindowID() const { return m_WindowID; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "TextInputEvent: " << m_Text << " ,WindowID: " << m_WindowID;
    return ss.str();
  }

  EVENT_CLASS_TYPE(EventType::TextInput)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard |
                      EventCategory::EventCategoryInput | EventCategory::EventCategoryTextInput)

protected:
  std::string m_Text;
  uint32 m_WindowID{0};
};

class YURITEA_API TextEditingEvent : public Event {
public:
    TextEditingEvent(const std::string &text, int start, int length, uint32 windowID)
        : m_Text(text), m_Start(start), m_Length(length) , m_WindowID(windowID) {}
    TextEditingEvent(const SDL_Event& event)
      : m_Text(event.edit.text), m_Start(event.edit.start), m_Length(event.edit.length) , m_WindowID(event.edit.windowID) {}
    ~TextEditingEvent() = default;
    inline const std::string &GetText() const { return m_Text; }
    inline const int &GetStart() const { return m_Start; }
    inline const int &GetLength() const { return m_Length; }
    inline const uint32 &GetWindowID() const { return m_WindowID; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "TextEditingEvent: " << m_Text << " Start: " << m_Start
        << " Length: " << m_Length << " ,WindowID: " << m_WindowID;
      return ss.str();
    }
    EVENT_CLASS_TYPE(EventType::TextEditing)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard |
                        EventCategory::EventCategoryInput | EventCategory::EventCategoryTextInput)

protected:
    std::string m_Text;
    int m_Start;
    int m_Length;
    uint32 m_WindowID{0};
};

class YURITEA_API ClipboardChangedEvent : public Event {
public:
    ClipboardChangedEvent(const std::string &text, int start, int length, uint32 windowID)
      : m_Text(text), m_Start(start), m_Length(length) , m_WindowID(windowID) {}

    ClipboardChangedEvent(const SDL_Event& event)
      : m_Text(event.edit.text), m_Start(event.edit.start), m_Length(event.edit.length) , m_WindowID(event.edit.windowID) {}
    ~ClipboardChangedEvent() = default;
    inline const std::string &GetText() const { return m_Text; }
    inline const int &GetStart() const { return m_Start; }
    inline const int &GetLength() const { return m_Length; }
    inline const uint32 &GetWindowID() const { return m_WindowID; }

    std::string ToString() const override {
      std::stringstream ss;
      ss << "ClipboardChangedEvent: " << m_Text << " Start: " << m_Start
        << " Length: " << m_Length << " ,WindowID: " << m_WindowID;
      return ss.str();
    }
    EVENT_CLASS_TYPE(EventType::ClipboardChanged)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryTextInput)
protected:
  std::string m_Text;
  int m_Start;
  int m_Length;
  uint32 m_WindowID{0};

  

};


} // namespace YuriTea
