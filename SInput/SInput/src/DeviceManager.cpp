
#include "Internal.hpp"
#include "DeviceManager.hpp"

#include <SInput\Device.hpp>

// Add All Input Device Managers Here /////////////////////////
#include "Keyboard\KeyboardManager.hpp"
#include "Mouse\MouseManager.hpp"
#include "GamePad\GamePadManager.hpp"

// Then add device name to DeviceEnums.inl

// Next add device header to DeviceList.hpp

// Lastly add the new device's Manager to device_managers
// in the DeviceManager constructor

////////////////////////////////////////////////////////////////

namespace SInput
{
  DeviceManager Dev_Mgr;

  DeviceManager::DeviceManager()
  {
    #ifdef ENUM_NAME
    #undef ENUM_NAME
    #endif

    #define ENUM_NAME(NAME) #NAME ,
    const char* InstKeysEnum[] =
    {
      "INVALID_DEVICE" ,
      #include <SInput\DeviceEnums.inl>
      "INVALID_ENUM"
    };
    #undef ENUM_NAME

    for (int i = DEVICE::UNKNOWN_DEVICE; i < DEVICE::NUMBEROFDEVICES; ++i)
    {
      DeviceEnum.addValue(i, InstKeysEnum[i+1]);
    }

    device_managers[DEVICE::KEYBOARD] = &Key_Mgr;
    device_managers[DEVICE::MOUSE]    = &Mouse_Mgr;
    device_managers[DEVICE::GAMEPAD]  = &GP_Mgr;

  }

  DeviceManager::~DeviceManager()
  {}

  void DeviceManager::SwapBuffers()
  {
    for (size_t i = 0; i < DEVICE::NUMBEROFDEVICES; ++i)
    {
      DevMgrPtr* mgr = device_managers[i];

      if (mgr)
      {
        mgr->SwapBuffers();
      }
    }
  }
}