#include "YuriTea/ImGui/imGuiLayer.hpp"
#include "YuriTea/Core/base.hpp"
#include "YuriTea/Platform/Windows/windowsWindow.hpp"
#include "imgui/imgui.h"



namespace YuriTea {

ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")  {

}


void ImGuiLayer::OnAttach(){

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  auto& io = ImGui::GetIO(); 
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;      // Enable Mouse Cursors
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;       // Enable SetMousePos

  

  float32 font_size = 16.0f;

#ifdef Yuritea_Release
  io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Medium.ttf", font_size);
  io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Medium.ttf", font_size);
#endif

  ImGui::StyleColorsDark();

  void* window = Application::Get()->GetWindow()->GetNativeWindow();
  void* gl_context = Application::Get()->GetWindow()->GetNativeContext();

  ImGuiStyle& style = ImGui::GetStyle();

  if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
    // 窗口圆角半径
    style.WindowRounding = 0.0f;
    // 窗口背景透明度
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;

  }

	SetDarkThemeColors();

  ImGui_ImplSDL2_InitForOpenGL(static_cast<SDL_Window*>(window), gl_context);
  ImGui_ImplOpenGL3_Init("#version 460");

}

void ImGuiLayer::OnDetach(){

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

}

void ImGuiLayer::OnEvent(Event& event) {

  ImGui_ImplSDL2_YuriTea_ProcessEvent(&event);

  if(m_BlockEvents){
    ImGuiIO& io = ImGui::GetIO();
    event |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
    event |= event.IsInCategory(EventCategoryMouseButton) & io.WantCaptureKeyboard;
    event |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;

  }
}



void ImGuiLayer::Begin(){
  ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

}

void ImGuiLayer::End(){

  ImGuiIO& io = ImGui::GetIO();
  const Application* app = Application::Get();
  auto window = app->GetWindow();

  io.DisplaySize = ImVec2(window->GetWidth(), window->GetHeight());

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


  if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
    SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
  }

  //  ImGui::EndFrame();
}


void ImGuiLayer::OnUpdate(){
  Begin();
  static bool show = true;
  //show demo window
  
  ImGui::ShowDemoWindow(&show);

  

  End();
}

void ImGuiLayer::SetDarkThemeColors(){

		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		
		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
}

uint32 ImGuiLayer::GetActiveWidgetID() const {
  return ImGui::GetActiveID();
}

}
