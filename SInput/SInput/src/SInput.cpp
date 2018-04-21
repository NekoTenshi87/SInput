


#include "Internal.hpp"
#include <SInput\SInput.hpp>
#include <SInput\NGram.hpp>
#include <SInput\Serialize.hpp>
#include <stdlib.h>
#include <time.h>

namespace SInput
{
  bool Instance_Init = false;
  Input Input_Instance;
  float currTime;
  bool first_time = true;

  void Init()
  {
    if (!Instance_Init)
    {
      Instance_Init = true;
      std::srand(time(NULL));
      currTime = 0.0f;
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
      currTime += 1.0f / 60.0f;
    }
  }

  void RunMonkey()
  {
    if (Instance_Init)
    {
      Input_Instance.RunMonkey();
    }
  }

  void EnableNGram(bool enable)
  {
    if (enable && first_time)
    {
      first_time = false;
      
      N_Gram.AddKeysToNGrams(serialize.GetDeviceKeyData(DEVICETYPE::BUILT_IN_DEVICE, 0));
      N_Gram.AddMouseToNGrams(serialize.GetDeviceMouseData(DEVICETYPE::BUILT_IN_DEVICE, 0));
      N_Gram.AddGamePadToNGrams(serialize.GetDeviceGamePadData(DEVICETYPE::BUILT_IN_DEVICE, 0));
      N_Gram.CalcUniGramKeys();
      N_Gram.CalcUniGramMouse();
      N_Gram.CalcUniGramGamePad();
    }
    else if (!enable)
    {
      first_time = true;
    }
  }
}

