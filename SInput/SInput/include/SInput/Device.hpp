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
  /*
  class Device
  {
  public:
    Device() {}
    virtual ~Device() {}

    virtual void SwapBuffers() {}
  };*/


}
