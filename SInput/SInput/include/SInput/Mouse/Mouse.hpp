


#pragma once

#include <SInput\Binding.hpp>
#include <SInput\Enum.hpp>

namespace SInput
{
  #ifdef ENUM_NAME
  #undef ENUM_NAME
  #endif

  #define ENUM_NAME(NAME) NAME ,
  struct MOUSE
  {
    enum ACTION
    {
      UNKNOWN_ACTION = -1,
      RELEASED,
      PRESSED
    };

    enum BUTTON
    {
      UNKNOWN_BUTTON = -1,
      #include <SInput\Mouse\MouseEnums.inl>
      NUMBEROFMOUSEBUTTONS
    };
  };
  #undef ENUM_NAME

  //////////////////////////////////////////////////////////////////////////////
  //  MousePos Struct
  //////////////////////////////////////////////////////////////////////////////

  struct MousePos
  {
    MousePos();
    MousePos(int X, int Y);
    ~MousePos();

    int x, y;
  };

  ////////////////////////////////////////////////////////////////////////////////
  //  Mouse Class
  ////////////////////////////////////////////////////////////////////////////////

  class MouseDevice
  {
  public:

    //////////////////////////////////////////////////////////////////////////////
    //  Constructor/Destructor
    //////////////////////////////////////////////////////////////////////////////

    MouseDevice();
    ~MouseDevice();

    //////////////////////////////////////////////////////////////////////////////
    //  Public Functions
    //////////////////////////////////////////////////////////////////////////////
    
    void Print(MOUSE::BUTTON button);

    void PrintPos();

    void PrintScoll();

    void SwapBuffers();

    bool ButtonPressed(MOUSE::BUTTON button);

    bool ButtonTriggered(MOUSE::BUTTON button);

    bool ButtonHeld(MOUSE::BUTTON button);

    bool ButtonReleased(MOUSE::BUTTON button);

    bool WheelUp();

    bool WheelDown();

    bool WheelLeft();

    bool WheelRight();

    int  GetDeltaX();

    int  GetDeltaY();

    bool InsideWindow(); // Press Logic

    bool EntersWindow(); // Triggered Logic

    bool LeavesWindow(); // Release Logic

    MousePos CurrMousePos();

    MousePos PrevMousePos();

    MousePos DiffMousePos();

    bool InArea(int posX_left, int posX_right, int posY_top, int posY_bottom);

    void UpdateButton(MOUSE::BUTTON button, MOUSE::ACTION action);

    void UpdateMouseEnter(bool action);

    void UpdateMousePos(MousePos pos);

    void UpdateMouseWheel(int dX, int dY);

    //////////////////////////////////////////////////////////////////////////////
    //  Bindings
    //////////////////////////////////////////////////////////////////////////////

    void BindButton(int name_id, MOUSE::BUTTON button);

    void UnBindButton(int name_id);

    MOUSE::BUTTON getBindButton(const int name_id) const;

    int getBindButtonID(const MOUSE::BUTTON button) const;

    bool getNextButton = false;

    MOUSE::BUTTON nextButton = MOUSE::BUTTON::UNKNOWN_BUTTON;

    //////////////////////////////////////////////////////////////////////////////
    // Enums
    //////////////////////////////////////////////////////////////////////////////

    const Enum& GetButtonEnum();

  protected:

    //////////////////////////////////////////////////////////////////////////////
    //  Protected Data
    //////////////////////////////////////////////////////////////////////////////

    struct MBUTTONSTATE
    {
      MBUTTONSTATE() : state(0) {}

      int state;
    };

    struct MOUSESTATE
    {
      MOUSESTATE() : pos(), deltaX(0), deltaY(0), inside(false) {}

      MousePos pos;
      int deltaX, deltaY;
      bool inside;
    };

    struct MOUSE_DATA
    {
      MBUTTONSTATE Button[MOUSE::BUTTON::NUMBEROFMOUSEBUTTONS];
      MOUSESTATE   Status;
    };

    MOUSE_DATA currMouse;  // Stores the current Mouse Buttons pressed
    MOUSE_DATA prevMouse;  // Stores the previous Mouse Buttons pressed

    Binding button_binding{ "Mouse Bindings" };
  };

  ////////////////////////////////////////////////////////////////////////////////
  //  Global Functions
  ////////////////////////////////////////////////////////////////////////////////

  MouseDevice* Mouse();

  MouseDevice* VMouse(unsigned num);

}

