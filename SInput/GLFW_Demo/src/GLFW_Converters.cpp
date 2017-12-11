
#include <GLFW\glfw3.h>
#include <GLFW_Demo\GLFW_Converters.hpp>
#include <SInput\Input.hpp>

SInput::KEYBOARD::KEY GLFW_KeyConverter(int key, int scancode)
{
  switch (key)
  {
  case GLFW_KEY_A:
    return SInput::KEYBOARD::KEY_A;
    break;

  case GLFW_KEY_B:
    return SInput::KEYBOARD::KEY_B;
    break;

  case GLFW_KEY_C:
    return SInput::KEYBOARD::KEY_C;
    break;

  case GLFW_KEY_D:
    return SInput::KEYBOARD::KEY_D;
    break;

  case GLFW_KEY_E:
    return SInput::KEYBOARD::KEY_E;
    break;

  case GLFW_KEY_F:
    return SInput::KEYBOARD::KEY_F;
    break;

  case GLFW_KEY_G:
    return SInput::KEYBOARD::KEY_G;
    break;

  case GLFW_KEY_H:
    return SInput::KEYBOARD::KEY_H;
    break;

  case GLFW_KEY_I:
    return SInput::KEYBOARD::KEY_I;
    break;

  case GLFW_KEY_J:
    return SInput::KEYBOARD::KEY_J;
    break;

  case GLFW_KEY_K:
    return SInput::KEYBOARD::KEY_K;
    break;

  case GLFW_KEY_L:
    return SInput::KEYBOARD::KEY_L;
    break;

  case GLFW_KEY_M:
    return SInput::KEYBOARD::KEY_M;
    break;

  case GLFW_KEY_N:
    return SInput::KEYBOARD::KEY_N;
    break;

  case GLFW_KEY_O:
    return SInput::KEYBOARD::KEY_O;
    break;

  case GLFW_KEY_P:
    return SInput::KEYBOARD::KEY_P;
    break;

  case GLFW_KEY_Q:
    return SInput::KEYBOARD::KEY_Q;
    break;

  case GLFW_KEY_R:
    return SInput::KEYBOARD::KEY_R;
    break;

  case GLFW_KEY_S:
    return SInput::KEYBOARD::KEY_S;
    break;

  case GLFW_KEY_T:
    return SInput::KEYBOARD::KEY_T;
    break;

  case GLFW_KEY_U:
    return SInput::KEYBOARD::KEY_U;
    break;

  case GLFW_KEY_V:
    return SInput::KEYBOARD::KEY_V;
    break;

  case GLFW_KEY_W:
    return SInput::KEYBOARD::KEY_W;
    break;

  case GLFW_KEY_X:
    return SInput::KEYBOARD::KEY_X;
    break;

  case GLFW_KEY_Y:
    return SInput::KEYBOARD::KEY_Y;
    break;

  case GLFW_KEY_Z:
    return SInput::KEYBOARD::KEY_Z;
    break;

  case GLFW_KEY_0:
    return SInput::KEYBOARD::KEY_0;
    break;

  case GLFW_KEY_1:
    return SInput::KEYBOARD::KEY_1;
    break;

  case GLFW_KEY_2:
    return SInput::KEYBOARD::KEY_2;
    break;

  case GLFW_KEY_3:
    return SInput::KEYBOARD::KEY_3;
    break;

  case GLFW_KEY_4:
    return SInput::KEYBOARD::KEY_4;
    break;

  case GLFW_KEY_5:
    return SInput::KEYBOARD::KEY_5;
    break;

  case GLFW_KEY_6:
    return SInput::KEYBOARD::KEY_6;
    break;

  case GLFW_KEY_7:
    return SInput::KEYBOARD::KEY_7;
    break;

  case GLFW_KEY_8:
    return SInput::KEYBOARD::KEY_8;
    break;

  case GLFW_KEY_9:
    return SInput::KEYBOARD::KEY_9;
    break;

  case GLFW_KEY_ESCAPE:
    return SInput::KEYBOARD::KEY_ESC;
    break;

  case GLFW_KEY_LEFT_CONTROL:
    return SInput::KEYBOARD::KEY_LEFT_CONTROL;
    break;

  case GLFW_KEY_LEFT_SHIFT:
    return SInput::KEYBOARD::KEY_LEFT_SHIFT;
    break;

  case GLFW_KEY_LEFT_ALT:
    return SInput::KEYBOARD::KEY_LEFT_ALT;
    break;

  case GLFW_KEY_LEFT_SUPER:
    return SInput::KEYBOARD::KEY_LEFT_SYSTEM;
    break;

  case GLFW_KEY_RIGHT_CONTROL:
    return SInput::KEYBOARD::KEY_RIGHT_CONTROL;
    break;

  case GLFW_KEY_RIGHT_SHIFT:
    return SInput::KEYBOARD::KEY_RIGHT_SHIFT;
    break;

  case GLFW_KEY_RIGHT_ALT:
    return SInput::KEYBOARD::KEY_RIGHT_ALT;
    break;

  case GLFW_KEY_RIGHT_SUPER:
    return SInput::KEYBOARD::KEY_RIGHT_SYSTEM;
    break;

  case GLFW_KEY_MENU:
    return SInput::KEYBOARD::KEY_MENU;
    break;

  case GLFW_KEY_LEFT_BRACKET:
    return SInput::KEYBOARD::KEY_LEFT_BRACKET;
    break;

  case GLFW_KEY_RIGHT_BRACKET:
    return SInput::KEYBOARD::KEY_RIGHT_BRACKET;
    break;

  case GLFW_KEY_SEMICOLON:
    return SInput::KEYBOARD::KEY_SEMICOLON;
    break;

  case GLFW_KEY_COMMA:
    return SInput::KEYBOARD::KEY_COMMA;
    break;

  case GLFW_KEY_PERIOD:
    return SInput::KEYBOARD::KEY_PERIOD;
    break;

  case GLFW_KEY_APOSTROPHE:
    return SInput::KEYBOARD::KEY_APOSTROPHE;
    break;

  case GLFW_KEY_SLASH:
    return SInput::KEYBOARD::KEY_SLASH;
    break;

  case GLFW_KEY_BACKSLASH:
    return SInput::KEYBOARD::KEY_BACKSLASH;
    break;

  case GLFW_KEY_GRAVE_ACCENT:
    return SInput::KEYBOARD::KEY_ACCENT;
    break;

  case GLFW_KEY_EQUAL:
    return SInput::KEYBOARD::KEY_EQUAL;
    break;

  case GLFW_KEY_MINUS:
    return SInput::KEYBOARD::KEY_DASH;
    break;

  case GLFW_KEY_SPACE:
    return SInput::KEYBOARD::KEY_SPACE;
    break;

  case GLFW_KEY_ENTER:
    return SInput::KEYBOARD::KEY_ENTER;
    break;

  case GLFW_KEY_BACKSPACE:
    return SInput::KEYBOARD::KEY_BACKSPACE;
    break;

  case GLFW_KEY_TAB:
    return SInput::KEYBOARD::KEY_TAB;
    break;

  case GLFW_KEY_PAGE_UP:
    return SInput::KEYBOARD::KEY_PAGE_UP;
    break;

  case GLFW_KEY_PAGE_DOWN:
    return SInput::KEYBOARD::KEY_PAGE_DOWN;
    break;

  case GLFW_KEY_END:
    return SInput::KEYBOARD::KEY_END;
    break;

  case GLFW_KEY_HOME:
    return SInput::KEYBOARD::KEY_HOME;
    break;

  case GLFW_KEY_INSERT:
    return SInput::KEYBOARD::KEY_INSERT;
    break;

  case GLFW_KEY_DELETE:
    return SInput::KEYBOARD::KEY_DELETE;
    break;

  case GLFW_KEY_KP_ADD:
    return SInput::KEYBOARD::KEY_PAD_ADD;
    break;

  case GLFW_KEY_KP_SUBTRACT:
    return SInput::KEYBOARD::KEY_PAD_SUBTRACT;
    break;

  case GLFW_KEY_KP_MULTIPLY:
    return SInput::KEYBOARD::KEY_PAD_MULTIPLY;
    break;

  case GLFW_KEY_KP_DIVIDE:
    return SInput::KEYBOARD::KEY_PAD_DIVIDE;
    break;

  case GLFW_KEY_LEFT:
    return SInput::KEYBOARD::KEY_LEFT_ARROW;
    break;

  case GLFW_KEY_RIGHT:
    return SInput::KEYBOARD::KEY_RIGHT_ARROW;
    break;

  case GLFW_KEY_UP:
    return SInput::KEYBOARD::KEY_UP_ARROW;
    break;

  case GLFW_KEY_DOWN:
    return SInput::KEYBOARD::KEY_DOWN_ARROW;
    break;

  case GLFW_KEY_KP_0:
    return SInput::KEYBOARD::KEY_PAD_0;
    break;

  case GLFW_KEY_KP_1:
    return SInput::KEYBOARD::KEY_PAD_1;
    break;

  case GLFW_KEY_KP_2:
    return SInput::KEYBOARD::KEY_PAD_2;
    break;

  case GLFW_KEY_KP_3:
    return SInput::KEYBOARD::KEY_PAD_3;
    break;

  case GLFW_KEY_KP_4:
    return SInput::KEYBOARD::KEY_PAD_4;
    break;

  case GLFW_KEY_KP_5:
    return SInput::KEYBOARD::KEY_PAD_5;
    break;

  case GLFW_KEY_KP_6:
    return SInput::KEYBOARD::KEY_PAD_6;
    break;

  case GLFW_KEY_KP_7:
    return SInput::KEYBOARD::KEY_PAD_7;
    break;

  case GLFW_KEY_KP_8:
    return SInput::KEYBOARD::KEY_PAD_8;
    break;

  case GLFW_KEY_KP_9:
    return SInput::KEYBOARD::KEY_PAD_9;
    break;

  case GLFW_KEY_F1:
    return SInput::KEYBOARD::KEY_F1;
    break;

  case GLFW_KEY_F2:
    return SInput::KEYBOARD::KEY_F2;
    break;

  case GLFW_KEY_F3:
    return SInput::KEYBOARD::KEY_F3;
    break;

  case GLFW_KEY_F4:
    return SInput::KEYBOARD::KEY_F4;
    break;

  case GLFW_KEY_F5:
    return SInput::KEYBOARD::KEY_F5;
    break;

  case GLFW_KEY_F6:
    return SInput::KEYBOARD::KEY_F6;
    break;

  case GLFW_KEY_F7:
    return SInput::KEYBOARD::KEY_F7;
    break;

  case GLFW_KEY_F8:
    return SInput::KEYBOARD::KEY_F8;
    break;

  case GLFW_KEY_F9:
    return SInput::KEYBOARD::KEY_F9;
    break;

  case GLFW_KEY_F10:
    return SInput::KEYBOARD::KEY_F10;
    break;

  case GLFW_KEY_F11:
    return SInput::KEYBOARD::KEY_F11;
    break;

  case GLFW_KEY_F12:
    return SInput::KEYBOARD::KEY_F12;
    break;

  case GLFW_KEY_F13:
    return SInput::KEYBOARD::KEY_F13;
    break;

  case GLFW_KEY_F14:
    return SInput::KEYBOARD::KEY_F14;
    break;

  case GLFW_KEY_F15:
    return SInput::KEYBOARD::KEY_F15;
    break;

  case GLFW_KEY_PAUSE:
    return SInput::KEYBOARD::KEY_PAUSE;
    break;

  case GLFW_KEY_CAPS_LOCK:
    return SInput::KEYBOARD::KEY_CAPS_LOCK;
    break;

  case GLFW_KEY_SCROLL_LOCK:
    return SInput::KEYBOARD::KEY_SCROLL_LOCK;
    break;

  case GLFW_KEY_NUM_LOCK:
    return SInput::KEYBOARD::KEY_NUM_LOCK;
    break;

  case GLFW_KEY_PRINT_SCREEN:
    return SInput::KEYBOARD::KEY_PRINT_SCREEN;
    break;

  case GLFW_KEY_KP_DECIMAL:
    return SInput::KEYBOARD::KEY_PAD_DECIMAL;
    break;

  case GLFW_KEY_KP_ENTER:
    return SInput::KEYBOARD::KEY_PAD_ENTER;
    break;

  case GLFW_KEY_KP_EQUAL:
    return SInput::KEYBOARD::KEY_PAD_EQUAL;
    break;

  default:
    return SInput::KEYBOARD::UNKNOWN_KEY;
    break;
  }
}

