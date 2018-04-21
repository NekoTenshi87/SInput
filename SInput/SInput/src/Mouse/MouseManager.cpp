
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

  void MouseManager::RunMonkey()
  {
    if (mouse.IsMonkey())
    {
      int frame_wait = mouse.GetMonkeyWait();

      if (frame_wait < 0)
      {
        int random = std::rand() % 12;

        if (random < 9)
        {
          MOUSE::BUTTON button = (MOUSE::BUTTON)(std::rand() % MOUSE::BUTTON::NUMBEROFMOUSEBUTTONS);

          mouse.UpdateButton(button, MOUSE::ACTION::PRESSED, true);
        }
        else
        {
          int random2 = std::rand() % 2;
          int random3 = std::rand() % 2;

          int dx = 0, dy = 0;

          if (random2 > 0)
          {
            dx = 1;
          }
          else
          {
            dy = 1;
          }

          if (random3 > 0)
          {
            dx *= -1; dy *= -1;
          }

          mouse.UpdateMouseWheel(dx, dy, true);
        }

        mouse.SetMonkeyWait(std::rand() % 60);
      }
      else
      {
        mouse.SetMonkeyWait(--frame_wait);
      }
    }

    for (auto& it : v_mice)
    {
      if (it.second.IsMonkey())
      {
        int frame_wait = it.second.GetMonkeyWait();

        if (frame_wait < 0)
        {
          int random = std::rand() % 12;

          if (random < 9)
          {
            MOUSE::BUTTON button = (MOUSE::BUTTON)(std::rand() % MOUSE::BUTTON::NUMBEROFMOUSEBUTTONS);

            it.second.UpdateButton(button, MOUSE::ACTION::PRESSED, true);
          }
          else
          {
            int random2 = std::rand() % 2;
            int random3 = std::rand() % 2;

            int dx = 0, dy = 0;

            if (random2 > 0)
            {
              dx = 1;
            }
            else
            {
              dy = 1;
            }

            if (random3 > 0)
            {
              dx *= -1; dy *= -1;
            }

            it.second.UpdateMouseWheel(dx, dy, true);
          }

          it.second.SetMonkeyWait(std::rand() % 60);
        }
        else
        {
          it.second.SetMonkeyWait(--frame_wait);
        }
      }
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