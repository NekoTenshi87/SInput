#pragma once

#include <SInput\Input.hpp>

namespace SInput
{
  void Init();

  void Shutdown();

  void SwapBuffers();

  void RunMonkey();

  void EnableNGram(bool enable);

  extern float currTime;
}
