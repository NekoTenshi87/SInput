
#include <SDL\SDL.h>
#include <SDL_Demo\SDL_Converters.hpp>
#include <SInput\Input.hpp>

SInput::KEYBOARD::KEY SDL_KeyConverter(int key, int scancode)
{
  switch (key)
  {
  case SDLK_a:
    return SInput::KEYBOARD::KEY_A;
    break;

  case SDLK_b:
    return SInput::KEYBOARD::KEY_B;
    break;

  case SDLK_c:
    return SInput::KEYBOARD::KEY_C;
    break;

  case SDLK_d:
    return SInput::KEYBOARD::KEY_D;
    break;

  case SDLK_e:
    return SInput::KEYBOARD::KEY_E;
    break;

  case SDLK_f:
    return SInput::KEYBOARD::KEY_F;
    break;

  case SDLK_g:
    return SInput::KEYBOARD::KEY_G;
    break;

  case SDLK_h:
    return SInput::KEYBOARD::KEY_H;
    break;

  case SDLK_i:
    return SInput::KEYBOARD::KEY_I;
    break;

  case SDLK_j:
    return SInput::KEYBOARD::KEY_J;
    break;

  case SDLK_k:
    return SInput::KEYBOARD::KEY_K;
    break;

  case SDLK_l:
    return SInput::KEYBOARD::KEY_L;
    break;

  case SDLK_m:
    return SInput::KEYBOARD::KEY_M;
    break;

  case SDLK_n:
    return SInput::KEYBOARD::KEY_N;
    break;

  case SDLK_o:
    return SInput::KEYBOARD::KEY_O;
    break;

  case SDLK_p:
    return SInput::KEYBOARD::KEY_P;
    break;

  case SDLK_q:
    return SInput::KEYBOARD::KEY_Q;
    break;

  case SDLK_r:
    return SInput::KEYBOARD::KEY_R;
    break;

  case SDLK_s:
    return SInput::KEYBOARD::KEY_S;
    break;

  case SDLK_t:
    return SInput::KEYBOARD::KEY_T;
    break;

  case SDLK_u:
    return SInput::KEYBOARD::KEY_U;
    break;

  case SDLK_v:
    return SInput::KEYBOARD::KEY_V;
    break;

  case SDLK_w:
    return SInput::KEYBOARD::KEY_W;
    break;

  case SDLK_x:
    return SInput::KEYBOARD::KEY_X;
    break;

  case SDLK_y:
    return SInput::KEYBOARD::KEY_Y;
    break;

  case SDLK_z:
    return SInput::KEYBOARD::KEY_Z;
    break;

  case SDLK_0:
    return SInput::KEYBOARD::KEY_0;
    break;

  case SDLK_1:
    return SInput::KEYBOARD::KEY_1;
    break;

  case SDLK_2:
    return SInput::KEYBOARD::KEY_2;
    break;

  case SDLK_3:
    return SInput::KEYBOARD::KEY_3;
    break;

  case SDLK_4:
    return SInput::KEYBOARD::KEY_4;
    break;

  case SDLK_5:
    return SInput::KEYBOARD::KEY_5;
    break;

  case SDLK_6:
    return SInput::KEYBOARD::KEY_6;
    break;

  case SDLK_7:
    return SInput::KEYBOARD::KEY_7;
    break;

  case SDLK_8:
    return SInput::KEYBOARD::KEY_8;
    break;

  case SDLK_9:
    return SInput::KEYBOARD::KEY_9;
    break;

  case SDLK_ESCAPE:
    return SInput::KEYBOARD::KEY_ESC;
    break;

  case SDLK_LCTRL:
    return SInput::KEYBOARD::KEY_LEFT_CONTROL;
    break;

  case SDLK_LSHIFT:
    return SInput::KEYBOARD::KEY_LEFT_SHIFT;
    break;

  case SDLK_LALT:
    return SInput::KEYBOARD::KEY_LEFT_ALT;
    break;

  case SDLK_LGUI:
    return SInput::KEYBOARD::KEY_LEFT_SYSTEM;
    break;

  case SDLK_RCTRL:
    return SInput::KEYBOARD::KEY_RIGHT_CONTROL;
    break;

  case SDLK_RSHIFT:
    return SInput::KEYBOARD::KEY_RIGHT_SHIFT;
    break;

  case SDLK_RALT:
    return SInput::KEYBOARD::KEY_RIGHT_ALT;
    break;

  case SDLK_RGUI:
    return SInput::KEYBOARD::KEY_RIGHT_SYSTEM;
    break;

  case SDLK_MENU:
    return SInput::KEYBOARD::KEY_MENU;
    break;

  case SDLK_LEFTBRACKET:
    return SInput::KEYBOARD::KEY_LEFT_BRACKET;
    break;

  case SDLK_RIGHTBRACKET:
    return SInput::KEYBOARD::KEY_RIGHT_BRACKET;
    break;

  case SDLK_SEMICOLON:
    return SInput::KEYBOARD::KEY_SEMICOLON;
    break;

  case SDLK_COMMA:
    return SInput::KEYBOARD::KEY_COMMA;
    break;

  case SDLK_PERIOD:
    return SInput::KEYBOARD::KEY_PERIOD;
    break;

  case SDLK_BACKQUOTE:
    return SInput::KEYBOARD::KEY_APOSTROPHE;
    break;

  case SDLK_SLASH:
    return SInput::KEYBOARD::KEY_SLASH;
    break;

  case SDLK_BACKSLASH:
    return SInput::KEYBOARD::KEY_BACKSLASH;
    break;

  case SDLK_QUOTEDBL:
    return SInput::KEYBOARD::KEY_ACCENT;
    break;

  case SDLK_EQUALS:
    return SInput::KEYBOARD::KEY_EQUAL;
    break;

  case SDLK_MINUS:
    return SInput::KEYBOARD::KEY_DASH;
    break;

  case SDLK_SPACE:
    return SInput::KEYBOARD::KEY_SPACE;
    break;

  case SDLK_RETURN:
    return SInput::KEYBOARD::KEY_ENTER;
    break;

  case SDLK_BACKSPACE:
    return SInput::KEYBOARD::KEY_BACKSPACE;
    break;

  case SDLK_TAB:
    return SInput::KEYBOARD::KEY_TAB;
    break;

  case SDLK_PAGEUP:
    return SInput::KEYBOARD::KEY_PAGE_UP;
    break;

  case SDLK_PAGEDOWN:
    return SInput::KEYBOARD::KEY_PAGE_DOWN;
    break;

  case SDLK_END:
    return SInput::KEYBOARD::KEY_END;
    break;

  case SDLK_HOME:
    return SInput::KEYBOARD::KEY_HOME;
    break;

  case SDLK_INSERT:
    return SInput::KEYBOARD::KEY_INSERT;
    break;

  case SDLK_DELETE:
    return SInput::KEYBOARD::KEY_DELETE;
    break;

  case SDLK_KP_PLUS:
    return SInput::KEYBOARD::KEY_PAD_ADD;
    break;

  case SDLK_KP_MINUS:
    return SInput::KEYBOARD::KEY_PAD_SUBTRACT;
    break;

  case SDLK_KP_MULTIPLY:
    return SInput::KEYBOARD::KEY_PAD_MULTIPLY;
    break;

  case SDLK_KP_DIVIDE:
    return SInput::KEYBOARD::KEY_PAD_DIVIDE;
    break;

  case SDLK_LEFT:
    return SInput::KEYBOARD::KEY_LEFT_ARROW;
    break;

  case SDLK_RIGHT:
    return SInput::KEYBOARD::KEY_RIGHT_ARROW;
    break;

  case SDLK_UP:
    return SInput::KEYBOARD::KEY_UP_ARROW;
    break;

  case SDLK_DOWN:
    return SInput::KEYBOARD::KEY_DOWN_ARROW;
    break;

  case SDLK_KP_0:
    return SInput::KEYBOARD::KEY_PAD_0;
    break;

  case SDLK_KP_1:
    return SInput::KEYBOARD::KEY_PAD_1;
    break;

  case SDLK_KP_2:
    return SInput::KEYBOARD::KEY_PAD_2;
    break;

  case SDLK_KP_3:
    return SInput::KEYBOARD::KEY_PAD_3;
    break;

  case SDLK_KP_4:
    return SInput::KEYBOARD::KEY_PAD_4;
    break;

  case SDLK_KP_5:
    return SInput::KEYBOARD::KEY_PAD_5;
    break;

  case SDLK_KP_6:
    return SInput::KEYBOARD::KEY_PAD_6;
    break;

  case SDLK_KP_7:
    return SInput::KEYBOARD::KEY_PAD_7;
    break;

  case SDLK_KP_8:
    return SInput::KEYBOARD::KEY_PAD_8;
    break;

  case SDLK_KP_9:
    return SInput::KEYBOARD::KEY_PAD_9;
    break;

  case SDLK_F1:
    return SInput::KEYBOARD::KEY_F1;
    break;

  case SDLK_F2:
    return SInput::KEYBOARD::KEY_F2;
    break;

  case SDLK_F3:
    return SInput::KEYBOARD::KEY_F3;
    break;

  case SDLK_F4:
    return SInput::KEYBOARD::KEY_F4;
    break;

  case SDLK_F5:
    return SInput::KEYBOARD::KEY_F5;
    break;

  case SDLK_F6:
    return SInput::KEYBOARD::KEY_F6;
    break;

  case SDLK_F7:
    return SInput::KEYBOARD::KEY_F7;
    break;

  case SDLK_F8:
    return SInput::KEYBOARD::KEY_F8;
    break;

  case SDLK_F9:
    return SInput::KEYBOARD::KEY_F9;
    break;

  case SDLK_F10:
    return SInput::KEYBOARD::KEY_F10;
    break;

  case SDLK_F11:
    return SInput::KEYBOARD::KEY_F11;
    break;

  case SDLK_F12:
    return SInput::KEYBOARD::KEY_F12;
    break;

  case SDLK_F13:
    return SInput::KEYBOARD::KEY_F13;
    break;

  case SDLK_F14:
    return SInput::KEYBOARD::KEY_F14;
    break;

  case SDLK_F15:
    return SInput::KEYBOARD::KEY_F15;
    break;

  case SDLK_PAUSE:
    return SInput::KEYBOARD::KEY_PAUSE;
    break;

  case SDLK_CAPSLOCK:
    return SInput::KEYBOARD::KEY_CAPS_LOCK;
    break;

  case SDLK_SCROLLLOCK:
    return SInput::KEYBOARD::KEY_SCROLL_LOCK;
    break;

  case SDLK_NUMLOCKCLEAR:
    return SInput::KEYBOARD::KEY_NUM_LOCK;
    break;

  case SDLK_PRINTSCREEN:
    return SInput::KEYBOARD::KEY_PRINT_SCREEN;
    break;

  case SDLK_KP_PERIOD:
    return SInput::KEYBOARD::KEY_PAD_DECIMAL;
    break;

  case SDLK_KP_ENTER:
    return SInput::KEYBOARD::KEY_PAD_ENTER;
    break;

  case SDLK_KP_EQUALS:
    return SInput::KEYBOARD::KEY_PAD_EQUAL;
    break;

  default:
    return SInput::KEYBOARD::UNKNOWN_KEY;
    break;
  }
}

