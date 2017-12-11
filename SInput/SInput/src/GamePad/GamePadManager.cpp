
#include "GamePadManager.hpp"

namespace SInput
{
  GamePadManager GP_Mgr;

  GamePadManager::GamePadManager()
  {
    #ifdef ENUM_NAME
    #undef ENUM_NAME
    #endif

    #define ENUM_NAME(NAME) #NAME ,
    const char* InstGPButtonEnum[] =
    {
      "INVALID_GP_BUTTON" ,
      #include <SInput\GamePad\GamePadButtonEnums.inl>
      "INVALID_ENUM"
    };

    const char* InstGPAxisEnum[] =
    {
      "INVALID_GP_AXIS" ,
      #include <SInput\GamePad\GamePadAxisEnums.inl>
      "INVALID_ENUM"
    };
    #undef ENUM_NAME

    for (int i = -1; i < GAMEPAD::NUMBEROFGPBUTTONS; ++i)
    {
      ButtonEnum.addValue(i, InstGPButtonEnum[i+1]);
    }

    for (int i = -1; i < GAMEPAD::NUMBEROFGPAXIS; ++i)
    {
      AxisEnum.addValue(i, InstGPAxisEnum[i+1]);
    }
  }

  GamePadManager::~GamePadManager()
  {}

  void GamePadManager::SwapBuffers()
  {
    for (size_t i = 0; i < GAMEPAD::NUMBEROFGAMEPADS; ++i)
    {
      gamepad[i].SwapBuffers();
    }

    for (auto& it : v_gamepads)
    {
      it.second.SwapBuffers();
    }
  }

  GamePadDevice* GamePadManager::GetGamepad(unsigned num)
  {
    if (num < GAMEPAD::NUMBEROFGAMEPADS)
    {
      return &gamepad[num];
    }

    return nullptr;
  }

  GamePadDevice* GamePadManager::GetVGamepad(unsigned num)
  {
    return &v_gamepads[num];
  }
}