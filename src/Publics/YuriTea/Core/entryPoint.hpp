#pragma once
extern YuriTea::Application *YuriTea::CreateApplication();


#ifdef YuriTea_Platform_Windows
#define MAIN SDL_main
#else
#define MAIN SDL_main
#endif


int MAIN(int argc, char* argv[]) {


  #ifdef YuriTea_DEBUG
  std::cerr << "YuriTe Engine Debug" << std::endl;
  YuriTea::Log::Init();
  #endif
  #ifdef YuriTea_RELEASE
  #ifdef  YuriTea_Platform_Windows


  #endif
  #endif


  auto app = YuriTea::CreateApplication();
  YuriTea::Application::Start(app);

  std::set_terminate([]() {
    std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
    std::abort();
  });
    
  return YuriTea::Application::Close();
}