SInput::KEYBOARD::ACTION GLFW_KeyActionConverter(int action)
{
  switch (action)
  {
    case GLFW_RELEASE:
      return SInput::KEYBOARD::RELEASED;
      break;

    case GLFW_PRESS:
      return SInput::KEYBOARD::PRESSED;
      break;

    default:
      return SInput::KEYBOARD::UNKNOWN_ACTION;
      break;
  }
}

int GLFW_ModConverter(int mods)
{
  int s_mods = SInput::KEYBOARD::MOD_NONE;

  if (mods & GLFW_MOD_SHIFT)
  {
    s_mods |= SInput::KEYBOARD::MOD_SHIFT;
  }

  if (mods & GLFW_MOD_CONTROL)
  {
    s_mods |= SInput::KEYBOARD::MOD_CTRL;
  }

  if (mods & GLFW_MOD_ALT)
  {
    s_mods |= SInput::KEYBOARD::MOD_ALT;
  }

  if (mods & GLFW_MOD_SUPER)
  {
    s_mods |= SInput::KEYBOARD::MOD_SYSTEM;
  }

  return s_mods;
}

SInput::MOUSE::BUTTON GLFW_MouseConverter(int button)
{
  switch (button)
  {
  case GLFW_MOUSE_BUTTON_1:
    return SInput::MOUSE::BUTTON_LEFT;
    break;

  case GLFW_MOUSE_BUTTON_2:
    return SInput::MOUSE::BUTTON_RIGHT;
    break;

  case GLFW_MOUSE_BUTTON_3:
    return SInput::MOUSE::BUTTON_MIDDLE;
    break;

  case GLFW_MOUSE_BUTTON_4:
    return SInput::MOUSE::BUTTON_4;
    break;

  case GLFW_MOUSE_BUTTON_5:
    return SInput::MOUSE::BUTTON_5;
    break;

  case GLFW_MOUSE_BUTTON_6:
    return SInput::MOUSE::BUTTON_6;
    break;

  case GLFW_MOUSE_BUTTON_7:
    return SInput::MOUSE::BUTTON_7;
    break;

  case GLFW_MOUSE_BUTTON_8:
    return SInput::MOUSE::BUTTON_8;
    break;

  default:
    return SInput::MOUSE::UNKNOWN_BUTTON;
    break;
  }
}

