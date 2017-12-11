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
  };

  class DeviceManager
  {
  public:

    DeviceManager();
    ~DeviceManager();

    void SwapBuffers();

    Enum DeviceEnum{ "Device Enums" };

  private:

    DevMgrPtr* device_managers[DEVICE::NUMBEROFDEVICES];
  };

  extern DeviceManager Dev_Mgr;
}
