


#include "Internal.hpp"
#include <SInput\SInput.hpp>

namespace SInput
{
  bool Instance_Init = false;
  Input Input_Instance;

  void Init()
  {
    if (!Instance_Init)
    {
      Instance_Init = true;
    }
  }

  void Shutdown()
  {
    Instance_Init = false;
  }

  void SwapBuffers()
  {
    if (Instance_Init)
    {
      Input_Instance.SwapBuffers();
    }
  }
}

