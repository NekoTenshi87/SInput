#pragma once

#include <SInput\DeviceList.hpp>
#include <SInput\Device.hpp>
#include <SInput\Serialize.hpp>
#include <vector>
#include <unordered_map>

namespace SInput
{
  struct StatsData
  {
    std::vector<float> pressed_times;
    std::vector<float> released_times;
  };

  class Stats
  {
    public:
      Stats();
      ~Stats();

      void AddStatData(DeviceData device, void* data);

      int GetPressedKey(KEYBOARD::KEY key);
      int GetPressedMouse(MOUSE::BUTTON button);
      int GetPressedGamePad(GAMEPAD::BUTTON button);

      int GetReleasedKey(KEYBOARD::KEY key);
      int GetReleasedMouse(MOUSE::BUTTON button);
      int GetReleasedGamePad(GAMEPAD::BUTTON button);

      float GetAverageTimeKey(KEYBOARD::KEY key);
      float GetAverageTimeMouse(MOUSE::BUTTON button);
      float GetAverageTimeGamePad(GAMEPAD::BUTTON button);

      float GetPercentUseKey(KEYBOARD::KEY key);
      float GetPercentUseMouse(MOUSE::BUTTON button);
      float GetPercentUseGamePad(GAMEPAD::BUTTON button);

    private:
      std::unordered_map<KEYBOARD::KEY, StatsData> sm_keys;
      int total_keys_pressed = 0;
      std::unordered_map<MOUSE::BUTTON, StatsData> sm_mouse;
      int total_mouse_pressed = 0;
      std::unordered_map<GAMEPAD::BUTTON, StatsData> sm_gamepad;
      int total_gamepad_pressed = 0;
  };

  extern Stats stats;
}
