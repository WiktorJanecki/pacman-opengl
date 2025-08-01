#pragma once

class GLFWwindow;

class GameLoop {
public:
  GameLoop();

private:
  GLFWwindow *m_window;
  int m_frames{0};
  double m_timer{0.0};

  auto loop() -> void;
};
