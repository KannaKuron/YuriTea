#pragma once

extern YuriTea::Application *YuriTea::CreateApplication();

int main(int32 argc, char **argv) {
  YuriTea::Log::Init();

  auto app = YuriTea::CreateApplication();

  YuriTea::Application::Start(app);
  
  return YuriTea::Application::Close();
}
