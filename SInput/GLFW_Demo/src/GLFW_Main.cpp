
#include <IMGUI/imgui.h>
#include <GLFW_Demo/GLFW_ImGui_gl3.hpp>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <SInput/SInput.hpp>

#include <Demo_Lib\ImGui_SInput_Display.hpp>
#include <GLFW_Demo/GLFW_Converters.hpp>

// Gets rid of Console Window
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

static ImGui_SInput_Display g_display;

static GLFWwindow* glfw_window;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (!g_display.is_active)
  {
    SInput::KEYBOARD::ACTION S_Action = GLFW_KeyActionConverter(action);

    if (S_Action != SInput::KEYBOARD::UNKNOWN_ACTION)
    {
      SInput::KEYBOARD::KEY S_Key = GLFW_KeyConverter(key);

      SInput::Keyboard()->UpdateKey(S_Key, S_Action);
      SInput::Keyboard()->UpdateMods(GLFW_ModConverter(mods));

      if (g_display.show_keys)
      {
        SInput::Keyboard()->Print(S_Key);
      }
    }
  }
  else
  {
    if (SInput::Keyboard()->getNextKey && SInput::Keyboard()->nextKey == SInput::KEYBOARD::KEY::UNKNOWN_KEY)
    {
      SInput::KEYBOARD::ACTION S_Action = GLFW_KeyActionConverter(action);

      if (S_Action != SInput::KEYBOARD::KEY::UNKNOWN_KEY)
      {
        SInput::Keyboard()->nextKey = GLFW_KeyConverter(key);
      }
    }
    else
    {
      GLFW_ImGui_GL3_KeyCallback(window, key, scancode, action, mods);
    }
  }

  if (key == GLFW_KEY_I && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS)
  {
    g_display.is_active ^= 1;
  }

  // Close App on ESC
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
  }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (!g_display.is_active)
  {
    SInput::MOUSE::ACTION S_Action = GLFW_MouseActionConverter(action);

    if (S_Action != SInput::MOUSE::UNKNOWN_ACTION)
    {
      SInput::MOUSE::BUTTON S_Button = GLFW_MouseConverter(button);

      SInput::Mouse()->UpdateButton(S_Button, S_Action);
      SInput::Keyboard()->UpdateMods(GLFW_ModConverter(mods));

      if (g_display.show_mouse_buttons)
      {
        SInput::Mouse()->Print(S_Button);
      }
    }
  }
  else
  {
    if (SInput::Mouse()->getNextButton && SInput::Mouse()->nextButton == SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
    {
      SInput::MOUSE::ACTION S_Action = GLFW_MouseActionConverter(action);

      if (S_Action != SInput::MOUSE::UNKNOWN_ACTION)
      {
        SInput::Mouse()->nextButton = GLFW_MouseConverter(button);
      }
    }
    else
    {
      GLFW_ImGui_GL3_MouseButtonCallback(window, button, action, mods);
    }
  }
}

void mouse_enter_callback(GLFWwindow* window, int enter)
{
  if (!g_display.is_active)
  {
    switch (enter)
    {
      case GLFW_FALSE:
        SInput::Mouse()->UpdateMouseEnter(false);
        break;

      case GLFW_TRUE:
        SInput::Mouse()->UpdateMouseEnter(true);
        break;

      default:
        break;
    }
  }
}

void mouse_pos_callback(GLFWwindow* window, double posX, double posY)
{
  if (!g_display.is_active)
  {
    SInput::MousePos pos(static_cast<int>(std::floor(posX)), static_cast<int>(std::floor(posY)));

    SInput::Mouse()->UpdateMousePos(pos);

    if (g_display.show_mouse_pos)
    {
      SInput::Mouse()->PrintPos();
    }
  }
}

void mouse_scroll_callback(GLFWwindow* window, double dX, double dY)
{
  if (!g_display.is_active)
  {
    SInput::Mouse()->UpdateMouseWheel(static_cast<int>(std::floor(-dX)), static_cast<int>(std::floor(dY)));

    if (g_display.show_mouse_scroll)
    {
      SInput::Mouse()->PrintScoll();
    }
  }
  else
  {
    GLFW_ImGui_GL3_ScrollCallback(window, dX, dY);
  }

  //std::cout << "MouseWheel: X: " << SInput::Mouse()->GetDeltaX() << " Y: " << SInput::Mouse()->GetDeltaY() << std::endl;
}

void focus_callback(GLFWwindow* window, int focused)
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

void gamepad_connection_callback(GLFWwindow* window, int gp_num, int connect)
{
  switch (connect)
  {
  case GLFW_FALSE:
    SInput::GamePad(gp_num)->UpdateConnection(SInput::GAMEPAD::DISCONNECTED);
    break;

  case GLFW_TRUE:
    SInput::GamePad(gp_num)->UpdateConnection(SInput::GAMEPAD::CONNECTED);
    break;

  default:
    break;
  }

  if (g_display.show_gamepad_connect)
  {
    SInput::GamePad(gp_num)->PrintConnection(gp_num +1);
  }
}


