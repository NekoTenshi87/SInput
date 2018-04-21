#pragma once

#include "..\DeviceManager.hpp"
#include <SInput\Enum.hpp>
#include <SInput\Keyboard\Keyboard.hpp>

#include <unordered_map>

namespace SInput
{
  class KeyboardManager : public DevMgrPtr
  {
  public:
    KeyboardManager();
    ~KeyboardManager();

    void SwapBuffers();

    void RunMonkey();

    KeyboardDevice* GetKeyboard();

    KeyboardDevice* GetVKeyboard(unsigned num);

    Enum KeysEnum{ "Keyboard Enums" };
    Enum ModsEnum{ "Modifier Enums" };

  private:

    KeyboardDevice keyboard;
    std::unordered_map<unsigned, VKeyboardDevice> v_keyboards;
  };

  extern KeyboardManager Key_Mgr;
}