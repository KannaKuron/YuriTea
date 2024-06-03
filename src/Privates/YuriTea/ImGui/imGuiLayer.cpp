#include "YuriTea/ImGui/imGuiLayer.hpp"
#include "YuriTea/Core/keyCodes.hpp"
#include "YuriTea/Core/window.hpp"
#include "YuriTea/Events/applicationEvent.hpp"
#include "YuriTea/Events/keyEvent.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "YuriTea/Core/application.hpp"



namespace YuriTea {

ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")  {



}

ImGuiLayer::~ImGuiLayer(){

}

void ImGuiLayer::OnAttach(){
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  auto& io = ImGui::GetIO(); 
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;      // Enable Mouse Cursors
  io.ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;       // Enable SetMousePos
  
  ImGui::StyleColorsDark();
  void* window = Application::Get()->GetWindow()->GetNativeWindow();
  void* gl_context = Application::Get()->GetWindow()->GetNativeContext();
  ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(window), gl_context);
  ImGui_ImplOpenGL3_Init("#version 460");


}

void ImGuiLayer::OnDetach(){

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

}



void ImGuiLayer::OnUpdate(){
  ImGui_ImplSDL2_NewFrame();
  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  static bool show = true;

  ImGui::ShowDemoWindow(&show);
  auto& io = ImGui::GetIO();

  float time = (float)SDL_GetTicks();
  io.DeltaTime = m_Time > 0.0 ? (time - m_Time) / 1000.0 : (1.0f / 60.0f);
  m_Time = time;


  ImGui::Render();
  Window* window = Application::Get()->GetWindow();
  WindowData* m_Data = static_cast<WindowData*>(window->GetNativeData());
  glViewport(0,0,m_Data->WindowSize.x,m_Data->WindowSize.y);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void ImGuiLayer::OnEvent(Event& event){
  EventDispatcher dispatcher(event);
  if(event. GetCategoryFlags() & EventCategory::EventCategoryKeyboard){
    //dispatcher.Dispatch<KeyPressedEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnKeyEvent));
    //dispatcher.Dispatch<KeyReleasedEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnKeyEvent));
    return;
  }else
  if(event.GetCategoryFlags() & EventCategory::EventCategoryMouse || event.GetCategoryFlags() & EventCategory::EventCategoryMouseButton){
    dispatcher.Dispatch<MouseMovedEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnMouseEvent));
    dispatcher.Dispatch<MouseButtonPressedEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnMouseEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnMouseEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnMouseEvent));
    return;
  }else
  if(event.GetCategoryFlags() & EventCategory::EventCategoryWindow){
    dispatcher.Dispatch<WindowResizeEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnWindowEvent));
   // dispatcher.Dispatch<WindowLeaveEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnWindowEvent));
    return;
  }else
  if(event.GetCategoryFlags() & EventCategory::EventCategoryTextInput){
    dispatcher.Dispatch<TextInputEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnCharEvent));
    dispatcher.Dispatch<TextEditingEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnCharEvent));
    dispatcher.Dispatch<ClipboardChangedEvent>(YT_BIND_EVENT_FN(ImGuiLayer::OnCharEvent));
    return;
  }
}


bool ImGuiLayer::OnMouseEvent(Event& event){
  //区别是MouseButtonPressedEvent和MouseButtonReleasedEvent
  auto& io = ImGui::GetIO();
  if(event.GetEventType() == EventType::MouseMoved){
    MouseMovedEvent& e = static_cast<MouseMovedEvent&>(event);
    auto [x,y] = e.GetPosition();
    io.MousePos = ImVec2(x,y);
    return false;
  }
  if(event.GetEventType() == EventType::MouseButtonPressed){
    MouseButtonPressedEvent& e = static_cast<MouseButtonPressedEvent&>(event);
    io.MouseDown[e.GetButton()-1] = true;

    const auto& keymod = e.GetModifiers();

    if(keymod & KeyMod::YRT_KMOD_SHIFT)
      io.KeyShift = true;
    if(keymod & KeyMod::YRT_KMOD_CTRL)
      io.KeyCtrl = true;
    if(keymod & KeyMod::YRT_KMOD_ALT)
      io.KeyAlt = true;
    if(keymod & KeyMod::YRT_KMOD_GUI)
      io.KeySuper = true;

    std::string keymod_str {(char*)YT_TOBITS(keymod)};

    YT_CORE_INFO("KeyMod {0},{1} ", keymod_str,(uint32)keymod); 
    //in 16 jinzhi

    return false;
  }
  if(event.GetEventType() == EventType::MouseButtonReleased){
    MouseButtonReleasedEvent& e = static_cast<MouseButtonReleasedEvent&>(event);
    io.MouseDown[e.GetButton()-1] = false;
    return false;
  }
  if(event.GetEventType() == EventType::MouseScrolled){
    MouseScrolledEvent& e = static_cast<MouseScrolledEvent&>(event);
    auto [x,y] = e.GetOffset();
    io.MouseWheel += y;
    io.MouseWheelH += x;
    return false;
  }
  if(event.GetEventType() == EventType::MouseMoved){
    MouseMovedEvent& e = static_cast<MouseMovedEvent&>(event);
    auto [x,y] = e.GetPosition();
    io.MousePos = ImVec2(x,y);
    return false;
  }
  YT_CORE_WARN("Event type not supported by ImGuiLayer , OnMouseEvent");

  return false;
}

bool ImGuiLayer::OnKeyEvent(Event& event){
  auto& io = ImGui::GetIO();
  if(event.GetEventType() == EventType::KeyPressed){
    KeyPressedEvent& e = static_cast<KeyPressedEvent&>(event);
    io.KeysDown[e.GetKeyCode()] = true;
    return false;
  }
  if(event.GetEventType() == EventType::KeyReleased){
    KeyReleasedEvent& e = static_cast<KeyReleasedEvent&>(event);
    io.KeysDown[e.GetKeyCode()] = false;
    return false;
  }

  YT_CORE_WARN("Event type not supported by ImGuiLayer , OnKeyEvent");

  return false;
}

bool ImGuiLayer::OnCharEvent(Event& event) {

  return false;
}

bool ImGuiLayer::OnWindowEvent(Event& event) {
  auto& io = ImGui::GetIO();
  if(event.GetEventType() == EventType::WindowResize){
    auto& e = static_cast<WindowResizeEvent&>(event);
    auto [width,height] = e.GetSize();
    io.DisplaySize = ImVec2(width,height);
    io.DisplayFramebufferScale = ImVec2(1.0f,1.0f);
    

    return false;
  }
  if(event.GetEventType() == EventType::WindowLeave){
    io.MouseDown[0] = false;
    io.MouseDown[1] = false;
    // stop moving and input
    io.MousePos = ImVec2(-FLT_MAX,-FLT_MAX);
    io.MousePosPrev = ImVec2(-FLT_MAX,-FLT_MAX);
    io.MouseDragThreshold = 0.0f; // stop dragging
    io.MouseWheel = 0.0f;
    io.MouseWheelH = 0.0f;

    return false;
  }

  YT_CORE_WARN("Event type not supported by ImGuiLayer , OnWindowEvent");

  return false;
}

};
