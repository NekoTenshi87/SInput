#pragma once

#include "..\DeviceManager.hpp"
#include <SInput\Enum.hpp>
#include <SInput\GamePad\GamePad.hpp>

#include <unordered_map>

namespace SInput
{
  class GamePadManager : public DevMgrPtr
  {
  public:
    GamePadManager();
    ~GamePadManager();

    void SwapBuffers();

    void RunMonkey();

    GamePadDevice* GetGamepad(unsigned num);

    GamePadDevice* GetVGamepad(unsigned num);

    Enum ButtonEnum{ "GamePad Button Enums" };
    Enum AxisEnum{ "GamePad Axis Enums" };

  private:

    GamePadDevice gamepad[GAMEPAD::NUMBEROFGAMEPADS];
    std::unordered_map<unsigned, GamePadDevice> v_gamepads;
  };

  extern GamePadManager GP_Mgr;
}