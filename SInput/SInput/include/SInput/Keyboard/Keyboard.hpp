


#pragma once

#include <SInput\Enum.hpp>
#include <unordered_map>

namespace SInput
{
  #ifdef MOD_NONE
  #undef MOD_NONE
  #endif

  #ifdef MOD_SHIFT
  #undef MOD_SHIFT
  #endif

  #ifdef MOD_CTRL
  #undef MOD_CTRL
  #endif

  #ifdef MOD_ALT
  #undef MOD_ALT
  #endif

  #ifdef MOD_SYSTEM
  #undef MOD_SYSTEM
  #endif

  #ifdef ENUM_NAME
  #undef ENUM_NAME
  #endif

  #define ENUM_NAME(NAME) NAME ,
  struct KEYBOARD
  {
    enum ACTION
    {
      UNKNOWN_ACTION = -1,
      RELEASED,
      PRESSED
    };

    enum KEY
    {
      UNKNOWN_KEY = -1,
      #include <SInput\Keyboard\KeyboardEnums.inl>
      NUMBEROFKEYS
    };

    enum MOD
    {
      MOD_NONE    =  0,  //00000000//
      MOD_SHIFT   =  1,  //00000001//
      MOD_CTRL    =  2,  //00000010//
      MOD_ALT     =  4,  //00000100//
      MOD_SYSTEM  =  8,  //00001000//
    };
  };
  #undef ENUM_NAME

  ////////////////////////////////////////////////////////////////////////////////
  //  Keyboard Class
  ////////////////////////////////////////////////////////////////////////////////

  class KeyboardDevice
  {
  public:
    //////////////////////////////////////////////////////////////////////////////
    //  Constructor/Destructor
    //////////////////////////////////////////////////////////////////////////////

    KeyboardDevice();
    ~KeyboardDevice();

    //////////////////////////////////////////////////////////////////////////////
    //  Public Functions
    //////////////////////////////////////////////////////////////////////////////

    void Print(KEYBOARD::KEY key);

    void SwapBuffers();

    bool KeyPressed(KEYBOARD::KEY key) const;

    bool KeyTriggered(KEYBOARD::KEY key) const;

    bool KeyHeld(KEYBOARD::KEY key) const;

    bool KeyReleased(KEYBOARD::KEY key) const;

    bool ModsPressed(int mods) const;

    bool ModsReleased(int mods) const;

    void UpdateKey(KEYBOARD::KEY key, KEYBOARD::ACTION action);

    void UpdateMods(int mods);

    void Bind(int name_id, KEYBOARD::KEY key);

    //////////////////////////////////////////////////////////////////////////////
    //  Enums
    //////////////////////////////////////////////////////////////////////////////

    const Enum& GetKeysEnum() const;

    const Enum& GetModsEnum() const;

  protected:
    //////////////////////////////////////////////////////////////////////////////
    //  Protected Data
    //////////////////////////////////////////////////////////////////////////////

    struct KEY_STATE
    {
      KEY_STATE() : state(0) {}

      int state;
    };

    struct KEY_DATA
    {
      KEY_STATE Key[KEYBOARD::KEY::NUMBEROFKEYS];
    };

    KEY_DATA currKeys;     // Stores the current Keys pressed
    KEY_DATA prevKeys;     // Stores the previous Keys pressed
    unsigned int currMods; // Stores the current Modifiers pressed
    unsigned int prevMods; // Stores the previous Modifiers pressed

    // So when it constructs a new object it defaults to unknown
    class KEY_INT
    {
    public:
      KEY_INT() : key(KEYBOARD::UNKNOWN_KEY) {}
      ~KEY_INT() {}

      KEYBOARD::KEY key;
    };
    
    class V_INT
    {
    public:
      V_INT() : value(-1) {}
      ~V_INT() {}

      int value;
    };

    std::unordered_map<int, KEY_INT> name_to_key;
    std::unordered_map<KEYBOARD::KEY, V_INT> key_to_name;
  };

  ////////////////////////////////////////////////////////////////////////////////
  //  Global Functions
  ////////////////////////////////////////////////////////////////////////////////

  KeyboardDevice* Keyboard();

  KeyboardDevice* VKeyboard(unsigned device_num);

}

