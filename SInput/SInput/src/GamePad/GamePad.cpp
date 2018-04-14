
#include "GamePadManager.hpp"
#include <SInput\GamePad\GamePad.hpp>
#include <iostream>

namespace SInput
{
  GamePadDevice::GamePadDevice()
  {}

  GamePadDevice::~GamePadDevice()
  {}

  void GamePadDevice::Print()
  {
    std::cout << "Connected | Axis1 | Axis2 | Axis3 | Axis4 | Axis5 | Axis6" << std::endl;
    std::cout << currGP.Connection.state << " | " << currGP.Axis[0].delta << " | " << currGP.Axis[1].delta << " | "
              << currGP.Axis[2].delta << " | " << currGP.Axis[3].delta << " | " 
              << currGP.Axis[4].delta << " | " << currGP.Axis[5].delta << " | " << std::endl;
    std::cout << "B1 |B2 |B3 |B4 |B5 |B6 |B7 |B8 |B9 |B10|B11|B12|B13|B14|B15|B16" << std::endl;
    std::cout << " " << currGP.Button[0].state << " | " << currGP.Button[1].state << " | " << currGP.Button[2].state << " | "
              << currGP.Button[3].state << " | " << currGP.Button[4].state << " | " << currGP.Button[5].state << " | "
              << currGP.Button[6].state << " | " << currGP.Button[7].state << " | " << currGP.Button[8].state << " | "
              << currGP.Button[9].state << " | " << currGP.Button[10].state << " | " << currGP.Button[11].state << " | "
              << currGP.Button[12].state << " | " << currGP.Button[13].state << " | " << currGP.Button[14].state << " | "
              << currGP.Button[15].state << std::endl;
  }

  void GamePadDevice::PrintConnection(int gp_num)
  {
    std::clog << "GamePad: PAD_" << gp_num << " was " << (currGP.Connection.state == 1 ? "Connected." : "Released.") << std::endl;
  }

  void GamePadDevice::PrintButton(int gp_num, GAMEPAD::BUTTON button)
  {
    std::clog << "GamePad: PAD_" << gp_num << " " << GetGPButtonEnum().toStr(button) << " was " << (currGP.Button[button].state == 1 ? "Pressed." : "Released.") << std::endl;
  }

  void GamePadDevice::PrintAxis(int gp_num, GAMEPAD::AXIS axis)
  {
    std::clog << "GamePad: PAD_" << gp_num << " " << GetGPAxisEnum().toStr(axis) << ": " << currGP.Axis[axis].delta << std::endl;
  }

  void GamePadDevice::SwapBuffers()
  {
    prevGP = currGP;
  }

  bool GamePadDevice::ButtonPressed(GAMEPAD::BUTTON button)
  {
    if (button > GAMEPAD::UNKNOWN_BUTTON && button < GAMEPAD::NUMBEROFGPBUTTONS)
    {
      if (currGP.Button[button].state)
      {
        return true;
      }
    }

    return false;
  }

  bool GamePadDevice::ButtonTriggered(GAMEPAD::BUTTON button)
  {
    if (button > GAMEPAD::UNKNOWN_BUTTON && button < GAMEPAD::NUMBEROFGPBUTTONS)
    {
      if (currGP.Button[button].state && !prevGP.Button[button].state)
      {
        return true;
      }
    }

    return false;
  }

  bool GamePadDevice::ButtonHeld(GAMEPAD::BUTTON button)
  {
    if (button > GAMEPAD::UNKNOWN_BUTTON && button < GAMEPAD::NUMBEROFGPBUTTONS)
    {
      if (currGP.Button[button].state && prevGP.Button[button].state)
      {
        return true;
      }
    }

    return false;
  }

  bool GamePadDevice::ButtonReleased(GAMEPAD::BUTTON button)
  {
    if (button > GAMEPAD::UNKNOWN_BUTTON && button < GAMEPAD::NUMBEROFGPBUTTONS)
    {
      if (!currGP.Button[button].state && prevGP.Button[button].state)
      {
        return true;
      }
    }

    return false;
  }