void gamepad_button_callback(GLFWwindow* window, int gp_num, int button, unsigned char action)
{
  if (!g_display.is_active)
  {
    SInput::GAMEPAD::ACTION S_Action = GLFW_GamePadActionConverter(action);

    if (S_Action != SInput::GAMEPAD::UNKNOWN_ACTION)
    {
      SInput::GAMEPAD::BUTTON S_Button = GLFW_GamePadButtonConverter(button);

      SInput::GamePad(gp_num)->UpdateButton(S_Button, S_Action);

      if (g_display.show_gamepad_buttons)
      {
        SInput::GamePad(gp_num)->PrintButton(gp_num + 1, S_Button);
      }
    }
  }
  else
  {
    if (SInput::GamePad(gp_num)->getNextButton && SInput::GamePad(gp_num)->nextButton == SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
    {
      SInput::GAMEPAD::ACTION S_Action = GLFW_GamePadActionConverter(action);

      if (S_Action != SInput::GAMEPAD::UNKNOWN_ACTION)
      {
        SInput::GamePad(gp_num)->nextButton = GLFW_GamePadButtonConverter(button);
      }
    }
  }
}

void gamepad_axis_callback(GLFWwindow* window, int gp_num, int axis, float delta)
{
  if (!g_display.is_active)
  {
    SInput::GAMEPAD::AXIS S_Axis = GLFW_GamePadAxisConverter(axis);

    SInput::GamePad(gp_num)->UpdateAxis(S_Axis, delta);

    if (g_display.show_gamepad_axis)
    {
      SInput::GamePad(gp_num)->PrintAxis(gp_num + 1, S_Axis);
    }
  }
}

void poll_joysticks()
{
  for (unsigned i = 0; i < SInput::GAMEPAD::NUMBEROFGAMEPADS; ++i)
  {
    int value = glfwJoystickPresent(i);

    if ((int)SInput::GamePad(i)->IsConnected() != value)
    {
      gamepad_connection_callback(glfw_window, i, value);
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

          if (SInput::GamePad(i)->ButtonPressed(S_Button) ^ (S_Action == SInput::GAMEPAD::PRESSED))
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
}

void PullEvents()
{
  glfwPollEvents();

  poll_joysticks();

  joystick_refresh();
}

int main(int argc, char* args[])
{
  /* Initialize the library */
  if (!glfwInit())
  {
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();

  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  /*
  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  */
  /* Create a windowed mode window and its OpenGL context */
  //glfw_window = glfwCreateWindow(mode->width, mode->height, "GLFW Window", monitor, NULL);

  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  glfw_window = glfwCreateWindow(mode->width, mode->height, "GLFW Window", NULL, NULL);
  //glfwSetWindowPos(glfw_window, mode->width/4, mode->height/4);

  if (!glfw_window)
  {
    glfwTerminate();
    return -1;
  }

  glfwShowWindow(glfw_window);

  glfwMakeContextCurrent(glfw_window);
  glfwSwapInterval(1); // Enable vsync

  gl3wInit();

  // Setup ImGui binding
  GLFW_ImGui_GL3_Init(glfw_window, true);

  glfwSetWindowPos(glfw_window, 1, 30);
  glfwSetKeyCallback(glfw_window, key_callback);
  glfwSetMouseButtonCallback(glfw_window, mouse_button_callback);
  glfwSetCursorEnterCallback(glfw_window, mouse_enter_callback);
  glfwSetCursorPosCallback(glfw_window, mouse_pos_callback);
  glfwSetScrollCallback(glfw_window, mouse_scroll_callback);
  glfwSetWindowFocusCallback(glfw_window, focus_callback);

  SInput::Init();

  

  //bool show_log_window = true;
  //bool show_another_window = false;


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

  SInput::Keyboard()->Bind(P_MOVE_UP, SInput::KEYBOARD::KEY::KEY_W);
  SInput::Keyboard()->Bind(P_MOVE_LEFT, SInput::KEYBOARD::KEY::KEY_A);
  SInput::Keyboard()->Bind(P_MOVE_DOWN, SInput::KEYBOARD::KEY::KEY_S);
  SInput::Keyboard()->Bind(P_MOVE_RIGHT, SInput::KEYBOARD::KEY::KEY_D);
  SInput::Keyboard()->Bind(P_JUMP, SInput::KEYBOARD::KEY::KEY_SPACE);
  SInput::Keyboard()->Bind(P_RUN, SInput::KEYBOARD::KEY::KEY_LEFT_SHIFT);
  SInput::Keyboard()->Bind(P_CROUCH, SInput::KEYBOARD::KEY::KEY_LEFT_CONTROL);

  SInput::Mouse()->Bind(P_SHOOT, SInput::MOUSE::BUTTON::BUTTON_LEFT);
  SInput::Mouse()->Bind(P_AIM, SInput::MOUSE::BUTTON::BUTTON_RIGHT);
  SInput::Mouse()->Bind(P_MELEE, SInput::MOUSE::BUTTON::BUTTON_4);

  //SInput::GamePad(0)

  // run the program as long as the window is open
  while (!glfwWindowShouldClose(glfw_window))
  {
    SInput::SwapBuffers();

    PullEvents();
    /*
    if (SInput::Keyboard()->ModsPressed(SInput::KEYBOARD::MOD_CTRL | SInput::KEYBOARD::MOD_SHIFT))
    {
      if (SInput::Keyboard()->KeyTriggered(SInput::KEYBOARD::KEY_Q))
      {
        glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
      }

      if (SInput::Keyboard()->KeyReleased(SInput::KEYBOARD::KEY_B))
      {
        glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
      }

      if (SInput::Mouse()->ButtonTriggered(SInput::MOUSE::BUTTON_4))
      {
        glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
      }
    }*/

    /* Render here */
    GLFW_ImGui_GL3_NewFrame();

#if(true)
    g_display.DisplaySInputWindow();

    g_display.DisplayDebbugWindow();
#else
    static bool show_test_window = true;

    ImGui::ShowTestWindow(&show_test_window);
#endif

    // Rendering
    int display_w, display_h;
    glfwGetFramebufferSize(glfw_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(g_display.color.x, g_display.color.y, g_display.color.z, g_display.color.w);
    //glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();


    /* Swap front and back buffers */
    glfwSwapBuffers(glfw_window);
  }

  SInput::Shutdown();
  GLFW_ImGui_GL3_Shutdown();
  glfwTerminate();

  return 0;
}