SInput::KEYBOARD::ACTION SDL_KeyActionConverter(int action)
{
  switch (action)
  {
    case SDL_RELEASED:
      return SInput::KEYBOARD::RELEASED;
      break;

    case SDL_PRESSED:
      return SInput::KEYBOARD::PRESSED;
      break;

    default:
      return SInput::KEYBOARD::UNKNOWN_ACTION;
      break;
  }
}

int SDL_ModConverter(int mods)
{
  int s_mods = SInput::KEYBOARD::MOD_NONE;

  if (mods & KMOD_SHIFT)
  {
    s_mods |= SInput::KEYBOARD::MOD_SHIFT;
  }

  if (mods & KMOD_CTRL)
  {
    s_mods |= SInput::KEYBOARD::MOD_CTRL;
  }

  if (mods & KMOD_ALT)
  {
    s_mods |= SInput::KEYBOARD::MOD_ALT;
  }

  if (mods & KMOD_GUI)
  {
    s_mods |= SInput::KEYBOARD::MOD_SYSTEM;
  }

  return s_mods;
}

SInput::MOUSE::BUTTON SDL_MouseConverter(int button)
{
  switch (button)
  {
  case SDL_BUTTON_LEFT:
    return SInput::MOUSE::BUTTON_LEFT;
    break;

  case SDL_BUTTON_RIGHT:
    return SInput::MOUSE::BUTTON_RIGHT;
    break;

  case SDL_BUTTON_MIDDLE:
    return SInput::MOUSE::BUTTON_MIDDLE;
    break;

  case SDL_BUTTON_X1:
    return SInput::MOUSE::BUTTON_4;
    break;

  case SDL_BUTTON_X2:
    return SInput::MOUSE::BUTTON_5;
    break;

  default:
    return SInput::MOUSE::UNKNOWN_BUTTON;
    break;
  }
}

