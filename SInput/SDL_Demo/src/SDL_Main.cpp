
#include <IMGUI/imgui.h>
#include <SDL_Demo/SDL_ImGui_gl3.hpp>
#include <GL/gl3w.h>
#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>
#include <SInput/SInput.hpp>

#include <Demo_Lib\ImGui_SInput_Display.hpp>
#include <SDL_Demo/SDL_Converters.hpp>

// Gets rid of Console Window
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

static ImGui_SInput_Display g_display;

static SDL_Window* sdl_window = NULL;
static bool done = false;

void key_callback(SDL_Window* window, int key, int scancode, int action, int mods)
{
  if (!g_display.is_active)
  {
    SInput::KEYBOARD::ACTION S_Action = SDL_KeyActionConverter(action);

    if (S_Action != SInput::KEYBOARD::UNKNOWN_ACTION)
    {
      SInput::KEYBOARD::KEY S_Key = SDL_KeyConverter(key);

      SInput::Keyboard()->UpdateKey(S_Key, S_Action, g_display.show_keys);
      SInput::Keyboard()->UpdateMods(SDL_ModConverter(mods));
    }
  }
  else
  {
    if (SInput::Keyboard()->getNextKey && SInput::Keyboard()->nextKey == SInput::KEYBOARD::KEY::UNKNOWN_KEY)
    {
      SInput::KEYBOARD::ACTION S_Action = SDL_KeyActionConverter(action);

      if (S_Action != SInput::KEYBOARD::KEY::UNKNOWN_KEY)
      {
        SInput::Keyboard()->nextKey = SDL_KeyConverter(key);
      }
    }
    else
    {
      SDL_ImGui_GL3_KeyCallback(window, key, scancode, action, mods);
    }
  }

  if (key == SDLK_i && mods | KMOD_CTRL && action == SDL_PRESSED)
  {
    g_display.is_active ^= 1;
  }
}

