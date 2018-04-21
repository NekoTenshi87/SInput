#pragma once

#include <SInput\DeviceList.hpp>
#include <SInput\Device.hpp>
#include <vector>
#include <list>
#include <time.h>

namespace SInput
{
  struct SerializeKey
  {
    KEYBOARD::ACTION action;
    KEYBOARD::KEY key;
    unsigned int mods;
    float time;
  };

  struct SerializeMouse
  {
    MOUSE::ACTION action;
    MOUSE::BUTTON button;
    MousePos pos;
    int deltaX, deltaY;
    bool inside;
    float time;
  };

  struct SerializeGamePad
  {
    GAMEPAD::ACTION action;
    GAMEPAD::BUTTON button;
    GAMEPAD::AXIS axis;
    float axis_delta;
    bool connected;
    float time;
  };

  class Serializer
  {
    public:
      Serializer() {}
      ~Serializer() {}

      void AddDeviceData(DeviceData device, void* data);

      std::list<SerializeKey> GetDeviceKeyData(DEVICETYPE type, int id);
      std::list<SerializeMouse> GetDeviceMouseData(DEVICETYPE type, int id);
      std::list<SerializeGamePad> GetDeviceGamePadData(DEVICETYPE type, int id);

      //void SaveToFile();

      //bool LoadFromFile();

    private:

      std::list<DeviceData> s_device;
      std::list<SerializeKey> s_key;
      std::list<SerializeMouse> s_mouse;
      std::list<SerializeGamePad> s_gamepad;

  };





  extern Serializer serialize;
}