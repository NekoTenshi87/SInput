
#include "KeyboardManager.hpp"
#include <SInput\Keyboard\Keyboard.hpp>
#include <iostream>

namespace SInput
{
  KeyboardDevice::KeyboardDevice() : currMods(0), prevMods(0)
  {}

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

  void KeyboardDevice::BindKey(int name_id, KEYBOARD::KEY key)
  {
    key_binding.addValue(name_id, key);
  }

  void KeyboardDevice::UnBindKey(int name_id)
  {
    key_binding.addValue(name_id, KEYBOARD::UNKNOWN_KEY);
  }

  KEYBOARD::KEY KeyboardDevice::getBindKey(const int name_id) const
  {
    return static_cast<KEYBOARD::KEY>(key_binding.toType(name_id));
  }

  int KeyboardDevice::getBindKeyID(const KEYBOARD::KEY key) const
  {
    return key_binding.toEnum(key);
  }

  const Enum& KeyboardDevice::GetKeysEnum() const
  {
    return Key_Mgr.KeysEnum;
  }

  const Enum& KeyboardDevice::GetModsEnum() const
  {
    return Key_Mgr.ModsEnum;
  }

  KeyboardDevice* Keyboard()
  {
    return Key_Mgr.GetKeyboard();
  }

  KeyboardDevice* VKeyboard(unsigned device_num)
  {
    return Key_Mgr.GetVKeyboard(device_num);
  }

}
