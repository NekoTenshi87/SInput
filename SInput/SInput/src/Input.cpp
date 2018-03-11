
#include "Internal.hpp"
#include "DeviceManager.hpp"
#include <SInput\Input.hpp>
#include <string.h>
#include <iostream>

namespace SInput
{
  ////////////////////////////////////////////////////////////////////////////////
  // Input Class Constructor/Deconstructor
  ////////////////////////////////////////////////////////////////////////////////

  Input::Input()
  {
    #ifdef ENUM_NAME
    #undef ENUM_NAME
    #endif

    #define ENUM_NAME(NAME) #NAME ,
    const char* InstEventEnums[] =
    {
      #include <SInput\EventEnums.inl>
      "INVALID_ENUM"
    };
    #undef ENUM_NAME

    for (int i = 0; i < EVENTS::NUMBEROFEVENTS; ++i)
    {
      EventEnum.addValue(i, InstEventEnums[i]);
    }
  }

  Input::~Input()
  {}

  //void Input::Init()
  //{}

  void Input::SwapBuffers()
  {
    Dev_Mgr.SwapBuffers();
  }

  /*
  void Input::PrintEvent(sf::Event& event_)
  {
    std::cout << "Event: " << getEventEnum().toStr(event_.type)
      << " invoked." << std::endl;

    //Print additional info
    switch (event_.type)
    {
    case sf::Event::Resized:
      std::cout << "  Width:  " << event_.size.width << std::endl;
      std::cout << "  Height: " << event_.size.height << std::endl;
      break;
    case sf::Event::KeyPressed:
      std::cout << "  Pressed: " << getKeysEnum().toStr(event_.key.code)
        << std::endl;
      break;
    case sf::Event::KeyReleased:
      std::cout << "  Released: " << getKeysEnum().toStr(event_.key.code)
        << std::endl;
      break;
    case sf::Event::MouseWheelMoved:
      std::cout << "  Delta: " << event_.mouseWheel.delta << std::endl;
      std::cout << "  Pos: x = " << event_.mouseWheel.x
        << ", y = " << event_.mouseWheel.y << std::endl;
      break;
    case sf::Event::MouseWheelScrolled:
      std::cout << "  Delta: " << event_.mouseWheelScroll.delta << std::endl;
      std::cout << "  Pos: x = " << event_.mouseWheelScroll.x
        << ", y = " << event_.mouseWheelScroll.y << std::endl;
      break;
    case sf::Event::MouseButtonPressed:
      std::cout << "  Pressed: " << getMouseEnum().toStr(event_.mouseButton.button) << std::endl;
      std::cout << "  Pos: x = " << event_.mouseButton.x
        << ", y = " << event_.mouseButton.y << std::endl;

      break;
    case sf::Event::MouseButtonReleased:
      std::cout << "  Released: " << getMouseEnum().toStr(event_.mouseButton.button) << std::endl;
      std::cout << "  Pos: x = " << event_.mouseButton.x
        << ", y = " << event_.mouseButton.y << std::endl;
      break;
    case sf::Event::MouseMoved:
      std::cout << "  Pos: x = " << event_.mouseMove.x
        << ", y = " << event_.mouseMove.y << std::endl;
      break;
    case sf::Event::JoystickButtonPressed:
      std::cout << "  Pressed: " << getJoyButtonEnum().toStr(event_.joystickButton.button)
        << std::endl;
      break;
    case sf::Event::JoystickButtonReleased:
      std::cout << "  Released: " << getJoyButtonEnum().toStr(event_.joystickButton.button)
        << std::endl;
      break;
    case sf::Event::JoystickMoved:
      std::cout << "  JoyStick: " << getJoyNumEnum().toStr(event_.joystickMove.joystickId) << std::endl;
      std::cout << "  Axis: " << getJoyAxisEnum().toStr(event_.joystickMove.axis) << std::endl;
      std::cout << "  Value: " << event_.joystickMove.position << std::endl;
      break;
    case sf::Event::JoystickConnected:
      std::cout << "  Connected: " << getJoyNumEnum().toStr(event_.joystickConnect.joystickId)
        << std::endl;
      break;
    case sf::Event::JoystickDisconnected:
      std::cout << "  Disconnected: " << getJoyNumEnum().toStr(event_.joystickConnect.joystickId)
        << std::endl;
      break;
      //case sf::Event::TouchBegan:
      //  break;
      //case sf::Event::TouchMoved:
      //  break;
      //case sf::Event::TouchEnded:
      //  break;
    }
  }*/

