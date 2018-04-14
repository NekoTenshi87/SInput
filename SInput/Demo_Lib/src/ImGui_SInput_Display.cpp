
#include <SInput\SInput.hpp>
#include <Demo_Lib\ImGui_SInput_Display.hpp>

static ExampleAppLog log_app;

void ImGui_SInput_Display::DisplaySInputWindow()
{
  // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
  if (is_active)
  {
    ImGui::Begin("SInput", &is_active);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::ColorEdit3("clear color", (float*)&color);
    if (ImGui::Button("Debug Window")) show_log_window ^= 1;
    if (ImGui::CollapsingHeader("Basic Debug"))
    {
      if (ImGui::TreeNode("Keyboard"))
      {
        ImGui::Checkbox("Keyboard Keys", &show_keys);
        //ImGui::Checkbox("Monkey", &run_monkey);
        ImGui::TreePop();
      }

      if (ImGui::TreeNode("Mouse"))
      {
        ImGui::Checkbox("Mouse Buttons", &show_mouse_buttons);
        ImGui::Checkbox("Mouse Scroll", &show_mouse_scroll);
        ImGui::Checkbox("Mouse Pos", &show_mouse_pos);
        //ImGui::Checkbox("Monkey", &run_monkey);
        ImGui::TreePop();
      }

      if (ImGui::TreeNode("GamePad"))
      {
        ImGui::Checkbox("GamePad Connection", &show_gamepad_connect);
        ImGui::Checkbox("GamePad Buttons", &show_gamepad_buttons);
        ImGui::Checkbox("GamePad Axis", &show_gamepad_axis);
        ImGui::Checkbox("Plug and Play Detection", &show_pnp_detection);
        //ImGui::Checkbox("Monkey", &run_monkey);
        ImGui::TreePop();
      }

    }
    if (ImGui::CollapsingHeader("Virtual Controller"))
    {

    }
    if (ImGui::CollapsingHeader("Key/Button Mapping"))
    {
      ImGui::Columns(4, NULL, true);
      ImGui::Checkbox("Single Mapping", &use_single_bind);

      ImGui::NextColumn();
      ImGui::NextColumn();
      ImGui::NextColumn();

      ImGui::DragInt("GamePad ID", &gamepad_id);
      if (gamepad_id < 0)
      {
        gamepad_id = 0;
      }
      if (gamepad_id > SInput::GAMEPAD::PAD::NUMBEROFGAMEPADS)
      {
        gamepad_id = SInput::GAMEPAD::PAD::NUMBEROFGAMEPADS - 1;
      }
      if (gamepad_id != gamepad_id_prev)
      {
        for (int i = 0; i < 16; ++i)
        {
          selected_gpbutton[i] = false;
        }

        gamepad_id_prev = gamepad_id;
      }

      ImGui::NextColumn();

      // Headers
      ImGui::Text("User Type");
      ImGui::NextColumn();

      ImGui::Text("Bound Key");
      ImGui::NextColumn();

      ImGui::Text("Bound Mouse");
      ImGui::NextColumn();

      ImGui::Text("Bound GamePad");
      ImGui::NextColumn();

      // Selectors
      std::string headers[16]{ "Move Up:", "Move Left:", "Move Down:", "Move Right:", "Jump:", "Run", "Crouch", "Shoot", "Aim", "Melee" };
      int e_value;

      for (int i = 0; i < 10; ++i)
      {
        // Header
        ImGui::Text(headers[i].c_str());
        ImGui::NextColumn();

        // Keyboard
        e_value = SInput::Keyboard()->getBindKey(i);

        ImGui::PushID(i);

        if (selected_key[i])
        {
          key_name[i] = std::string("PRESS KEY");
        }
        else
        {
          if (e_value == SInput::KEYBOARD::KEY::UNKNOWN_KEY)
          {
            key_name[i] = std::string("-- NOT ASSIGNED --");
          }
          else
          {
            key_name[i] = SInput::Keyboard()->GetKeysEnum().toStr(e_value);
          }
        }

        if (ImGui::Button(key_name[i].c_str()))
        {
          SInput::Keyboard()->getNextKey = true;
          selected_key[i] = true;
          
          if (use_single_bind)
          {
            for (int j = 0; j < 10; ++j)
            {
              if (j == i)
              {
                continue;
              }

              selected_key[j] = false;
            }
          }
        }

        ImGui::PopID();
        ImGui::SameLine();
        ImGui::PushID(i);

        if (ImGui::Button(" X "))
        {
          SInput::Keyboard()->UnBindKey(i);
        }

        ImGui::PopID();

        if (selected_key[i] && SInput::Keyboard()->getNextKey && SInput::Keyboard()->nextKey != SInput::KEYBOARD::KEY::UNKNOWN_KEY)
        {
          SInput::Keyboard()->BindKey(i, SInput::Keyboard()->nextKey);
          selected_key[i] = false;
        }

        ImGui::NextColumn();

        // Mouse
        e_value = SInput::Mouse()->getBindButton(i);

        ImGui::PushID(10 + i);

        if (selected_mbutton[i])
        {
          mbutton_name[i] = std::string("PRESS MOUSE BUTTON");
        }
        else
        {
          if (e_value == SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
          {
            mbutton_name[i] = std::string("-- NOT ASSIGNED --");
          }
          else
          {
            mbutton_name[i] = SInput::Mouse()->GetButtonEnum().toStr(e_value);
          }
        }

        if (ImGui::Button(mbutton_name[i].c_str()))
        {
          SInput::Mouse()->getNextButton = true;
          selected_mbutton[i] = true;

          if (use_single_bind)
          {
            for (int j = 0; j < 10; ++j)
            {
              if (j == i)
              {
                continue;
              }

              selected_mbutton[j] = false;
            }
          }
        }

        ImGui::PopID();
        ImGui::SameLine();
        ImGui::PushID(10 + i);

        if (ImGui::Button(" X "))
        {
          SInput::Mouse()->UnBindButton(i);
        }

        ImGui::PopID();

        if (selected_mbutton[i] && SInput::Mouse()->getNextButton && SInput::Mouse()->nextButton != SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
        {
          SInput::Mouse()->BindButton(i, SInput::Mouse()->nextButton);
          selected_mbutton[i] = false;
        }

        ImGui::NextColumn();

        // GamePad
        e_value = SInput::GamePad(gamepad_id)->getBindButton(i);
        int a_value = SInput::GamePad(gamepad_id)->getBindAxis(i);

        ImGui::PushID(20 + i);

        if (selected_gpbutton[i])
        {
          gpbutton_name[i] = std::string("PRESS GAMEPAD BUTTON/AXIS");
        }
        else
        {
          if (e_value == SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
          {
            if (a_value == SInput::GAMEPAD::AXIS::UNKNOWN_AXIS)
            {
              gpbutton_name[i] = std::string("-- NOT ASSIGNED --");
            }
            else
            {
              gpbutton_name[i] = SInput::GamePad(gamepad_id)->GetGPAxisEnum().toStr(a_value);
            }
          }
          else
          {
            gpbutton_name[i] = SInput::GamePad(gamepad_id)->GetGPButtonEnum().toStr(e_value);
          }
        }

        if (ImGui::Button(gpbutton_name[i].c_str()))
        {
          SInput::GamePad(gamepad_id)->getNextButton = true;
          SInput::GamePad(gamepad_id)->getNextAxis = true;
          selected_gpbutton[i] = true;

          if (use_single_bind)
          {
            for (int j = 0; j < 10; ++j)
            {
              if (j == i)
              {
                continue;
              }

              selected_gpbutton[j] = false;
            }
          }
        }

        ImGui::PopID();
        ImGui::SameLine();
        ImGui::PushID(20 + i);

        if (ImGui::Button(" X "))
        {
          SInput::GamePad(gamepad_id)->UnBindButton(i);
          SInput::GamePad(gamepad_id)->UnBindAxis(i);
        }

        ImGui::PopID();

        if (selected_gpbutton[i] && SInput::GamePad(gamepad_id)->getNextButton && SInput::GamePad(gamepad_id)->nextButton != SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
        {
          SInput::GamePad(gamepad_id)->BindButton(i, SInput::GamePad(gamepad_id)->nextButton);
          SInput::GamePad(gamepad_id)->UnBindAxis(i);
          selected_gpbutton[i] = false;
        }
        else if (selected_gpbutton[i] && SInput::GamePad(gamepad_id)->getNextAxis && SInput::GamePad(gamepad_id)->nextAxis != SInput::GAMEPAD::AXIS::UNKNOWN_AXIS)
        {
          SInput::GamePad(gamepad_id)->BindAxis(i, SInput::GamePad(gamepad_id)->nextAxis);
          SInput::GamePad(gamepad_id)->UnBindButton(i);
          selected_gpbutton[i] = false;
        }

        ImGui::NextColumn();
      }

      // Reset Nexts
      if (SInput::Keyboard()->getNextKey && SInput::Keyboard()->nextKey != SInput::KEYBOARD::KEY::UNKNOWN_KEY)
      {
        SInput::Keyboard()->nextKey = SInput::KEYBOARD::KEY::UNKNOWN_KEY;
        SInput::Keyboard()->getNextKey = false;
      }

      if (SInput::Mouse()->getNextButton && SInput::Mouse()->nextButton != SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
      {
        SInput::Mouse()->nextButton = SInput::MOUSE::BUTTON::UNKNOWN_BUTTON;
        SInput::Mouse()->getNextButton = false;
      }

      if (SInput::GamePad(gamepad_id)->getNextButton && SInput::GamePad(gamepad_id)->nextButton != SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
      {
        SInput::GamePad(gamepad_id)->nextButton = SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON;
        SInput::GamePad(gamepad_id)->getNextButton = false;
        SInput::GamePad(gamepad_id)->getNextAxis = false;
      }

      if (SInput::GamePad(gamepad_id)->getNextAxis && SInput::GamePad(gamepad_id)->nextAxis != SInput::GAMEPAD::AXIS::UNKNOWN_AXIS)
      {
        SInput::GamePad(gamepad_id)->nextAxis = SInput::GAMEPAD::AXIS::UNKNOWN_AXIS;
        SInput::GamePad(gamepad_id)->getNextButton = false;
        SInput::GamePad(gamepad_id)->getNextAxis = false;
      }

      ImGui::Columns(1);

    }
    if (ImGui::CollapsingHeader("Combination Detection"))
    {

    }
    if (ImGui::CollapsingHeader("Stat Tracking"))
    {
      ImGui::Checkbox("# of Times Triggered", &show_num_times_triggered);
      ImGui::Checkbox("Average Time Pressed", &show_avg_time_pressed);
      ImGui::Checkbox("Percent of Usage", &show_percent_of_usage);
      ImGui::Checkbox("Most Common Next", &show_most_common_next);
      if (show_most_common_next)
      {
        ImGui::SameLine();
        ImGui::Text(" Top:");
        ImGui::SameLine();
        ImGui::InputInt("", &num_most_common_next);
        if (num_most_common_next <= 0)
        {
          num_most_common_next = 1;
        }
      }
    }
    if (ImGui::CollapsingHeader("N-Grams"))
    {

    }
    if (ImGui::CollapsingHeader("Pattern Recognition"))
    {

    }

    /*
    if (ImGui::CollapsingHeader("Full Scene Replay"))
    {

    }
    if (ImGui::CollapsingHeader("Single Source Rewind"))
    {

    }
    */

    ImGui::End();
  }
}

void ImGui_SInput_Display::DisplayDebbugWindow()
{
  if (show_log_window)
  {
    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);

    log_app.AddLog();

    log_app.ScrollToBottom = true;

    log_app.Draw("Debug Window", &show_log_window);
  }
}