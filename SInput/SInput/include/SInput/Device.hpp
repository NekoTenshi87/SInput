#pragma once

namespace SInput
{
  #ifdef ENUM_NAME
  #undef ENUM_NAME
  #endif

  #define ENUM_NAME(NAME) NAME ,
  enum DEVICE
  {
    UNKNOWN_DEVICE = -1,
    #include <SInput\DeviceEnums.inl>
    NUMBEROFDEVICES
  };
  #undef ENUM_NAME

  enum DEVICETYPE
  {
    UNKNOWN_DEVICE_TYPE = -1,
    BUILT_IN_DEVICE,
    VIRTUAL_DEVICE
  };

  struct DeviceData
  {
    DEVICE device;
    DEVICETYPE device_type;
    int device_id;
    void* data;
  };
}