SInput::MOUSE::ACTION SDL_MouseActionConverter(int action)
{
  switch (action)
  {
  case SDL_RELEASED:
    return SInput::MOUSE::RELEASED;
    break;

  case SDL_PRESSED:
    return SInput::MOUSE::PRESSED;
    break;

  default:
    return SInput::MOUSE::UNKNOWN_ACTION;
    break;
  }
}

SInput::GAMEPAD::STATUS SDL_GamePadStatusConverter(int status)
{
  switch (status)
  {
    case SDL_TRUE:
      return SInput::GAMEPAD::CONNECTED;
      break;

    case SDL_FALSE:
      return SInput::GAMEPAD::DISCONNECTED;
      break;

    default:
      return SInput::GAMEPAD::UNKNOWN_STATUS;
      break;
  }
}

SInput::GAMEPAD::BUTTON SDL_GamePadButtonConverter(int button)
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

SInput::GAMEPAD::AXIS SDL_GamePadAxisConverter(int axis)
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

SInput::GAMEPAD::ACTION SDL_GamePadActionConverter(int action)
{
  switch (action)
  {
    case SDL_RELEASED:
      return SInput::GAMEPAD::RELEASED;
      break;

    case SDL_PRESSED:
      return SInput::GAMEPAD::PRESSED;
      break;

    default:
      return SInput::GAMEPAD::UNKNOWN_ACTION;
      break;
  }
}

