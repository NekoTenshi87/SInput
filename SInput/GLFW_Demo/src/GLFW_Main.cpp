
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

      SInput::Keyboard()->UpdateMods(GLFW_ModConverter(mods));
      SInput::Keyboard()->UpdateKey(S_Key, S_Action, g_display.show_keys);
    }
  }
  else
  {
    if (SInput::Keyboard()->getNextKey && SInput::Keyboard()->nextKey == SInput::KEYBOARD::KEY::UNKNOWN_KEY)
    {
      SInput::KEYBOARD::ACTION S_Action = GLFW_KeyActionConverter(action);

      if (S_Action == SInput::KEYBOARD::ACTION::PRESSED)
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
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (!g_display.is_active)
  {
    SInput::MOUSE::ACTION S_Action = GLFW_MouseActionConverter(action);

    if (S_Action != SInput::MOUSE::UNKNOWN_ACTION)
    {
      SInput::MOUSE::BUTTON S_Button = GLFW_MouseConverter(button);

      SInput::Keyboard()->UpdateMods(GLFW_ModConverter(mods));
      SInput::Mouse()->UpdateButton(S_Button, S_Action, g_display.show_mouse_buttons);
    }
  }
  else
  {
    if (SInput::Mouse()->getNextButton && SInput::Mouse()->nextButton == SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
    {
      SInput::MOUSE::ACTION S_Action = GLFW_MouseActionConverter(action);

      if (S_Action == SInput::MOUSE::ACTION::PRESSED)
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
        SInput::Mouse()->UpdateMouseEnter(false, g_display.show_mouse_enter);
        break;

      case GLFW_TRUE:
        SInput::Mouse()->UpdateMouseEnter(true, g_display.show_mouse_enter);
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

    SInput::Mouse()->UpdateMousePos(pos, g_display.show_mouse_pos);
  }
}

void mouse_scroll_callback(GLFWwindow* window, double dX, double dY)
{
  if (!g_display.is_active)
  {
    SInput::Mouse()->UpdateMouseWheel(static_cast<int>(std::floor(-dX)), static_cast<int>(std::floor(dY)), g_display.show_mouse_scroll);
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
    SInput::GamePad(gp_num)->UpdateConnection(gp_num, SInput::GAMEPAD::DISCONNECTED, g_display.show_gamepad_connect);
    break;

  case GLFW_TRUE:
    SInput::GamePad(gp_num)->UpdateConnection(gp_num, SInput::GAMEPAD::CONNECTED, g_display.show_gamepad_connect);
    break;

  default:
    break;
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

      SInput::GamePad(gp_num)->UpdateButton(gp_num, S_Button, S_Action, g_display.show_gamepad_buttons);
    }
  }
  else
  {
    if (SInput::GamePad(gp_num)->getNextButton && SInput::GamePad(gp_num)->nextButton == SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
    {
      SInput::GAMEPAD::ACTION S_Action = GLFW_GamePadActionConverter(action);

      if (S_Action == SInput::GAMEPAD::ACTION::PRESSED)
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

    SInput::GamePad(gp_num)->UpdateAxis(gp_num, S_Axis, delta, g_display.show_gamepad_axis);
  }
  else
  {
    if (SInput::GamePad(gp_num)->getNextAxis && SInput::GamePad(gp_num)->nextAxis == SInput::GAMEPAD::AXIS::UNKNOWN_AXIS)
    {
      if (std::abs(delta) > 0.5f)
      {
        SInput::GamePad(gp_num)->nextAxis = GLFW_GamePadAxisConverter(axis);
      }
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

  // run the program as long as the window is open
  while (!glfwWindowShouldClose(glfw_window))
  {
    if (!g_display.is_active)
    {
      SInput::SwapBuffers();
      SInput::RunMonkey();
    }

    SInput::EnableNGram(g_display.is_active);

    PullEvents();

    if (SInput::Keyboard()->KeyTriggered(SInput::KEYBOARD::KEY::KEY_ESC))
    {
      glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
    }

    /* Render here */
    GLFW_ImGui_GL3_NewFrame();

#if(true)
    g_display.DisplayAll();
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
