#pragma once

extern YuriTea::Application *YuriTea::CreateApplication();

int main(int32 argc, char **argv) {
  YuriTea::Log::Init();

  auto app = YuriTea::CreateApplication();
  app->Run();
  delete app;
  return 0;
}
