#pragma once

#include <SInput\Device.hpp>
#include <SInput\Enum.hpp>

namespace SInput
{
  class DevMgrPtr
  {
  public:

    DevMgrPtr() {}
    virtual ~DevMgrPtr() {}

    virtual void SwapBuffers() {}
    virtual void RunMonkey() {}
  };

  class DeviceManager
  {
  public:

    DeviceManager();
    ~DeviceManager();

    void SwapBuffers();

    void RunMonkey();

    Enum DeviceEnum{ "Device Enums" };

  private:

    DevMgrPtr* device_managers[DEVICE::NUMBEROFDEVICES];
  };

  extern DeviceManager Dev_Mgr;
}
