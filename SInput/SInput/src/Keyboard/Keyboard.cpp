
#include <SInput\SInput.hpp>
#include "KeyboardManager.hpp"
#include <SInput\Keyboard\Keyboard.hpp>
#include <SInput\Serialize.hpp>
#include <SInput\Stats.hpp>
#include <iostream>

namespace SInput
{
  KeyboardDevice::KeyboardDevice() : currMods(0), prevMods(0), device_id(0)
  {
    device_type = DEVICETYPE::BUILT_IN_DEVICE;
  }

  KeyboardDevice::~KeyboardDevice()
  {}

  VKeyboardDevice::VKeyboardDevice() : KeyboardDevice()
  {
    device_type = DEVICETYPE::VIRTUAL_DEVICE;
  }

  VKeyboardDevice::~VKeyboardDevice()
  {}

  void KeyboardDevice::PrintKey(KEYBOARD::KEY key)
  {
    if (device_type == DEVICETYPE::VIRTUAL_DEVICE)
    {
      std::clog << "VKeyboard(" << device_id << "): ";
    }
    else
    {
      std::clog << "Keyboard: ";
    }
    
    PrintMods(key);
      
    std::clog << GetKeysEnum().toStr(key) << " was " << (currKeys.Key[key].state == 1 ? "Pressed." : "Released.") << std::endl;
  }

  void KeyboardDevice::PrintMods(KEYBOARD::KEY key)
  {
    if (currMods != KEYBOARD::MOD_NONE)
    {
      if (key != KEYBOARD::KEY::KEY_LEFT_SHIFT && key != KEYBOARD::KEY::KEY_RIGHT_SHIFT)
      {
        std::clog << (currMods & KEYBOARD::MOD_SHIFT ? "SHIFT + " : "");
      }
      if (key != KEYBOARD::KEY::KEY_LEFT_CONTROL && key != KEYBOARD::KEY::KEY_RIGHT_CONTROL)
      {
        std::clog << (currMods & KEYBOARD::MOD_CTRL ? "CTRL + " : "");
      }
      if (key != KEYBOARD::KEY::KEY_LEFT_ALT && key != KEYBOARD::KEY::KEY_RIGHT_ALT)
      {
        std::clog << (currMods & KEYBOARD::MOD_ALT ? "ALT + " : "");
      }
      if (key != KEYBOARD::KEY::KEY_LEFT_SYSTEM && key != KEYBOARD::KEY::KEY_RIGHT_SYSTEM)
      {
        std::clog << (currMods & KEYBOARD::MOD_SYSTEM ? "SYSTEM + " : "");
      }
    }
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

  KEYBOARD::MOD KeyboardDevice::KeyToMod(KEYBOARD::KEY key) const
  {
    switch (key)
    {
      case KEYBOARD::KEY::KEY_LEFT_ALT:
      case KEYBOARD::KEY::KEY_RIGHT_ALT:
        return KEYBOARD::MOD::MOD_ALT;
        break;
      case KEYBOARD::KEY::KEY_LEFT_CONTROL:
      case KEYBOARD::KEY::KEY_RIGHT_CONTROL:
        return KEYBOARD::MOD::MOD_CTRL;
        break;
      case KEYBOARD::KEY::KEY_LEFT_SHIFT:
      case KEYBOARD::KEY::KEY_RIGHT_SHIFT:
        return KEYBOARD::MOD::MOD_SHIFT;
        break;
      case KEYBOARD::KEY::KEY_LEFT_SYSTEM:
      case KEYBOARD::KEY::KEY_RIGHT_SYSTEM:
        return KEYBOARD::MOD::MOD_SYSTEM;
        break;
      default:
        return KEYBOARD::MOD::MOD_NONE;
        break;
    }
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

  void KeyboardDevice::UpdateKey(KEYBOARD::KEY key, KEYBOARD::ACTION action, bool debugShow)
  {
    if (action > KEYBOARD::UNKNOWN_ACTION)
    {
      if (key > KEYBOARD::UNKNOWN_KEY && key < KEYBOARD::NUMBEROFKEYS)
      {
        currKeys.Key[key].state = action;
        
        DeviceData device;
        device.device = DEVICE::KEYBOARD;
        device.device_type = device_type;
        device.device_id = device_id;

        SerializeKey key_data;
        key_data.action = action;
        key_data.key = key;
        key_data.mods = currMods;
        key_data.time = currTime;

        serialize.AddDeviceData(device, &key_data);
        stats.AddStatData(device, &key_data);

        if (debugShow)
        {
          PrintKey(key);
        }
      }
    }
  }

  void KeyboardDevice::UpdateMods(int mods)
  {
    currMods = mods;
  }

  void KeyboardDevice::Monkey(bool enable)
  {
    if (monkey != enable)
    {
      monkey = enable;
    }
  }

  bool KeyboardDevice::IsMonkey()
  {
    return monkey;
  }

  void KeyboardDevice::SetMonkeyWait(int wait)
  {
    monkey_wait = wait;
  }

  int KeyboardDevice::GetMonkeyWait()
  {
    return monkey_wait;
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
