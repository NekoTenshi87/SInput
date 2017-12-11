
#include "MouseManager.hpp"

namespace SInput
{
  MouseManager Mouse_Mgr;

  MouseManager::MouseManager()
  {
    #ifdef ENUM_NAME
    #undef ENUM_NAME
    #endif

    #define ENUM_NAME(NAME) #NAME ,
    const char* InstMouseEnum[] =
    {
      "INVALID_MOUSE_BUTTON" ,
      #include <SInput\Mouse\MouseEnums.inl>
      "INVALID_ENUM"
    };
    #undef ENUM_NAME

    for (int i = MOUSE::UNKNOWN_BUTTON; i < MOUSE::NUMBEROFMOUSEBUTTONS; ++i)
    {
      ButtonEnum.addValue(i, InstMouseEnum[i+1]);
    }
  }

  MouseManager::~MouseManager()
  {}

  void MouseManager::SwapBuffers()
  {
    mouse.SwapBuffers();

    for (auto& it : v_mice)
    {
      it.second.SwapBuffers();
    }
  }

  MouseDevice* MouseManager::GetMouse()
  {
    return &mouse;
  }

  MouseDevice* MouseManager::GetVMouse(unsigned num)
  {
    return &v_mice[num];
  }

}