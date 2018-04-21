
#include "KeyboardManager.hpp"
#include <stdlib.h>

namespace SInput
{
  KeyboardManager Key_Mgr;

  KeyboardManager::KeyboardManager()
  {
    #ifdef ENUM_NAME
    #undef ENUM_NAME
    #endif

    #define ENUM_NAME(NAME) #NAME ,
    const char* InstKeysEnum[] =
    {
      "INVALID_KEY" ,
      #include <SInput\Keyboard\KeyboardEnums.inl>
      "INVALID_ENUM"
    };
    #undef ENUM_NAME

    for (int i = KEYBOARD::UNKNOWN_KEY; i < KEYBOARD::NUMBEROFKEYS; ++i)
    {
      KeysEnum.addValue(i, InstKeysEnum[i+1]);
    }

    // Add in MODS

    ModsEnum.addValue(KEYBOARD::MOD_NONE, "NONE");
    ModsEnum.addValue(KEYBOARD::MOD_SHIFT, "SHIFT");
    ModsEnum.addValue(KEYBOARD::MOD_CTRL, "CTRL");
    ModsEnum.addValue(KEYBOARD::MOD_ALT, "ALT");
    ModsEnum.addValue(KEYBOARD::MOD_SYSTEM, "SYSTEM");
  }

  KeyboardManager::~KeyboardManager()
  {}

  void KeyboardManager::SwapBuffers()
  {
    keyboard.SwapBuffers();

    for (auto& it : v_keyboards)
    {
      it.second.SwapBuffers();
    }
  }

  void KeyboardManager::RunMonkey()
  {
    if (keyboard.IsMonkey())
    {
      int frame_wait = keyboard.GetMonkeyWait();

      if (frame_wait < 0)
      {
        int random = std::rand() % KEYBOARD::KEY::NUMBEROFKEYS;

        if (random == KEYBOARD::KEY::KEY_ESC)
        {
          ++random;
        }

        KEYBOARD::KEY key = (KEYBOARD::KEY)(random);

        keyboard.UpdateKey(key, KEYBOARD::ACTION::PRESSED, true);

        keyboard.SetMonkeyWait(std::rand() % 60);
      }
      else
      {
        keyboard.SetMonkeyWait(--frame_wait);
      }
    }

    for (auto& it : v_keyboards)
    {
      if (it.second.IsMonkey())
      {
        int frame_wait = it.second.GetMonkeyWait();

        if (frame_wait < 0)
        {
          KEYBOARD::KEY key = (KEYBOARD::KEY)(std::rand() % KEYBOARD::KEY::NUMBEROFKEYS);

          it.second.UpdateKey(key, KEYBOARD::ACTION::PRESSED, true);

          it.second.SetMonkeyWait(std::rand() % 60);
        }
        else
        {
          it.second.SetMonkeyWait(--frame_wait);
        }
      }
    }
  }

  KeyboardDevice* KeyboardManager::GetKeyboard()
  {
    return &keyboard;
  }

  KeyboardDevice* KeyboardManager::GetVKeyboard(unsigned num)
  {
    return &v_keyboards[num];
  }
}
