
#include <YuriTea/Core/YuriTea.hpp>


class ExampleLayer : public YuriTea::Layer {
public:
  ExampleLayer() : Layer("Example") {}

  void OnUpdate() override {
    YT_INFO("ExampleLayer::Update");
  }

  void OnEvent(YuriTea::Event &event) override {
    YT_WARN("{0}", event.ToString());
  }

};



class SandBox : public YuriTea::Application {

public:
  SandBox() {
    PushLayer(new ExampleLayer());

  }

  ~SandBox() {

  }
};

YuriTea::Application *YuriTea::CreateApplication() { return new SandBox(); }