  void PrintEvent(int key, int action, int mods)
  {
    //std::cout << "Event: " << init_instance->getEventEnum().toStr(event_.type)
    //<< " invoked." << std::endl;

    //Print additional info
    switch (action)//event_.type)
    {/*
    case sf::Event::Resized:
    std::cout << "  Width:  " << event_.size.width << std::endl;
    std::cout << "  Height: " << event_.size.height << std::endl;
    break;*/
    case 1:
      std::cout << "  Pressed: " << Keyboard()->GetKeysEnum().toStr(key)
        << std::endl;
      break;
    case 0:
      std::cout << "  Released: " << Keyboard()->GetKeysEnum().toStr(key)
        << std::endl;
      break;/*
      case sf::Event::MouseWheelMoved:
      std::cout << "  Delta: " << event_.mouseWheel.delta << std::endl;
      std::cout << "  Pos: x = " << event_.mouseWheel.x
      << ", y = " << event_.mouseWheel.y << std::endl;
      break;
      case sf::Event::MouseWheelScrolled:
      std::cout << "  Delta: " << event_.mouseWheelScroll.delta << std::endl;
      std::cout << "  Pos: x = " << event_.mouseWheelScroll.x
      << ", y = " << event_.mouseWheelScroll.y << std::endl;
      break;
      case sf::Event::MouseButtonPressed:
      std::cout << "  Pressed: " << getMouseEnum().toStr(event_.mouseButton.button) << std::endl;
      std::cout << "  Pos: x = " << event_.mouseButton.x
      << ", y = " << event_.mouseButton.y << std::endl;

      break;
      case sf::Event::MouseButtonReleased:
      std::cout << "  Released: " << getMouseEnum().toStr(event_.mouseButton.button) << std::endl;
      std::cout << "  Pos: x = " << event_.mouseButton.x
      << ", y = " << event_.mouseButton.y << std::endl;
      break;
      case sf::Event::MouseMoved:
      std::cout << "  Pos: x = " << event_.mouseMove.x
      << ", y = " << event_.mouseMove.y << std::endl;
      break;
      case sf::Event::JoystickButtonPressed:
      std::cout << "  Pressed: " << getJoyButtonEnum().toStr(event_.joystickButton.button)
      << std::endl;
      break;
      case sf::Event::JoystickButtonReleased:
      std::cout << "  Released: " << getJoyButtonEnum().toStr(event_.joystickButton.button)
      << std::endl;
      break;
      case sf::Event::JoystickMoved:
      std::cout << "  JoyStick: " << getJoyNumEnum().toStr(event_.joystickMove.joystickId) << std::endl;
      std::cout << "  Axis: " << getJoyAxisEnum().toStr(event_.joystickMove.axis) << std::endl;
      std::cout << "  Value: " << event_.joystickMove.position << std::endl;
      break;
      case sf::Event::JoystickConnected:
      std::cout << "  Connected: " << getJoyNumEnum().toStr(event_.joystickConnect.joystickId)
      << std::endl;
      break;
      case sf::Event::JoystickDisconnected:
      std::cout << "  Disconnected: " << getJoyNumEnum().toStr(event_.joystickConnect.joystickId)
      << std::endl;
      break;*/
      //case sf::Event::TouchBegan:
      //  break;
      //case sf::Event::TouchMoved:
      //  break;
      //case sf::Event::TouchEnded:
      //  break;
    }
  }

  /*
  void Input::PrintKey(Keyboard::KEYS key)
  {
    system("cls");
    std::cout << "Key: " << key << " has curr value: " << currKeys.Keys[key].state << std::endl;
    //std::cout << "Key: " << key << " has last value: " << input.prevKeys.top().Keys[key].state << std::endl;
    std::cout << "Key: " << key << " has last value: " << prevKeys.Keys[key].state << std::endl;
  }

  void Input::PrintMouseInfo()
  {
    system("cls");
    std::cout << "PosX: " << currMState.state.posX << std::endl;
    std::cout << "PosY: " << currMState.state.posY << std::endl;
    std::cout << "Delta: " << currMState.state.delta << std::endl;
    std::cout << "Enter: " << currMState.state.enter << std::endl;
    std::cout << "Click: " << currMButtons.Button[Mouse::MOUSE_LEFT].state << std::endl;

  }*/

  ////////////////////////////////////////////////////////////////////////////////
  // Private Input Class Functions
  ////////////////////////////////////////////////////////////////////////////////

  const Enum& Input::getEventEnum()
  {
    return EventEnum;
  }

  const Enum& Input::getDeviceEnum()
  {
    return Dev_Mgr.DeviceEnum;
  }

}// End of SInput