  bool GamePadDevice::IsConnected()
  {
    return currGP.Connection.state;
  }

  bool GamePadDevice::IsPluggedIn()
  {
    if (currGP.Connection.state && !prevGP.Connection.state)
    {
      return true;
    }

    return false;
  }

  bool GamePadDevice::IsUnplugged()
  {
    if (!currGP.Connection.state && prevGP.Connection.state)
    {
      return true;
    }

    return false;
  }

  float GamePadDevice::GetAxis(GAMEPAD::AXIS axis)
  {
    if (axis > GAMEPAD::UNKNOWN_AXIS && axis < GAMEPAD::NUMBEROFGPAXIS)
    {
      return currGP.Axis[axis].delta;
    }

    return 0.0f;
  }

  void GamePadDevice::UpdateButton(GAMEPAD::BUTTON button, GAMEPAD::ACTION action)
  {
    if (action > GAMEPAD::UNKNOWN_ACTION)
    {
      if (button > GAMEPAD::UNKNOWN_BUTTON && button < GAMEPAD::NUMBEROFGPBUTTONS)
      {
        currGP.Button[button].state = action;
      }
    }
  }

  void GamePadDevice::UpdateAxis(GAMEPAD::AXIS axis, float delta)
  {
    if (axis > GAMEPAD::UNKNOWN_AXIS && axis < GAMEPAD::NUMBEROFGPAXIS)
    {
      currGP.Axis[axis].delta = delta;
    }
  }

  void GamePadDevice::UpdateConnection(GAMEPAD::STATUS status)
  {
    switch (status)
    {
      case GAMEPAD::CONNECTED:
      {
        currGP.Connection.state = true;
      }
      break;

      case GAMEPAD::DISCONNECTED:
      {
        currGP.Connection.state = false;
      }
      break;

      default:
      break;

    }
  }

  void GamePadDevice::BindButton(int name_id, GAMEPAD::BUTTON button)
  {
    button_binding.addValue(name_id, button);
  }

  void GamePadDevice::BindAxis(int name_id, GAMEPAD::AXIS axis)
  {
    axis_binding.addValue(name_id, axis);
  }

  void GamePadDevice::UnBindButton(int name_id)
  {
    button_binding.addValue(name_id, GAMEPAD::BUTTON::UNKNOWN_BUTTON);
  }

  void GamePadDevice::UnBindAxis(int name_id)
  {
    axis_binding.addValue(name_id, GAMEPAD::AXIS::UNKNOWN_AXIS);
  }

  GAMEPAD::BUTTON GamePadDevice::getBindButton(const int name_id) const
  {
    return static_cast<GAMEPAD::BUTTON>(button_binding.toType(name_id));
  }

  GAMEPAD::AXIS GamePadDevice::getBindAxis(const int name_id) const
  {
    return static_cast<GAMEPAD::AXIS>(axis_binding.toType(name_id));
  }

  int GamePadDevice::getBindButtonID(const GAMEPAD::BUTTON button) const
  {
    return button_binding.toEnum(button);
  }

  int GamePadDevice::getBindAxisID(const GAMEPAD::AXIS axis) const
  {
    return axis_binding.toEnum(axis);
  }

  const Enum& GamePadDevice::GetGPButtonEnum() const
  {
    return GP_Mgr.ButtonEnum;
  }

  const Enum& GamePadDevice::GetGPAxisEnum() const
  {
    return GP_Mgr.AxisEnum;
  }

  GamePadDevice* GamePad(unsigned device_num)
  {
    return GP_Mgr.GetGamepad(device_num);
  }

  GamePadDevice* VGamePad(unsigned device_num)
  {
    return GP_Mgr.GetVGamepad(device_num);
  }

}
