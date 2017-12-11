
#include "KeyboardManager.hpp"
#include <SInput\Keyboard\Keyboard.hpp>
#include <iostream>

namespace SInput
{
  KeyboardDevice::KeyboardDevice() : currMods(0), prevMods(0)
  {
    Bind(0, KEYBOARD::KEY_SPACE);
    Bind(1, KEYBOARD::KEY_E);
    Bind(2, KEYBOARD::KEY_Q);
    Bind(3, KEYBOARD::KEY_SPACE);
    Bind(2, KEYBOARD::KEY_R);
  }

  KeyboardDevice::~KeyboardDevice()
  {}

  void KeyboardDevice::Print(KEYBOARD::KEY key)
  {
    std::clog << "Keyboard: " << GetKeysEnum().toStr(key) << " was " << (currKeys.Key[key].state == 1 ? "Pressed." : "Released.") << std::endl;
  }

  void KeyboardDevice::SwapBuffers()
  {
    prevKeys = currKeys;
    prevMods = currMods;
  }

  const Enum& KeyboardDevice::GetKeysEnum() const
  {
    return Key_Mgr.KeysEnum;
  }

  const Enum& KeyboardDevice::GetModsEnum() const
  {
    return Key_Mgr.ModsEnum;
  }

  bool KeyboardDevice::KeyPressed(KEYBOARD::KEY key) const
  {
    if (key > KEYBOARD::UNKNOWN_KEY && key < KEYBOARD::NUMBEROFKEYS)
    {
      if (currKeys.Key[key].state)
      {
        return true;
      }
    }

    return false;
  }

  bool KeyboardDevice::KeyTriggered(KEYBOARD::KEY key) const
  {
    if (key > KEYBOARD::UNKNOWN_KEY && key < KEYBOARD::NUMBEROFKEYS)
    {
      if (currKeys.Key[key].state && !prevKeys.Key[key].state)
      {
        return true;
      }
    }

    return false;
  }

  bool KeyboardDevice::KeyHeld(KEYBOARD::KEY key) const
  {
    if (key > KEYBOARD::UNKNOWN_KEY && key < KEYBOARD::NUMBEROFKEYS)
    {
      if (currKeys.Key[key].state && prevKeys.Key[key].state)
      {
        return true;
      }
    }

    return false;
  }

  bool KeyboardDevice::KeyReleased(KEYBOARD::KEY key) const
  {
    if (key > KEYBOARD::UNKNOWN_KEY && key < KEYBOARD::NUMBEROFKEYS)
    {
      if (!currKeys.Key[key].state && prevKeys.Key[key].state)
      {
        return true;
      }
    }

    return false;
  }

  bool KeyboardDevice::ModsPressed(int mods) const
  {
    if (mods ^ currMods)  // XOR check of mods
    {
      return false;
    }

    return true;
  }

  bool KeyboardDevice::ModsReleased(int mods) const
  {
    if (mods == prevMods)
    {
      if (mods ^ currMods)
      {
        return true;
      }
    }

    return false;
  }

  void KeyboardDevice::UpdateKey(KEYBOARD::KEY key, KEYBOARD::ACTION action)
  {
    if (action > KEYBOARD::UNKNOWN_ACTION)
    {
      if (key > KEYBOARD::UNKNOWN_KEY && key < KEYBOARD::NUMBEROFKEYS)
      {
        currKeys.Key[key].state = action;
      }
    }
  }

  void KeyboardDevice::UpdateMods(int mods)
  {
    currMods = mods;
  }

  void KeyboardDevice::Bind(int name_id, KEYBOARD::KEY key)
  {
    KEYBOARD::KEY old_key = name_to_key[name_id].key;

    name_to_key[name_id].key = key;

    int old_name = key_to_name[key].value;

    if (old_name > -1)
    {
      name_to_key[old_name].key = KEYBOARD::UNKNOWN_KEY;
    }

    if (old_key > KEYBOARD::UNKNOWN_KEY)
    {
      key_to_name[old_key].value = -1;
    }

    key_to_name[key].value = name_id;
  }

  KeyboardDevice* Keyboard()
  {
    return Key_Mgr.GetKeyboard();
  }

  KeyboardDevice* VKeyboard(unsigned device_num)
  {
    return Key_Mgr.GetVKeyboard(device_num);
  }

  //void BindKeyConverter(KeyFunc func)
  //{
  //  if (func)
  //  {
  //    KeyboardDevice::func = func;



  //  }
  //}

}