void mouse_button_callback(SDL_Window* window, int button, int action, int mods)
{
  if (!g_display.is_active)
  {
    SInput::MOUSE::ACTION S_Action = SDL_MouseActionConverter(action);

    if (S_Action != SInput::MOUSE::UNKNOWN_ACTION)
    {
      SInput::MOUSE::BUTTON S_Button = SDL_MouseConverter(button);

      SInput::Mouse()->UpdateButton(S_Button, S_Action, g_display.show_mouse_buttons);
      SInput::Keyboard()->UpdateMods(SDL_ModConverter(mods));
    }
  }
  else
  {
    if (SInput::Mouse()->getNextButton && SInput::Mouse()->nextButton == SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
    {
      SInput::MOUSE::ACTION S_Action = SDL_MouseActionConverter(action);

      if (S_Action != SInput::MOUSE::UNKNOWN_ACTION)
      {
        SInput::Mouse()->nextButton = SDL_MouseConverter(button);
      }
    }
    else
    {
      SDL_ImGui_GL3_MouseButtonCallback(window, button, action, mods);
    }
  }

}

void mouse_enter_callback(SDL_Window* window, int enter)
{
  if (!g_display.is_active)
  {
    switch (enter)
    {
      case SDL_FALSE:
        SInput::Mouse()->UpdateMouseEnter(false, g_display.show_mouse_enter);
        break;

      case SDL_TRUE:
        SInput::Mouse()->UpdateMouseEnter(true, g_display.show_mouse_enter);
        break;

      default:
        break;
    }
  }
}

void mouse_pos_callback(SDL_Window* window, int posX, int posY)
{
  if (!g_display.is_active)
  {
    SInput::MousePos pos(posX, posY);

    SInput::Mouse()->UpdateMousePos(pos, g_display.show_mouse_pos);
  }
}

void mouse_scroll_callback(SDL_Window* window, double dX, double dY)
{
  if (!g_display.is_active)
  {
    SInput::Mouse()->UpdateMouseWheel(static_cast<int>(std::floor(-dX)), static_cast<int>(std::floor(dY)), g_display.show_mouse_scroll);
  }
  else
  {
    SDL_ImGui_GL3_ScrollCallback(window, dX, dY);
  }

  //std::cout << "MouseWheel: X: " << SInput::Mouse()->GetDeltaX() << " Y: " << SInput::Mouse()->GetDeltaY() << std::endl;
}

void focus_callback(SDL_Window* window, int focused)
{
  /*
  if (focused == GLFW_TRUE)
  {
    std::cout << "GLFW Window Gained Focus!" << std::endl;
  }
  else
  {
    std::cout << "GLFW Window Lost Focus!" << std::endl;
  }
  */
}

void gamepad_connection_callback(SDL_Window* window, int gp_num, int connect)
{
  switch (connect)
  {
  case SDL_FALSE:
    SInput::GamePad(gp_num)->UpdateConnection(gp_num, SInput::GAMEPAD::DISCONNECTED, g_display.show_gamepad_connect);
    break;

  case SDL_TRUE:
    SInput::GamePad(gp_num)->UpdateConnection(gp_num, SInput::GAMEPAD::CONNECTED, g_display.show_gamepad_connect);
    break;

  default:
    break;
  }
}


void gamepad_button_callback(SDL_Window* window, int gp_num, int button, unsigned char action)
{
  if (!g_display.is_active)
  {
    SInput::GAMEPAD::ACTION S_Action = SDL_GamePadActionConverter(action);

    if (S_Action != SInput::GAMEPAD::UNKNOWN_ACTION)
    {
      SInput::GAMEPAD::BUTTON S_Button = SDL_GamePadButtonConverter(button);

      SInput::GamePad(gp_num)->UpdateButton(gp_num, S_Button, S_Action, g_display.show_gamepad_buttons);
    }
  }
  else
  {
    if (SInput::GamePad(gp_num)->getNextButton && SInput::GamePad(gp_num)->nextButton == SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
    {
      SInput::GAMEPAD::ACTION S_Action = SDL_GamePadActionConverter(action);

      if (S_Action != SInput::GAMEPAD::UNKNOWN_ACTION)
      {
        SInput::GamePad(gp_num)->nextButton = SDL_GamePadButtonConverter(button);
      }
    }
  }

}

void gamepad_axis_callback(SDL_Window* window, int gp_num, int axis, float delta)
{
  if (!g_display.is_active)
  {
    SInput::GAMEPAD::AXIS S_Axis = SDL_GamePadAxisConverter(axis);

    SInput::GamePad(gp_num)->UpdateAxis(gp_num, S_Axis, delta, g_display.show_gamepad_axis);
  }
  else
  {
    if (SInput::GamePad(gp_num)->getNextAxis && SInput::GamePad(gp_num)->nextAxis == SInput::GAMEPAD::AXIS::UNKNOWN_AXIS)
    {
      if (std::abs(delta) > 0.5f)
      {
        SInput::GamePad(gp_num)->nextAxis = SDL_GamePadAxisConverter(axis);
      }
    }
  }
}

/*
void poll_joysticks()
{
  for (unsigned i = 0; i < SInput::GAMEPAD::NUMBEROFGAMEPADS; ++i)
  {
    int value = SDL_NumJoysticks();

    if ((int)SInput::GamePad(i)->IsConnected() != value)
    {
      gamepad_connection_callback(sdl_window, i, value);
    }
  }
}

// Please don't blame me for this utter trash way of updating GamePad
// GLFW needs to update their archaic way of grabbing joystick info
void joystick_refresh()
{
  for (int i = 0; i < SInput::GAMEPAD::NUMBEROFGAMEPADS; ++i)
  {
    if (SInput::GamePad(i)->IsConnected())
    {
      int button_count, axis_count;

      const unsigned char* glfw_buttons = glfwGetJoystickButtons(i, &button_count);

      for (int j = 0; j < SInput::GAMEPAD::NUMBEROFGPBUTTONS; ++j)
      {
        if (j < button_count)
        {
          SInput::GAMEPAD::BUTTON S_Button = GLFW_GamePadButtonConverter(j);
          SInput::GAMEPAD::ACTION S_Action = GLFW_GamePadActionConverter(glfw_buttons[j]);

          if (SInput::GamePad(i)->ButtonPressed(S_Button) != (bool)S_Action)
          {
            gamepad_button_callback(glfw_window, i, j, glfw_buttons[j]);
          }
        }
        else
        {
          break;
        }
      }

      const float* glfw_axis = glfwGetJoystickAxes(i, &axis_count);

      for (int j = 0; j < SInput::GAMEPAD::NUMBEROFGPAXIS; ++j)
      {
        if (j < axis_count)
        {
          SInput::GAMEPAD::AXIS S_Axis = GLFW_GamePadAxisConverter(j);

          if (j < SInput::GAMEPAD::LEFT_TRIGGER_AXIS)
          {
            if (SInput::GamePad(i)->GetAxis(S_Axis) != glfw_axis[j])
            {
              gamepad_axis_callback(glfw_window, i, j, glfw_axis[j]);
            }
          }
          else
          {
            if (SInput::GamePad(i)->GetAxis(S_Axis) != ((glfw_axis[j] + 1.0f) / 2.0f))
            {
              gamepad_axis_callback(glfw_window, i, j, (glfw_axis[j] + 1.0f) / 2.0f);
            }
          }
        }
        else
        {
          break;
        }
      }
    }
  }
}*/

void PullEvents()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    //if (!g_display.is_active)
    //{
      switch (event.type)
      {
        case SDL_KEYDOWN:
        {
          key_callback(sdl_window, event.key.keysym.sym, event.key.keysym.scancode, SDL_PRESSED, event.key.keysym.mod);
          break;
        }
        case SDL_KEYUP:
        {
          key_callback(sdl_window, event.key.keysym.sym, event.key.keysym.scancode, SDL_RELEASED, event.key.keysym.mod);
          break;
        }
        case SDL_MOUSEWHEEL:
        {
          mouse_scroll_callback(sdl_window, event.wheel.x, event.wheel.y);
          break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
          mouse_button_callback(sdl_window, event.button.button, SDL_PRESSED, 0);
          break;
        }
        case SDL_MOUSEBUTTONUP:
        {
          mouse_button_callback(sdl_window, event.button.button, SDL_RELEASED, 0);
          break;
        }
        case SDL_MOUSEMOTION:
        {
          mouse_pos_callback(sdl_window, event.motion.x, event.motion.y);
          break;
        }
        case SDL_JOYAXISMOTION:
        {
          gamepad_axis_callback(sdl_window, event.jdevice.which, event.jaxis.axis, (float)event.jaxis.value);
          break;
        }
        case SDL_JOYBUTTONDOWN:
        {
          gamepad_button_callback(sdl_window, event.jdevice.which, event.jbutton.button, SDL_PRESSED);
          break;
        }
        case SDL_JOYBUTTONUP:
        {
          gamepad_button_callback(sdl_window, event.jdevice.which, event.jbutton.button, SDL_RELEASED);
          break;
        }
        case SDL_JOYDEVICEADDED:
        {
          gamepad_connection_callback(sdl_window, event.jdevice.which, SDL_TRUE);
          break;
        }
        case SDL_JOYDEVICEREMOVED:
        {
          gamepad_connection_callback(sdl_window, event.jdevice.which, SDL_FALSE);
          break;
        }
        case SDL_QUIT:
        {
          done = true;
          break;
        }
      }
    //}
    //else
    //{
      //SDL_ImGui_GL3_ProcessEvent(&event);
    //}
  }
}

