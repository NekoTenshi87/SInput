#pragma once

#include <SInput\DeviceList.hpp>
#include <SInput\Enum.hpp>
#include <SInput\Event.hpp>
#include <SInput\Serialize.hpp>
#include <SInput\Stats.hpp>
#include <SInput\NGram.hpp>

#include <fstream>
#include <queue>

namespace SInput
{
  // Abstract out!!!
  #define LEFT_AXIS_THRESHOLD  0.4f
  #define RIGHT_AXIS_THRESHOLD 0.5f
  #define KEY_HELD 2500

  //void PrintEvent(int key, int action, int mods);

  ////////////////////////////////////////////////////////////////////////////////
  //  Input Class
  ////////////////////////////////////////////////////////////////////////////////

  class Input
  {
  public:
    //////////////////////////////////////////////////////////////////////////////
    //  Constructor/Destructor
    //////////////////////////////////////////////////////////////////////////////

    //****************************************************************************
    //  \brief
    //    Default Input constructor.
    //****************************************************************************
    Input();

    //****************************************************************************
    //  \brief
    //    Default Input destructor.
    //****************************************************************************
    ~Input();

    //void Init();

    void SwapBuffers();

    void RunMonkey();

    //////////////////////////////////////////////////////////////////////////////
    //  Global Debugging Functions
    //////////////////////////////////////////////////////////////////////////////
    friend void PrintEvent(int key, int action, int mods);
    //void PrintKey(Keyboard::KEYS key);
    //void PrintMouseInfo();

    //////////////////////////////////////////////////////////////////////////////
    //  Function Handlers
    //////////////////////////////////////////////////////////////////////////////

    const Enum& getEventEnum();

    const Enum& getDeviceEnum();

  private:

    //////////////////////////////////////////////////////////////////////////////
    // Private Functions
    //////////////////////////////////////////////////////////////////////////////

    Enum EventEnum{ "Event Enums" };
  };



}

