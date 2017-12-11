
#include "KeyboardManager.hpp"

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

  KeyboardDevice* KeyboardManager::GetKeyboard()
  {
    return &keyboard;
  }

  KeyboardDevice* KeyboardManager::GetVKeyboard(unsigned num)
  {
    return &v_keyboards[num];
  }
}
