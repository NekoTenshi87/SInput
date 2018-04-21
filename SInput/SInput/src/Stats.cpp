#include <SInput\Stats.hpp>
#include <algorithm>

namespace SInput
{
  Stats stats;

  Stats::Stats() {}

  Stats::~Stats() {}

  void Stats::AddStatData(DeviceData device, void* data)
  {
    if (device.device == DEVICE::UNKNOWN_DEVICE)
    {
      return;
    }

    switch (device.device)
    {
      case DEVICE::KEYBOARD:
      {
        SerializeKey* s_key = reinterpret_cast<SerializeKey*>(data);

        if (s_key->action == KEYBOARD::ACTION::PRESSED)
        {
          sm_keys[s_key->key].pressed_times.push_back(s_key->time);
          ++total_keys_pressed;
        }
        else if (s_key->action == KEYBOARD::ACTION::RELEASED)
        {
          sm_keys[s_key->key].released_times.push_back(s_key->time);
        }

        break;
      }
      case DEVICE::MOUSE:
      {
        SerializeMouse* s_mouse = reinterpret_cast<SerializeMouse*>(data);

        if (s_mouse->action == MOUSE::ACTION::PRESSED)
        {
          sm_mouse[s_mouse->button].pressed_times.push_back(s_mouse->time);
          ++total_mouse_pressed;
        }
        else if (s_mouse->action == MOUSE::ACTION::RELEASED)
        {
          sm_mouse[s_mouse->button].released_times.push_back(s_mouse->time);
        }

        break;
      }
      case DEVICE::GAMEPAD:
      {
        SerializeGamePad* s_gpad = reinterpret_cast<SerializeGamePad*>(data);

        if (s_gpad->action == GAMEPAD::ACTION::PRESSED)
        {
          sm_gamepad[s_gpad->button].pressed_times.push_back(s_gpad->time);
          ++total_gamepad_pressed;
        }
        else if (s_gpad->action == GAMEPAD::ACTION::RELEASED)
        {
          sm_gamepad[s_gpad->button].released_times.push_back(s_gpad->time);
        }

        break;
      }
      default:
        break;
    }
  }

  int Stats::GetPressedKey(KEYBOARD::KEY key)
  {
    return sm_keys[key].pressed_times.size();
  }

  int Stats::GetPressedMouse(MOUSE::BUTTON button)
  {
    return sm_mouse[button].pressed_times.size();
  }

  int Stats::GetPressedGamePad(GAMEPAD::BUTTON button)
  {
    return sm_gamepad[button].pressed_times.size();
  }

  int Stats::GetReleasedKey(KEYBOARD::KEY key)
  {
    return sm_keys[key].released_times.size();
  }

  int Stats::GetReleasedMouse(MOUSE::BUTTON button)
  {
    return sm_mouse[button].released_times.size();
  }

  int Stats::GetReleasedGamePad(GAMEPAD::BUTTON button)
  {
    return sm_gamepad[button].released_times.size();
  }

  float Stats::GetAverageTimeKey(KEYBOARD::KEY key)
  {
    int size = std::min(sm_keys[key].pressed_times.size(), sm_keys[key].released_times.size());

    if (size == 0)
    {
      return 0.0f;
    }

    float time = 0.0f;

    for (int i = 0; i < size; ++i)
    {
      time += sm_keys[key].released_times[i] - sm_keys[key].pressed_times[i];
    }

    return time / (float)(size);
  }

  float Stats::GetAverageTimeMouse(MOUSE::BUTTON button)
  {
    int size = std::min(sm_mouse[button].pressed_times.size(), sm_mouse[button].released_times.size());

    if (size == 0)
    {
      return 0.0f;
    }

    float time = 0.0f;

    for (int i = 0; i < size; ++i)
    {
      time += sm_mouse[button].released_times[i] - sm_mouse[button].pressed_times[i];
    }

    return time / (float)(size);
  }

  float Stats::GetAverageTimeGamePad(GAMEPAD::BUTTON button)
  {
    int size = std::min(sm_gamepad[button].pressed_times.size(), sm_gamepad[button].released_times.size());

    if (size == 0)
    {
      return 0.0f;
    }

    float time = 0.0f;

    for (int i = 0; i < size; ++i)
    {
      time += sm_gamepad[button].released_times[i] - sm_gamepad[button].pressed_times[i];
    }

    return time / (float)(size);
  }

  float Stats::GetPercentUseKey(KEYBOARD::KEY key)
  {
    return (float)(GetPressedKey(key)) / (float)(total_keys_pressed);
  }

  float Stats::GetPercentUseMouse(MOUSE::BUTTON button)
  {
    return (float)(GetPressedMouse(button)) / (float)(total_mouse_pressed);
  }

  float Stats::GetPercentUseGamePad(GAMEPAD::BUTTON button)
  {
    return (float)(GetPressedGamePad(button)) / (float)(total_gamepad_pressed);
  }

}