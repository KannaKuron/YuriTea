#pragma once

#include "YuriTea/Core/base.hpp"
#include <SDL2/SDL_events.h>

namespace YuriTea {

enum class EventType : uint32 {
  TouchMove = 0, 
  MouseMove, 

  None = 0, // 0
  Quit = 0x100, // 256 退出事件 如用户正常关闭
  AppTerminate, // app退出 如 ctrl+c 关机
  AppLowMemory, // 内存不足
  AppWillEnterBackground, // app将进入后台
  AppDidEnterBackground, // app已经进入后台
  AppWillEnterForeground, // app将进入前台
  AppDidEnterForeground, // app已经进入前台
  AppTick, // app每一帧
  AppUpdate, // app每一次更新
  AppRender, // app每一次渲染
  
  LocaleChanged, // 语言改变

  DisplayEvent = 0x150, // 336 显示事件
  
  
  WindowEvent = 0x200, // 512 窗口事件
  SysWMEvent , 
  WindowClose, // ok
  WindowResize, // ok
  WindowFocus, // ok
  WindowLostFocus, // ok
  WindowMoved, // ok
  WindowMinimized,  // ok
  WindowMaximized,  // ok
  WindowShown,  // ok
  WindowHidden,  // ok
  WindowEnter,  // ok
  WindowLeave,   // ok
  WindowExposed, // ok
  WindowRestored, // ok

  KeyPressed = 0x300,  // 按下 键盘
  KeyReleased, // 松开
  TextEditing, // ok
  TextInput, // ok
  KeymapChanged,          /**< 由于系统事件（如输入语言或键盘布局更改）导致的按键映射更改 */
  TextEditingExt,       /**< 扩展键盘文本编辑（组合） */


  MouseMoved = 0x400, //鼠标移动
  MouseButtonPressed, // ok
  MouseButtonReleased, // ok
  MouseScrolled ,

  JoyAxisMotion = 0x600,          /**< 摇杆轴运动 */
  JoyBallMotion,          /**< 摇杆轨迹球运动 */
  JoyHatMotion,           /**< 摇杆帽位置变化 */
  JoyButtonDown,          /**< 摇杆按钮按下 */
  JoyButtonUp,            /**< 摇杆按钮释放 */
  JoyDeviceAdded,         /**< 系统中插入了一个新的摇杆 */
  JoyDeviceRemoved,       /**< 已打开的摇杆被移除 */
  JoyBatteryUpdated,      /**< 摇杆电池电量变化 */

  /* 游戏控制器事件 */
  ControllerAxisMotion  = 0x650, /**< 游戏控制器轴运动 */
  ControllerButtonDown,          /**< 游戏控制器按钮按下 */
  ControllerButtonUp,            /**< 游戏控制器按钮释放 */
  ControllerDeviceAdded,         /**< 系统中插入了一个新的游戏控制器 */
  ControllerDeviceRemoved,       /**< 已打开的游戏控制器被移除 */
  ControllerDeviceRemapped,      /**< 控制器映射已更新 */
  ControllerTouchpadDown,        /**< 游戏控制器触摸板被触摸 */
  ControllerTouchpadMotion,      /**< 游戏控制器触摸板手指移动 */
  ControllerTouchpadUp,          /**< 游戏控制器触摸板手指抬起 */
  ControllerSensorUpdate,        /**< 游戏控制器传感器更新 */
  ControllerUpdateCompleteReservedForSDL3, /**< 为 SDL3 保留的控制器更新完成事件 */
  ControllerSteamHandleUpdated,  /**< 游戏控制器 Steam 句柄已更改 */
  
  // 触摸
  FingerDown = 0x700, /**< 触摸按下 */
  FingerUp,                /**< 触摸抬起 */
  FingerMotion,            /**< 触摸移动 */

  /* 手势事件 */
  DollarGesture   = 0x800, /**< 单次手势 */
  DollarRecord,            /**< 手势记录 */
  MultiGesture,            /**< 多点手势 */
  
  // 剪切板变化
  ClipboardChanged = 0x900,

  /* 拖放事件 */
  DropFile        = 0x1000, /**< 请求打开文件 */
  DropText,                 /**< 文本拖放事件 */
  DropBegin,                /**< 新的拖放集合开始（文件名为 NULL） */
  DropComplete,             /**< 当前拖放集合完成（文件名为 NULL） */


  /* 音频热插拔事件 */
  AudioDeviceAdded = 0x1100, /**< 有新的音频设备可用 */
  AudioDeviceRemoved,       /**< 音频设备已移除 */

  /* 传感器事件 */
  SensorUpdate = 0x1200,     /**< 传感器已更新 */

  /* 渲染事件 */
  RenderTargetsReset = 0x2000, /**< 渲染目标已重置，它们的内容需要更新 */
  RenderDeviceReset,           /**< 设备已重置，所有纹理需要重新创建 */

  /* 内部事件 */
  PollSentinel = 0x7F00, /**< 表示事件轮询周期结束 */


  CustomEvent = 0x8000
};

enum EventCategory : uint32 {
  EventCategoryAll = 0xFF,          // 11111111 所有事件
  None = 0, // 00000000 None event
  EventCategoryApplication = BIT(0), // BIT(0) = 00000001 应用事件
  EventCategoryInput = BIT(1),       // BIT(1) = 00000010 输入事件
  EventCategoryKeyboard = BIT(2),    // BIT(2) = 00000100 键盘事件
  EventCategoryMouse = BIT(3),       // BIT(3) = 00001000 鼠标事件
  EventCategoryMouseButton = BIT(4), // BIT(4) = 00010000 鼠标按键事件
  EventCategoryWindow = BIT(5),      // BIT(5) = 00100000 窗口事件
  EventCategoryTextInput = BIT(6),   // BIT(6) = 01000000 文本输入事件
  EventCategoryJoystick = BIT(7),    // BIT(7) = 10000000 手柄事件
  EventCategoryGameController = BIT(8), // BIT(8) = 100000000 游戏控制器事件
  EventCategoryDisplay = BIT(9),       // BIT(8) = 100000000 显示事件
  EventCategoryCustom = BIT(10)       // BIT(8) = 100000000 自定义事件
};

#define EVENT_CLASS_TYPE(type)                                                 \
  static EventType GetStaticType() { return type; }                            \
  virtual EventType GetEventType() const override { return GetStaticType(); }  \
  virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                         \
  virtual uint32 GetCategoryFlags() const override { return category; }



// =========================================

// the Event class is a base class for all events in the engine


















// ============== Event Class ==============
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

  inline const bool& IsHandled() const { return m_Handled; }

  bool operator |= (const bool& b) { return m_Handled |= b; }
  bool operator |= (const bool&& b) { return m_Handled |= b; }


public:
  Event() = default;          // 默认构造函数
  virtual ~Event() = default; // 默认析构函数

protected:
  bool m_Handled = false;
};


class YURITEA_API UnKnownEvent : public Event {
public:
  UnKnownEvent() = default;
  virtual ~UnKnownEvent() = default;
  std::string ToString() const override { return "UnKnownEvent Can't Dispatch"; }

  EVENT_CLASS_TYPE(EventType::None)
  EVENT_CLASS_CATEGORY(EventCategory::None)
};




class YURITEA_API EventDispatcher {
  template <typename T> using EventFn = std::function<bool(T &)>;

public:
  EventDispatcher(Event &event) : m_Event(event) {}

  template <typename T> bool Dispatch(EventFn<T> func) {
    if (m_Event.GetEventType() == T::GetStaticType()) {
      m_Event |= func(*(T *)&m_Event);
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
