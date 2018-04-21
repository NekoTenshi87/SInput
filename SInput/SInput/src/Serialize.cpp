
#include <SInput\Serialize.hpp>

namespace SInput
{
  Serializer serialize;

  void Serializer::AddDeviceData(DeviceData device, void* data)
  {
    if (device.device == DEVICE::UNKNOWN_DEVICE)
    {
      return;
    }

    if (device.device_type == DEVICETYPE::UNKNOWN_DEVICE_TYPE)
    {
      return;
    }

    if (data == nullptr)
    {
      return;
    }

    switch (device.device)
    {
      case DEVICE::KEYBOARD:
        s_key.push_back(*reinterpret_cast<SerializeKey*>(data));
        device.data = &s_key.back();
        break;
      case DEVICE::MOUSE:
        s_mouse.push_back(*reinterpret_cast<SerializeMouse*>(data));
        device.data = &s_mouse.back();
        break;
      case DEVICE::GAMEPAD:
        s_gamepad.push_back(*reinterpret_cast<SerializeGamePad*>(data));
        device.data = &s_gamepad.back();
        break;
      default:
        break;
    }

    s_device.push_back(device);
  }

  std::list<SerializeKey> Serializer::GetDeviceKeyData(DEVICETYPE type, int id)
  {
    std::list<SerializeKey> list;
    
    for (DeviceData data : s_device)
    {
      if (data.device == DEVICE::KEYBOARD && data.device_type == type && data.device_id == id)
      {
        list.push_back(*reinterpret_cast<SerializeKey*>(data.data));
      }
    }

    return list;
  }

  std::list<SerializeMouse> Serializer::GetDeviceMouseData(DEVICETYPE type, int id)
  {
    std::list<SerializeMouse> list;

    for (DeviceData data : s_device)
    {
      if (data.device == DEVICE::MOUSE && data.device_type == type && data.device_id == id)
      {
        list.push_back(*reinterpret_cast<SerializeMouse*>(data.data));
      }
    }

    return list;
  }

  std::list<SerializeGamePad> Serializer::GetDeviceGamePadData(DEVICETYPE type, int id)
  {
    std::list<SerializeGamePad> list;

    for (DeviceData data : s_device)
    {
      if (data.device == DEVICE::GAMEPAD && data.device_type == type && data.device_id == id)
      {
        list.push_back(*reinterpret_cast<SerializeGamePad*>(data.data));
      }
    }

    return list;
  }



}