int main(int argc, char* args[])
{
  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
  {
    printf("Error: %s\n", SDL_GetError());
    return -1;
  }

  // Setup window
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_DisplayMode current;
  SDL_GetCurrentDisplayMode(0, &current);

  sdl_window = SDL_CreateWindow("SLD Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, current.w/2, current.h/2, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  SDL_GLContext glcontext = SDL_GL_CreateContext(sdl_window);

  gl3wInit();

  // Setup ImGui binding
  SDL_ImGui_GL3_Init(sdl_window);

  SInput::Init();

  // Testing Bindings
  enum PLAYER_EVENTS
  {
    P_MOVE_UP,
    P_MOVE_LEFT,
    P_MOVE_DOWN,
    P_MOVE_RIGHT,
    P_JUMP,
    P_RUN,
    P_CROUCH,
    P_SHOOT,
    P_AIM,
    P_MELEE
  };

  SInput::Keyboard()->BindKey(P_MOVE_UP, SInput::KEYBOARD::KEY::KEY_W);
  SInput::Keyboard()->BindKey(P_MOVE_LEFT, SInput::KEYBOARD::KEY::KEY_A);
  SInput::Keyboard()->BindKey(P_MOVE_DOWN, SInput::KEYBOARD::KEY::KEY_S);
  SInput::Keyboard()->BindKey(P_MOVE_RIGHT, SInput::KEYBOARD::KEY::KEY_D);
  SInput::Keyboard()->BindKey(P_JUMP, SInput::KEYBOARD::KEY::KEY_SPACE);
  SInput::Keyboard()->BindKey(P_RUN, SInput::KEYBOARD::KEY::KEY_LEFT_SHIFT);
  SInput::Keyboard()->BindKey(P_CROUCH, SInput::KEYBOARD::KEY::KEY_LEFT_CONTROL);

  SInput::Mouse()->BindButton(P_SHOOT, SInput::MOUSE::BUTTON::BUTTON_LEFT);
  SInput::Mouse()->BindButton(P_AIM, SInput::MOUSE::BUTTON::BUTTON_RIGHT);
  SInput::Mouse()->BindButton(P_MELEE, SInput::MOUSE::BUTTON::BUTTON_4);

  SInput::GamePad(0)->BindButton(P_MOVE_UP, SInput::GAMEPAD::BUTTON::BUTTON_11);
  SInput::GamePad(0)->BindButton(P_MOVE_LEFT, SInput::GAMEPAD::BUTTON::BUTTON_14);
  SInput::GamePad(0)->BindButton(P_MOVE_DOWN, SInput::GAMEPAD::BUTTON::BUTTON_13);
  SInput::GamePad(0)->BindButton(P_MOVE_RIGHT, SInput::GAMEPAD::BUTTON::BUTTON_12);
  SInput::GamePad(0)->BindButton(P_JUMP, SInput::GAMEPAD::BUTTON::BUTTON_1);
  SInput::GamePad(0)->BindButton(P_RUN, SInput::GAMEPAD::BUTTON::BUTTON_5);
  SInput::GamePad(0)->BindButton(P_CROUCH, SInput::GAMEPAD::BUTTON::BUTTON_2);
  SInput::GamePad(0)->BindButton(P_MELEE, SInput::GAMEPAD::BUTTON::BUTTON_3);

  SInput::GamePad(0)->BindAxis(P_SHOOT, SInput::GAMEPAD::AXIS::RIGHT_TRIGGER_AXIS);
  SInput::GamePad(0)->BindAxis(P_AIM, SInput::GAMEPAD::AXIS::LEFT_TRIGGER_AXIS);

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  //poll_joysticks();

  // run the program as long as the window is open
  while (!done)
  {
    if (!g_display.is_active)
    {
      SInput::SwapBuffers();
      SInput::RunMonkey();
    }

    SInput::EnableNGram(g_display.is_active);

    PullEvents();

    // Close App on ESC
    if (SInput::Keyboard()->KeyTriggered(SInput::KEYBOARD::KEY::KEY_ESC))
    {
      done = true;
    }

    /* Render here */
    SDL_ImGui_GL3_NewFrame(sdl_window);

    g_display.DisplayAll();

    // Rendering
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();

    SDL_GL_SwapWindow(sdl_window);
  }

  SInput::Shutdown();
  SDL_ImGui_GL3_Shutdown();
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();

  return 0;
}
