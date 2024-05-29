#include "YuriTea/ImGui/imGuiLayer.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "YuriTea/Core/application.hpp"


namespace YuriTea {

ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer") , io(nullptr) {



}

ImGuiLayer::~ImGuiLayer(){

}

void ImGuiLayer::OnAttach(){
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = &ImGui::GetIO(); 
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io->ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;      // Enable Mouse Cursors
  io->ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;       // Enable SetMousePos
  
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

  io = nullptr;
}



void ImGuiLayer::OnUpdate(){
  ImGui_ImplSDL2_NewFrame();
  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  static bool show = true;

  ImGui::ShowDemoWindow(&show);

  float time = (float)SDL_GetTicks();
  io->DeltaTime = m_Time > 0.0 ? (time - m_Time) / 1000.0 : (1.0f / 60.0f);
  m_Time = time;


  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void ImGuiLayer::OnEvent(Event& event){

}


};
