
#include "MouseManager.hpp"
#include <SInput\Mouse\Mouse.hpp>
#include <iostream>

namespace SInput
{
  MousePos::MousePos() : x(0), y(0) {}

  MousePos::MousePos(int X, int Y) : x(X), y(Y) {}

  MousePos::~MousePos() {}

  MouseDevice::MouseDevice()
  {}

  MouseDevice::~MouseDevice()
  {}

  void MouseDevice::Print(MOUSE::BUTTON button)
  {
    std::clog << "Mouse: " << GetButtonEnum().toStr(button) << " was " << (currMouse.Button[button].state == 1 ? "Pressed." : "Released.") << std::endl;
  }

  void MouseDevice::PrintPos()
  {
    std::clog << "MousePos: " << Mouse()->currMouse.Status.pos.x << ","
                              << Mouse()->currMouse.Status.pos.y << std::endl;
  }

  void MouseDevice::PrintScoll()
  {
    std::clog << "MouseScroll: X: " << currMouse.Status.deltaX << " Y: " << currMouse.Status.deltaY << std::endl;
  }

  void MouseDevice::SwapBuffers()
  {
    prevMouse = currMouse;

    currMouse.Status.deltaX = 0;
    currMouse.Status.deltaY = 0;
  }

  bool MouseDevice::ButtonPressed(MOUSE::BUTTON button)
  {
    if (button > MOUSE::UNKNOWN_BUTTON && button < MOUSE::NUMBEROFMOUSEBUTTONS)
    {
      if (currMouse.Button[button].state)
      {
        return true;
      }
    }

    return false;
  }

  bool MouseDevice::ButtonTriggered(MOUSE::BUTTON button)
  {
    if (button > MOUSE::UNKNOWN_BUTTON && button < MOUSE::NUMBEROFMOUSEBUTTONS)
    {
      if (currMouse.Button[button].state && !prevMouse.Button[button].state)
      {
        return true;
      }
    }

    return false;
  }

  bool MouseDevice::ButtonHeld(MOUSE::BUTTON button)
  {
    if (button > MOUSE::UNKNOWN_BUTTON && button < MOUSE::NUMBEROFMOUSEBUTTONS)
    {
      if (currMouse.Button[button].state && prevMouse.Button[button].state)
      {
        return true;
      }
    }

    return false;
  }

  bool MouseDevice::ButtonReleased(MOUSE::BUTTON button)
  {
    if (button > MOUSE::UNKNOWN_BUTTON && button < MOUSE::NUMBEROFMOUSEBUTTONS)
    {
      if (!currMouse.Button[button].state && prevMouse.Button[button].state)
      {
        return true;
      }
    }

    return false;
  }

  bool MouseDevice::WheelUp()
  {
    if (currMouse.Status.deltaY > 0)
    {
      return true;
    }

    return false;
  }

  bool MouseDevice::WheelDown()
  {
    if (currMouse.Status.deltaY < 0)
    {
      return true;
    }

    return false;
  }

  bool MouseDevice::WheelLeft()
  {
    if (currMouse.Status.deltaX < 0)
    {
      return true;
    }

    return false;
  }

  bool MouseDevice::WheelRight()
  {
    if (currMouse.Status.deltaX > 0)
    {
      return true;
    }

    return false;
  }

  int MouseDevice::GetDeltaX()
  {
    return currMouse.Status.deltaX;
  }

  int MouseDevice::GetDeltaY()
  {
    return currMouse.Status.deltaY;
  }

  bool MouseDevice::InsideWindow()
  {
    return currMouse.Status.inside;
  }

  bool MouseDevice::EntersWindow()
  {
    if (currMouse.Status.inside && !prevMouse.Status.inside)
    {
      return true;
    }

    return false;
  }

  bool MouseDevice::LeavesWindow()
  {
    if (!currMouse.Status.inside && prevMouse.Status.inside)
    {
      return true;
    }

    return false;
  }

  MousePos MouseDevice::CurrMousePos()
  {
    return currMouse.Status.pos;
  }

  MousePos MouseDevice::PrevMousePos()
  {
    return prevMouse.Status.pos;
  }

  MousePos MouseDevice::DiffMousePos()
  {
    return MousePos(currMouse.Status.pos.x - prevMouse.Status.pos.x,
      currMouse.Status.pos.y - prevMouse.Status.pos.y);
  }

  bool MouseDevice::InArea(int posX_left, int posX_right, int posY_top, int posY_bottom)
  {
    if (currMouse.Status.pos.x < posX_left || currMouse.Status.pos.y < posY_top ||
      currMouse.Status.pos.x > posX_right || currMouse.Status.pos.y > posY_bottom)
    {
      return false;
    }

    return true;
  }

  void MouseDevice::UpdateButton(MOUSE::BUTTON button, MOUSE::ACTION action)
  {
    if (action > MOUSE::UNKNOWN_ACTION)
    {
      if (button > MOUSE::UNKNOWN_BUTTON && button < MOUSE::NUMBEROFMOUSEBUTTONS)
      {
        currMouse.Button[button].state = action;
      }
    }
  }

  void MouseDevice::UpdateMouseEnter(bool action)
  {
    currMouse.Status.inside = action;
  }

  void MouseDevice::UpdateMousePos(MousePos pos)
  {
    currMouse.Status.pos = pos;
  }

  void MouseDevice::UpdateMouseWheel(int dX, int dY)
  {
    currMouse.Status.deltaX = dX;
    currMouse.Status.deltaY = dY;
  }

  const Enum& MouseDevice::GetButtonEnum()
  {
    return Mouse_Mgr.ButtonEnum;
  }

  MouseDevice* Mouse()
  {
    return Mouse_Mgr.GetMouse();
  }

  MouseDevice* VMouse(unsigned device_num)
  {
    return Mouse_Mgr.GetVMouse(device_num);
  }

}