SInput::MOUSE::ACTION GLFW_MouseActionConverter(int action)
{
  switch (action)
  {
  case GLFW_RELEASE:
    return SInput::MOUSE::RELEASED;
    break;

  case GLFW_PRESS:
    return SInput::MOUSE::PRESSED;
    break;

  default:
    return SInput::MOUSE::UNKNOWN_ACTION;
    break;
  }
}

SInput::GAMEPAD::STATUS GLFW_GamePadStatusConverter(int status)
{
  switch (status)
  {
    case GLFW_CONNECTED:
      return SInput::GAMEPAD::CONNECTED;
      break;

    case GLFW_DISCONNECTED:
      return SInput::GAMEPAD::DISCONNECTED;
      break;

    default:
      return SInput::GAMEPAD::UNKNOWN_STATUS;
      break;
  }
}

SInput::GAMEPAD::BUTTON GLFW_GamePadButtonConverter(int button)
{
  switch (button)
  {
    case 0:
      return SInput::GAMEPAD::BUTTON_1;
      break;

    case 1:
      return SInput::GAMEPAD::BUTTON_2;
      break;

    case 2:
      return SInput::GAMEPAD::BUTTON_3;
      break;

    case 3:
      return SInput::GAMEPAD::BUTTON_4;
      break;

    case 4:
      return SInput::GAMEPAD::BUTTON_5;
      break;

    case 5:
      return SInput::GAMEPAD::BUTTON_6;
      break;

    case 6:
      return SInput::GAMEPAD::BUTTON_7;
      break;

    case 7:
      return SInput::GAMEPAD::BUTTON_8;
      break;

    case 8:
      return SInput::GAMEPAD::BUTTON_9;
      break;

    case 9:
      return SInput::GAMEPAD::BUTTON_10;
      break;

    case 10:
      return SInput::GAMEPAD::BUTTON_11;
      break;

    case 11:
      return SInput::GAMEPAD::BUTTON_12;
      break;

    case 12:
      return SInput::GAMEPAD::BUTTON_13;
      break;

    case 13:
      return SInput::GAMEPAD::BUTTON_14;
      break;

    case 14:
      return SInput::GAMEPAD::BUTTON_15;
      break;

    case 15:
      return SInput::GAMEPAD::BUTTON_16;
      break;

    default:
      return SInput::GAMEPAD::UNKNOWN_BUTTON;
      break;
  }
}

SInput::GAMEPAD::AXIS GLFW_GamePadAxisConverter(int axis)
{
  switch (axis)
  {
    case 0:
      return SInput::GAMEPAD::LEFT_X_AXIS;
      break;

    case 1:
      return SInput::GAMEPAD::LEFT_Y_AXIS;
      break;

    case 2:
      return SInput::GAMEPAD::RIGHT_X_AXIS;
      break;

    case 3:
      return SInput::GAMEPAD::RIGHT_Y_AXIS;
      break;

    case 4:
      return SInput::GAMEPAD::LEFT_TRIGGER_AXIS;
      break;

    case 5:
      return SInput::GAMEPAD::RIGHT_TRIGGER_AXIS;
      break;

    default:
      return SInput::GAMEPAD::UNKNOWN_AXIS;
      break;
  }
}

SInput::GAMEPAD::ACTION GLFW_GamePadActionConverter(unsigned char action)
{
  switch (action)
  {
    case 0:
      return SInput::GAMEPAD::RELEASED;
      break;

    case 1:
      return SInput::GAMEPAD::PRESSED;
      break;

    default:
      return SInput::GAMEPAD::UNKNOWN_ACTION;
      break;
  }
}

