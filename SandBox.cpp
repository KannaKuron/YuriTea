

#include <YuriTea/Core/YuriTea.hpp>
#include <iostream>

#ifdef _WIN32
#define MAIN wmain
#else
#define MAIN main
#endif

class SandBox : public YuriTea::Application {

public:
  SandBox() {}

  ~SandBox() {}
};

YuriTea::Application *YuriTea::CreateApplication() { return new SandBox(); }
