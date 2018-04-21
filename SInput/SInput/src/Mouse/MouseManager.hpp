#pragma once

#include "..\DeviceManager.hpp"
#include <SInput\Enum.hpp>
#include <SInput\Mouse\Mouse.hpp>

#include <unordered_map>

namespace SInput
{
  class MouseManager : public DevMgrPtr
  {
  public:
    MouseManager();
    ~MouseManager();

    void SwapBuffers();

    void RunMonkey();

    MouseDevice* GetMouse();

    MouseDevice* GetVMouse(unsigned num);

    Enum ButtonEnum{ "MouseButton Enums" };

  private:

    MouseDevice mouse;
    std::unordered_map<unsigned, VMouseDevice> v_mice;
  };

  extern MouseManager Mouse_Mgr;
}