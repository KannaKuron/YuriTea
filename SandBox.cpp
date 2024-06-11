#include <YuriTea/Core/YuriTea.hpp>


class ExampleLayer : public YuriTea::Layer {
public:
  ExampleLayer() : Layer("Example") {}

  void OnUpdate() override {
  }

  void OnEvent(YuriTea::Event &event) override {
  }

};



class SandBox : public YuriTea::Application {

public:
  SandBox() {
    auto temp1 = new ExampleLayer();
    PushLayer(std::move(temp1));

    auto temp2 = new YuriTea::ImGuiLayer();
    PushLayer(std::move(temp2));
      

  }

  ~SandBox() {

  }
};

YuriTea::Application *YuriTea::CreateApplication() { return new SandBox(); }
