


#include "Internal.hpp"
#include <SInput\SInput.hpp>

namespace SInput
{
  bool Instance_Init = false;

  void Init()
  {
    if (!Instance_Init)
    {
      Instance_Init = true;

      //Input_Instance.Init();

      // Init ImGui

    }


  }

  void Shutdown()
  {
    Instance_Init = false;

    // Close ImGui


  }

  void SwapBuffers()
  {
    if (Instance_Init)
    {
      Input_Instance.SwapBuffers();
    }
  }

}

