


#pragma once

#include <SInput\Enum.hpp>

namespace SInput
{
  #ifdef ENUM_NAME
  #undef ENUM_NAME
  #endif

  #define ENUM_NAME(NAME) NAME ,
  struct GAMEPAD
  {
    enum PAD
    {
      UNKNOWN_PAD = -1,
      PAD_1,
      PAD_2,
      PAD_3,
      PAD_4,
      PAD_5,
      PAD_6,
      PAD_7,
      PAD_8,
      PAD_9,
      PAD_10,
      PAD_11,
      PAD_12,
      PAD_13,
      PAD_14,
      PAD_15,
      PAD_16,
      NUMBEROFGAMEPADS
    };

    enum STATUS
    {
      UNKNOWN_STATUS = -1,
      CONNECTED,
      DISCONNECTED
    };

    enum ACTION
    {
      UNKNOWN_ACTION = -1,
      RELEASED,
      PRESSED
    };

    enum BUTTON
    {
      UNKNOWN_BUTTON = -1,
      #include <SInput\GamePad\GamePadButtonEnums.inl>

      /* XBOX Bindings
      XBOX_A          = GAMEPAD::BUTTON_1,
      XBOX_B          = GAMEPAD::BUTTON_2,
      XBOX_X          = GAMEPAD::BUTTON_3,
      XBOX_Y          = GAMEPAD::BUTTON_4,
      XBOX_LB         = GAMEPAD::BUTTON_5,
      XBOX_RB         = GAMEPAD::BUTTON_6,
      XBOX_BACK       = GAMEPAD::BUTTON_7,
      XBOX_START      = GAMEPAD::BUTTON_8,
      XBOX_LEFT_JS    = GAMEPAD::BUTTON_9,
      XBOX_RIGHT_JS   = GAMEPAD::BUTTON_10,
      XBOX_DPAD_UP    = GAMEPAD::BUTTON_11,
      XBOX_DPAD_RIGHT = GAMEPAD::BUTTON_12,
      XBOX_DPAD_DOWN  = GAMEPAD::BUTTON_13,
      XBOX_DPAD_LEFT  = GAMEPAD::BUTTON_14,
      */

      NUMBEROFGPBUTTONS
    };

    enum AXIS
    {
      UNKNOWN_AXIS = -1,
      #include <SInput\GamePad\GamePadAxisEnums.inl>
      NUMBEROFGPAXIS
    };
  };
  #undef ENUM_NAME

  ////////////////////////////////////////////////////////////////////////////////
  //  GamePad Class
  ////////////////////////////////////////////////////////////////////////////////

  class GamePadDevice
  {
  public:

    //////////////////////////////////////////////////////////////////////////////
    //  Constructor/Destructor
    //////////////////////////////////////////////////////////////////////////////

    GamePadDevice();
    ~GamePadDevice();

    //////////////////////////////////////////////////////////////////////////////
    //  Public Functions
    //////////////////////////////////////////////////////////////////////////////
    
    void Print();

    void PrintConnection(int gp_num);

    void PrintButton(int gp_num, GAMEPAD::BUTTON button);

    void PrintAxis(int gp_num, GAMEPAD::AXIS axis);

    void SwapBuffers();

    bool ButtonPressed(GAMEPAD::BUTTON button);

    bool ButtonTriggered(GAMEPAD::BUTTON button);

    bool ButtonHeld(GAMEPAD::BUTTON button);

    bool ButtonReleased(GAMEPAD::BUTTON button);

    bool IsConnected(); // Pressed Logic

    bool IsPluggedIn(); // Triggered Logic

    bool IsUnplugged(); // Released Logic

    float GetAxis(GAMEPAD::AXIS axis);

    void UpdateButton(GAMEPAD::BUTTON button, GAMEPAD::ACTION action);

    void UpdateAxis(GAMEPAD::AXIS axis, float delta);

    void UpdateConnection(GAMEPAD::STATUS status);

    //////////////////////////////////////////////////////////////////////////////
    // Enums
    //////////////////////////////////////////////////////////////////////////////

    const Enum& GetGPButtonEnum() const;

    const Enum& GetGPAxisEnum() const;

  protected:

    //////////////////////////////////////////////////////////////////////////////
    //  Protected Data
    //////////////////////////////////////////////////////////////////////////////

    struct BUTTON_STATE
    {
      BUTTON_STATE() : state(0) {}

      int state;
    };

    struct AXIS_STATE
    {
      AXIS_STATE() : delta(0.0f) {}

      float delta;
    };

    struct CONNECT_STATE
    {
      CONNECT_STATE() : state(false) {}

      bool state;
    };

    struct GP_DATA
    {
      BUTTON_STATE  Button[GAMEPAD::BUTTON::NUMBEROFGPBUTTONS];
      AXIS_STATE    Axis[GAMEPAD::AXIS::NUMBEROFGPAXIS];
      CONNECT_STATE Connection;
    };

    GP_DATA currGP;  // Stores the current GamePad Buttons pressed
    GP_DATA prevGP;  // Stores the previous GamePad Buttons pressed
  };

  ////////////////////////////////////////////////////////////////////////////////
  //  Global Functions
  ////////////////////////////////////////////////////////////////////////////////

  GamePadDevice* GamePad(unsigned num);

  GamePadDevice* VGamePad(unsigned num);

}

