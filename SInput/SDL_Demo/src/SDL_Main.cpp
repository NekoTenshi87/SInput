#include <stdio.h>
#include <iostream>
#include <IMGUI/imgui.h>
#include <SDL_Demo/SDL_ImGui_gl3.hpp>
#include <GL/gl3w.h>
#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>
#include <SInput/SInput.hpp>

#include <SDL_Demo/SDL_Converters.hpp>

// Gets rid of Console Window
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

static bool imgui_window_active = false;

static bool show_keys = true;
static bool show_mouse_buttons = true;
static bool show_mouse_scroll = true;
static bool show_mouse_pos = true;
static bool show_gamepad_buttons = true;
static bool show_gamepad_connect = true;
static bool show_gamepad_axis = true;

static SDL_Window* sdl_window = NULL;
static bool done = false;

void key_callback(SDL_Window* window, int key, int scancode, int action, int mods)
{
  SInput::KEYBOARD::ACTION S_Action = SDL_KeyActionConverter(action);

  if (S_Action != SInput::KEYBOARD::UNKNOWN_ACTION)
  {
    SInput::KEYBOARD::KEY S_Key = SDL_KeyConverter(key);

    SInput::Keyboard()->UpdateKey(S_Key, S_Action);
    SInput::Keyboard()->UpdateMods(SDL_ModConverter(mods));

    if (show_keys)
    {
      SInput::Keyboard()->Print(S_Key);
    }
  }
}

void mouse_button_callback(SDL_Window* window, int button, int action, int mods)
{
  SInput::MOUSE::ACTION S_Action = SDL_MouseActionConverter(action);

  if (S_Action != SInput::MOUSE::UNKNOWN_ACTION)
  {
    SInput::MOUSE::BUTTON S_Button = SDL_MouseConverter(button);

    SInput::Mouse()->UpdateButton(S_Button, S_Action);
    SInput::Keyboard()->UpdateMods(SDL_ModConverter(mods));

    if (show_mouse_buttons)
    {
      SInput::Mouse()->Print(S_Button);
    }
  }
}

void mouse_enter_callback(SDL_Window* window, int enter)
{
  switch (enter)
  {
    case SDL_FALSE:
      SInput::Mouse()->UpdateMouseEnter(false);
      break;

    case SDL_TRUE:
      SInput::Mouse()->UpdateMouseEnter(true);
      break;

    default:
      break;
  }
}

void mouse_pos_callback(SDL_Window* window, int posX, int posY)
{
  SInput::MousePos pos(posX, posY);

  SInput::Mouse()->UpdateMousePos(pos);

  if (show_mouse_pos)
  {
    SInput::Mouse()->PrintPos();
  }
}

void mouse_scroll_callback(SDL_Window* window, double dX, double dY)
{
  SInput::Mouse()->UpdateMouseWheel(static_cast<int>(std::floor(-dX)), static_cast<int>(std::floor(dY)));

  if (show_mouse_scroll)
  {
    SInput::Mouse()->PrintScoll();
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
    SInput::GamePad(gp_num)->UpdateConnection(SInput::GAMEPAD::DISCONNECTED);
    break;

  case SDL_TRUE:
    SInput::GamePad(gp_num)->UpdateConnection(SInput::GAMEPAD::CONNECTED);
    break;

  default:
    break;
  }

  if (show_gamepad_connect)
  {
    SInput::GamePad(gp_num)->PrintConnection(gp_num +1);
  }
}


void gamepad_button_callback(SDL_Window* window, int gp_num, int button, unsigned char action)
{
  SInput::GAMEPAD::ACTION S_Action = SDL_GamePadActionConverter(action);

  if (S_Action != SInput::GAMEPAD::UNKNOWN_ACTION)
  {
    SInput::GAMEPAD::BUTTON S_Button = SDL_GamePadButtonConverter(button);

    SInput::GamePad(gp_num)->UpdateButton(S_Button, S_Action);

    if (show_gamepad_buttons)
    {
      SInput::GamePad(gp_num)->PrintButton(gp_num + 1, S_Button);
    }
  }
}

void gamepad_axis_callback(SDL_Window* window, int gp_num, int axis, float delta)
{
  SInput::GAMEPAD::AXIS S_Axis = SDL_GamePadAxisConverter(axis);

  SInput::GamePad(gp_num)->UpdateAxis(S_Axis, delta);

  if (show_gamepad_axis)
  {
    SInput::GamePad(gp_num)->PrintAxis(gp_num + 1, S_Axis);
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
    if (!imgui_window_active)
    {
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
    }
    else
    {
     SDL_ImGui_GL3_ProcessEvent(&event);
    }

    if (event.key.keysym.sym == SDLK_i && event.key.keysym.mod | KMOD_CTRL && event.type == SDL_KEYDOWN)
    {
      imgui_window_active ^= 1;
    }

    // Close App on ESC
    if (event.key.keysym.sym == SDLK_ESCAPE && event.key.keysym.mod == KMOD_NONE && event.type == SDL_KEYDOWN)
    {
      done = true;
    }
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

  

  bool show_log_window = true;
  //bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  //poll_joysticks();

  // run the program as long as the window is open
  while (!done)
  {
    SInput::SwapBuffers();

    PullEvents();

    /* Render here */
    SDL_ImGui_GL3_NewFrame(sdl_window);

    // 1. Show a simple window
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
    if (imgui_window_active)
    {
      ImGui::Begin("SInput", &imgui_window_active);
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::ColorEdit3("clear color", (float*)&clear_color);
      if (ImGui::Button("Debug Window")) show_log_window ^= 1;
      if (ImGui::CollapsingHeader("Basic Debug"))
      {
        if (ImGui::TreeNode("Keyboard"))
        {
          ImGui::Checkbox("Keyboard Keys", &show_keys);
          ImGui::TreePop();
        }

        if (ImGui::TreeNode("Mouse"))
        {
          ImGui::Checkbox("Mouse Buttons", &show_mouse_buttons);
          ImGui::Checkbox("Mouse Scroll", &show_mouse_scroll);
          ImGui::Checkbox("Mouse Pos", &show_mouse_pos);
          ImGui::TreePop();
        }

        if (ImGui::TreeNode("GamePad"))
        {
          ImGui::Checkbox("GamePad Connection", &show_gamepad_connect);
          ImGui::Checkbox("GamePad Buttons", &show_gamepad_buttons);
          ImGui::Checkbox("GamePad Axis", &show_gamepad_axis);
          ImGui::TreePop();
        }

      }


      ImGui::End();
    }

    // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
    if (show_log_window)
    {
      ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
      //ImGui::ShowTestWindow(&show_test_window);
      SDL_ImGui_GL3_ShowLog(&imgui_window_active);
      //ImGui::ShowExampleApp
    }

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
