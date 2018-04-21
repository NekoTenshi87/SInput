
#include <SInput\SInput.hpp>
#include <Demo_Lib\ImGui_SInput_Display.hpp>
#include <string>
#include <vector>

static ExampleAppLog log_app;

int v_mods = SInput::KEYBOARD::MOD::MOD_NONE;

void ImGui_SInput_Display::DisplayAll()
{
  DisplaySInputWindow();

  DisplayDebbugWindow();

  DisplayVirtualKeyboard();

  DisplayVirtualMouse();

  DisplayVirtualGamePad();
}

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
      ImGui::PushID(1000);
      if (ImGui::TreeNode("Keyboard"))
      {
        ImGui::Checkbox("Keyboard Keys", &show_keys);
        ImGui::Checkbox("Monkey", &run_monkey_keyboard);
        SInput::Keyboard()->Monkey(run_monkey_keyboard);
        ImGui::TreePop();
      }
      ImGui::PopID();

      ImGui::PushID(1100);
      if (ImGui::TreeNode("Mouse"))
      {
        ImGui::Checkbox("Mouse Buttons", &show_mouse_buttons);
        ImGui::Checkbox("Mouse Scroll", &show_mouse_scroll);
        ImGui::Checkbox("Mouse Pos", &show_mouse_pos);
        ImGui::Checkbox("Mouse Enter", &show_mouse_enter);
        ImGui::Checkbox("Monkey", &run_monkey_mouse);
        SInput::Mouse()->Monkey(run_monkey_mouse);
        ImGui::TreePop();
      }
      ImGui::PopID();

      ImGui::PushID(1200);
      if (ImGui::TreeNode("GamePad"))
      {
        ImGui::Checkbox("GamePad Connection", &show_gamepad_connect);
        ImGui::Checkbox("GamePad Buttons", &show_gamepad_buttons);
        ImGui::Checkbox("GamePad Axis", &show_gamepad_axis);
        ImGui::Checkbox("Plug and Play Detection", &show_pnp_detection);
        ImGui::Checkbox("Monkey", &run_monkey_gamepad);
        SInput::GamePad(0)->Monkey(run_monkey_gamepad);
        ImGui::TreePop();
      }
      ImGui::PopID();

    }
    if (ImGui::CollapsingHeader("Virtual Controller"))
    {
      ImGui::PushID(2000);
      if (ImGui::TreeNode("Keyboard"))
      {
        if (ImGui::Button("Show Keyboard")) show_virt_keyboard ^= 1;
        
        ImGui::Checkbox("Monkey", &run_monkey_vkeyboard);
        SInput::VKeyboard(0)->Monkey(run_monkey_vkeyboard);
        ImGui::TreePop();
      }
      ImGui::PopID();

      ImGui::PushID(2100);
      if (ImGui::TreeNode("Mouse"))
      {
        if (ImGui::Button("Show Mouse")) show_virt_mouse ^= 1;

        ImGui::Checkbox("Monkey", &run_monkey_vmouse);
        SInput::VMouse(0)->Monkey(run_monkey_vmouse);
        ImGui::TreePop();
      }
      ImGui::PopID();

      ImGui::PushID(2200);
      if (ImGui::TreeNode("GamePad"))
      {
        if (ImGui::Button("Show GamePad")) show_virt_gamepad ^= 1;

        ImGui::Checkbox("Monkey", &run_monkey_vgamepad);
        SInput::VGamePad(0)->Monkey(run_monkey_vgamepad);
        ImGui::TreePop();
      }
      ImGui::PopID();
    }
    if (ImGui::CollapsingHeader("Key/Button Mapping"))
    {
      ImGui::Columns(4, NULL, true);
      ImGui::SetColumnOffset(1, 150.0f);

      ImGui::Checkbox("Single Mapping", &use_single_bind);

      ImGui::NextColumn();
      ImGui::NextColumn();
      ImGui::NextColumn();
      
      ImGui::DragInt("GamePad ID", &gamepad_id, 1.0f, 0, SInput::GAMEPAD::PAD::NUMBEROFGAMEPADS - 1);
      
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

      ImGui::Columns(1);

    }
    if (ImGui::CollapsingHeader("Combination Detection"))
    {

    }
    if (ImGui::CollapsingHeader("Stat Tracking"))
    {
      ImGui::Columns(4, NULL, true);
      ImGui::SetColumnOffset(1, 160.0f);

      // Headers
      ImGui::Text("Stats");
      ImGui::NextColumn();
      ImGui::Text("Keyboard:");
      ImGui::NextColumn();
      ImGui::Text("Mouse:");
      ImGui::NextColumn();
      ImGui::Text("GamePad:");
      ImGui::NextColumn();
      ImGui::NextColumn();

      // Keyboard
      ImGui::PushID(100);

      if (stats_selected_key)
      {
        stats_key_name = std::string("PRESS KEY");
      }
      else
      {
        if (stats_key == SInput::KEYBOARD::KEY::UNKNOWN_KEY)
        {
          stats_key_name = std::string("-- NOT ASSIGNED --");
        }
        else
        {
          stats_key_name = SInput::Keyboard()->GetKeysEnum().toStr(stats_key);
        }
      }

      if (ImGui::Button(stats_key_name.c_str()))
      {
        SInput::Keyboard()->getNextKey = true;
        stats_selected_key = true;
      }

      ImGui::PopID();
      ImGui::SameLine();
      ImGui::PushID(101);

      if (ImGui::Button(" X "))
      {
        stats_key = SInput::KEYBOARD::KEY::UNKNOWN_KEY;
      }

      ImGui::PopID();

      if (stats_selected_key && SInput::Keyboard()->getNextKey && SInput::Keyboard()->nextKey != SInput::KEYBOARD::KEY::UNKNOWN_KEY)
      {
        stats_key = SInput::Keyboard()->nextKey;
        stats_selected_key = false;
      }

      ImGui::NextColumn();

      // Mouse
      ImGui::PushID(102);

      if (stats_selected_mouse)
      {
        stats_mouse_name = std::string("PRESS BUTTON");
      }
      else
      {
        if (stats_mouse == SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
        {
          stats_mouse_name = std::string("-- NOT ASSIGNED --");
        }
        else
        {
          stats_mouse_name = SInput::Mouse()->GetButtonEnum().toStr(stats_mouse);
        }
      }

      if (ImGui::Button(stats_mouse_name.c_str()))
      {
        SInput::Mouse()->getNextButton = true;
        stats_selected_mouse = true;
      }

      ImGui::PopID();
      ImGui::SameLine();
      ImGui::PushID(103);

      if (ImGui::Button(" X "))
      {
        stats_mouse = SInput::MOUSE::BUTTON::UNKNOWN_BUTTON;
      }

      ImGui::PopID();

      if (stats_selected_mouse && SInput::Mouse()->getNextButton && SInput::Mouse()->nextButton != SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
      {
        stats_mouse = SInput::Mouse()->nextButton;
        stats_selected_mouse = false;
      }

      ImGui::NextColumn();

      // GamePad
      ImGui::PushID(104);

      if (stats_selected_gamepad)
      {
        stats_gamepad_name = std::string("PRESS GAMEPAD BUTTON");
      }
      else
      {
        if (stats_gamepad == SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
        {
          stats_gamepad_name = std::string("-- NOT ASSIGNED --");
        }
        else
        {
          stats_gamepad_name = SInput::GamePad(0)->GetGPButtonEnum().toStr(stats_gamepad);
        }
      }

      if (ImGui::Button(stats_gamepad_name.c_str()))
      {
        SInput::GamePad(0)->getNextButton = true;
        stats_selected_gamepad = true;
      }

      ImGui::PopID();
      ImGui::SameLine();
      ImGui::PushID(105);

      if (ImGui::Button(" X "))
      {
        stats_gamepad = SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON;
      }

      ImGui::PopID();

      if (stats_selected_gamepad && SInput::GamePad(0)->getNextButton && SInput::GamePad(0)->nextButton != SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
      {
        stats_gamepad = SInput::GamePad(0)->nextButton;
        stats_selected_gamepad = false;
      }

      ImGui::NextColumn();
      ImGui::Text("# of Times Pressed:");
      ImGui::NextColumn();

      if (stats_key == SInput::KEYBOARD::KEY::UNKNOWN_KEY)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetPressedKey(stats_key)).c_str());
      }

      ImGui::NextColumn();

      if (stats_mouse == SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetPressedMouse(stats_mouse)).c_str());
      }

      ImGui::NextColumn();

      if (stats_gamepad == SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetPressedGamePad(stats_gamepad)).c_str());
      }

      ImGui::NextColumn();
      ImGui::Text("# of Times Released:");
      ImGui::NextColumn();

      if (stats_key == SInput::KEYBOARD::KEY::UNKNOWN_KEY)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetReleasedKey(stats_key)).c_str());
      }

      ImGui::NextColumn();

      if (stats_mouse == SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetReleasedMouse(stats_mouse)).c_str());
      }

      ImGui::NextColumn();

      if (stats_gamepad == SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetReleasedGamePad(stats_gamepad)).c_str());
      }

      ImGui::NextColumn();
      ImGui::Text("Average Time Pressed:");
      ImGui::NextColumn();

      if (stats_key == SInput::KEYBOARD::KEY::UNKNOWN_KEY)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetAverageTimeKey(stats_key)).c_str());
      }

      ImGui::NextColumn();

      if (stats_mouse == SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetAverageTimeMouse(stats_mouse)).c_str());
      }

      ImGui::NextColumn();

      if (stats_gamepad == SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetAverageTimeGamePad(stats_gamepad)).c_str());
      }

      ImGui::NextColumn();
      ImGui::Text("Use Percentage:");
      ImGui::NextColumn();

      if (stats_key == SInput::KEYBOARD::KEY::UNKNOWN_KEY)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetPercentUseKey(stats_key)).c_str());
      }

      ImGui::NextColumn();

      if (stats_mouse == SInput::MOUSE::BUTTON::UNKNOWN_BUTTON)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetPercentUseMouse(stats_mouse)).c_str());
      }

      ImGui::NextColumn();

      if (stats_gamepad == SInput::GAMEPAD::BUTTON::UNKNOWN_BUTTON)
      {
        ImGui::Text("0");
      }
      else
      {
        ImGui::Text(std::to_string(SInput::stats.GetPercentUseGamePad(stats_gamepad)).c_str());
      }

      ImGui::Columns(1);
    }
    if (ImGui::CollapsingHeader("N-Grams"))
    {
      //std::vector<SInput::NGramNodeKeyData> result = SInput::N_Gram.GetUniGramKeysResult();
      ImGui::Columns(4, NULL, true);
      ImGui::SetColumnOffset(1, 90.0f);

      std::vector<SInput::NGramNodeKeyData> UniKeyResult = SInput::N_Gram.GetUniGramKeysResult();
      std::vector<SInput::NGramNodeMouseData> UniMouseResult = SInput::N_Gram.GetUniGramMouseResult();
      std::vector<SInput::NGramNodeGamePadData> UniGamePadResult = SInput::N_Gram.GetUniGramGamePadResult();

      // Headers
      ImGui::Text("N-Gram Type");
      ImGui::NextColumn();
      ImGui::Text("Keyboard:");
      ImGui::NextColumn();
      ImGui::Text("Mouse:");
      ImGui::NextColumn();
      ImGui::Text("GamePad:");
      ImGui::NextColumn();

      ImGui::Text("Uni-Gram:");
      ImGui::NextColumn();

      // Keyboard
      ImGui::Text("#1:");
      ImGui::SameLine();
      if (UniKeyResult.size() > 0)
      {
        ImGui::Text(SInput::Keyboard()->GetKeysEnum().toStr(UniKeyResult[0].key).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniKeyResult[0].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();

      // Mouse
      ImGui::Text("#1:");
      ImGui::SameLine();
      if (UniMouseResult.size() > 0)
      {
        ImGui::Text(SInput::Mouse()->GetButtonEnum().toStr(UniMouseResult[0].button).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniMouseResult[0].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();

      // GamePad
      ImGui::Text("#1:");
      ImGui::SameLine();
      if (UniGamePadResult.size() > 0)
      {
        ImGui::Text(SInput::GamePad(0)->GetGPButtonEnum().toStr(UniGamePadResult[0].button).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniGamePadResult[0].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();
      ImGui::NextColumn();

      ImGui::Text("#2:");
      ImGui::SameLine();
      if (UniKeyResult.size() > 1)
      {
        ImGui::Text(SInput::Keyboard()->GetKeysEnum().toStr(UniKeyResult[1].key).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniKeyResult[1].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();

      // Mouse
      ImGui::Text("#2:");
      ImGui::SameLine();
      if (UniMouseResult.size() > 1)
      {
        ImGui::Text(SInput::Mouse()->GetButtonEnum().toStr(UniMouseResult[1].button).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniMouseResult[1].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();

      // GamePad
      ImGui::Text("#2:");
      ImGui::SameLine();
      if (UniGamePadResult.size() > 1)
      {
        ImGui::Text(SInput::GamePad(0)->GetGPButtonEnum().toStr(UniGamePadResult[1].button).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniGamePadResult[1].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();
      ImGui::NextColumn();

      // Keyboard
      ImGui::Text("#3:");
      ImGui::SameLine();
      if (UniKeyResult.size() > 2)
      {
        ImGui::Text(SInput::Keyboard()->GetKeysEnum().toStr(UniKeyResult[2].key).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniKeyResult[2].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();

      // Mouse
      ImGui::Text("#3:");
      ImGui::SameLine();
      if (UniMouseResult.size() > 2)
      {
        ImGui::Text(SInput::Mouse()->GetButtonEnum().toStr(UniMouseResult[2].button).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniMouseResult[2].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();

      // GamePad
      ImGui::Text("#3:");
      ImGui::SameLine();
      if (UniGamePadResult.size() > 2)
      {
        ImGui::Text(SInput::GamePad(0)->GetGPButtonEnum().toStr(UniGamePadResult[2].button).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniGamePadResult[2].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();
      ImGui::NextColumn();

      // Keyboard
      ImGui::Text("#4:");
      ImGui::SameLine();
      if (UniKeyResult.size() > 3)
      {
        ImGui::Text(SInput::Keyboard()->GetKeysEnum().toStr(UniKeyResult[3].key).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniKeyResult[3].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();

      // Mouse
      ImGui::Text("#4:");
      ImGui::SameLine();
      if (UniMouseResult.size() > 3)
      {
        ImGui::Text(SInput::Mouse()->GetButtonEnum().toStr(UniMouseResult[3].button).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniMouseResult[3].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();

      // GamePad
      ImGui::Text("#4:");
      ImGui::SameLine();
      if (UniGamePadResult.size() > 3)
      {
        ImGui::Text(SInput::GamePad(0)->GetGPButtonEnum().toStr(UniGamePadResult[3].button).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniGamePadResult[3].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();
      ImGui::NextColumn();

      // Keyboard
      ImGui::Text("#5:");
      ImGui::SameLine();
      if (UniKeyResult.size() > 4)
      {
        ImGui::Text(SInput::Keyboard()->GetKeysEnum().toStr(UniKeyResult[4].key).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniKeyResult[4].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();

      // Mouse
      ImGui::Text("#5:");
      ImGui::SameLine();
      if (UniMouseResult.size() > 4)
      {
        ImGui::Text(SInput::Mouse()->GetButtonEnum().toStr(UniMouseResult[4].button).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniMouseResult[4].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::NextColumn();

      // GamePad
      ImGui::Text("#5:");
      ImGui::SameLine();
      if (UniGamePadResult.size() > 4)
      {
        ImGui::Text(SInput::GamePad(0)->GetGPButtonEnum().toStr(UniGamePadResult[4].button).c_str());
        ImGui::SameLine();
        ImGui::Text(std::to_string(UniGamePadResult[4].percent).c_str());
      }
      else
      {
        ImGui::Text("");
      }

      ImGui::Columns(1);
    }
    if (ImGui::CollapsingHeader("Pattern Recognition"))
    {

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

void ImGui_SInput_Display::DisplayVKey(SInput::KEYBOARD::KEY key, std::string name, ImVec2 size)
{
  ImGui::PushID(2001 + key);
  if (SInput::VKeyboard(0)->KeyPressed(key))
  {
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(171, 102, 102));
  }
  else
  {
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(116, 78, 80));
  }

  if (ImGui::Button(name.c_str(), size))
  {
    SInput::VKeyboard(0)->UpdateKey(key, SInput::KEYBOARD::ACTION::PRESSED, !is_active);
  }
  else
  {
    if (SInput::VKeyboard(0)->KeyPressed(key))
    {
      SInput::VKeyboard(0)->UpdateKey(key, SInput::KEYBOARD::ACTION::RELEASED, !is_active);
    }
  }
  ImGui::PopStyleColor(1);
  ImGui::PopID();
}

void ImGui_SInput_Display::DisplayVMod(SInput::KEYBOARD::KEY key, std::string name, ImVec2 size)
{
  ImGui::PushID(2001 + key);
  if (SInput::VKeyboard(0)->KeyPressed(key))
  {
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(171, 102, 102));
  }
  else
  {
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(116, 78, 80));
  }

  int mod = SInput::VKeyboard(0)->KeyToMod(key);

  if (ImGui::Button(name.c_str(), size))
  {
    if (SInput::VKeyboard(0)->KeyPressed(key))
    {
      SInput::VKeyboard(0)->UpdateKey(key, SInput::KEYBOARD::ACTION::RELEASED, !is_active);
    }
    else
    {
      SInput::VKeyboard(0)->UpdateKey(key, SInput::KEYBOARD::ACTION::PRESSED, !is_active);
    }
  }

  if (mod != SInput::KEYBOARD::MOD::MOD_NONE)
  {
    if (SInput::VKeyboard(0)->KeyTriggered(key))
    {
      v_mods |= mod;
      SInput::VKeyboard(0)->UpdateMods(v_mods);
    }
    else if (SInput::VKeyboard(0)->KeyReleased(key))
    {
      if (v_mods & mod)
      {
        v_mods ^= mod;
        SInput::VKeyboard(0)->UpdateMods(v_mods);
      }
    }
  }

  ImGui::PopStyleColor(1);
  ImGui::PopID();
}

void ImGui_SInput_Display::DisplayVirtualKeyboard()
{
  if (show_virt_keyboard)
  {
    float x_offset = 8.0f;
    float x_step = 0.0f;
    float x_original_size = 28.0f;
    float x_size = 28.0f;
    float y_size = 28.0f;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);

    ImGui::Begin("Virtual Keyboard", &show_virt_keyboard);

    ImGui::Columns(2, NULL, false);
    ImGui::SetColumnOffset(1, 817.0f);

    x_step = x_offset; x_size = 36.0f;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_ESC, "ESC", ImVec2(x_size, y_size));
    x_step += x_size + 28.0f + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F1, "F1", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F2, "F2", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F3, "F3", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F4, "F4", ImVec2(x_size, y_size));
    x_step += x_size + 18.0f + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F5, "F5", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F6, "F6", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F7, "F7", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F8, "F8", ImVec2(x_size, y_size));
    x_step += x_size + 18.0f + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F9, "F9", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F10, "F10", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F11, "F11", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F12, "F12", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 48.0f;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PRINT_SCREEN, "PrtScr", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_SCROLL_LOCK, "ScrLk", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAUSE, "Pause", ImVec2(x_size, y_size));

    x_step = x_offset; x_size = x_original_size; 
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_ACCENT, "`", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_1, "1", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_2, "2", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_3, "3", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_4, "4", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_5, "5", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_6, "6", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_7, "7", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_8, "8", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_9, "9", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_0, "0", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_DASH, "-", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_EQUAL, "=", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 64.0f;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_BACKSPACE, "<--", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 48.0f;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_INSERT, "Ins", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_HOME, "Home", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAGE_UP, "PgUp", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_NUM_LOCK, "Num", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_DIVIDE, "/", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_MULTIPLY, "*", ImVec2(x_size, y_size));

    x_step = x_offset; x_size = 46.0f;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_TAB, "TAB", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_Q, "Q", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_W, "W", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_E, "E", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_R, "R", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_T, "T", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_Y, "Y", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_U, "U", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_I, "I", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_O, "O", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_P, "P", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_LEFT_BRACKET, "[", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_RIGHT_BRACKET, "]", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 46.0f;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_BACKSLASH, "\\", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 48.0f;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_DELETE, "Del", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_END, "End", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAGE_DOWN, "PgDn", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_7, "7", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_8, "8", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_9, "9", ImVec2(x_size, y_size));

    x_step = x_offset; x_size = 58.0f;
    DisplayVMod(SInput::KEYBOARD::KEY_CAPS_LOCK, "Caps", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_A, "A", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_S, "S", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_D, "D", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_F, "F", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_G, "G", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_H, "H", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_J, "J", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_K, "K", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_L, "L", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_SEMICOLON, ";", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_APOSTROPHE, "'", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 70.0f;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_ENTER, "Enter", ImVec2(x_size, y_size));
    x_step += x_size + 168.0f + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_4, "4", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_5, "5", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_6, "6", ImVec2(x_size, y_size));

    x_step = x_offset; x_size = 76.0f;
    DisplayVMod(SInput::KEYBOARD::KEY_LEFT_SHIFT, "Shift", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_Z, "Z", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_X, "X", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_C, "C", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_V, "V", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_B, "B", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_N, "N", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_M, "M", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_K, ",", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_L, ".", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_SLASH, "/", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 88.0f;
    DisplayVMod(SInput::KEYBOARD::KEY::KEY_RIGHT_SHIFT, "Shift", ImVec2(x_size, y_size));
    x_step += x_size + 66.0f + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_UP_ARROW, "^", ImVec2(x_size, y_size));
    x_step += x_size + 66.0f + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_1, "1", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_2, "2", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_3, "3", ImVec2(x_size, y_size));

    x_step = x_offset; x_size = 44.0f;
    DisplayVMod(SInput::KEYBOARD::KEY_LEFT_CONTROL, "Ctrl", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVMod(SInput::KEYBOARD::KEY::KEY_LEFT_SYSTEM, "Win", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 44.0f;
    DisplayVMod(SInput::KEYBOARD::KEY::KEY_LEFT_ALT, "Alt", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 252.0f;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_SPACE, "Space", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 44.0f;
    DisplayVMod(SInput::KEYBOARD::KEY::KEY_RIGHT_ALT, "Alt", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVMod(SInput::KEYBOARD::KEY::KEY_RIGHT_SYSTEM, "Win", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 44.0f;
    DisplayVMod(SInput::KEYBOARD::KEY::KEY_RIGHT_CONTROL, "Ctrl", ImVec2(x_size, y_size));
    x_step += x_size + 30.0f + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_LEFT_ARROW, "<", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_DOWN_ARROW, "v", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_RIGHT_ARROW, ">", ImVec2(x_size, y_size));
    x_step += x_size + 30.0f + x_offset; ImGui::SameLine(x_step); x_size = 64.0f;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_0, "0", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_DECIMAL, ".", ImVec2(x_size, y_size));

    ImGui::NextColumn();
    x_step = x_offset; x_size = x_original_size;
    ImGui::Dummy(ImVec2(x_size, y_size));
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_SUBTRACT, "-", ImVec2(x_size, y_size));
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_ADD, "+", ImVec2(x_size, 60.0f));
    DisplayVKey(SInput::KEYBOARD::KEY::KEY_PAD_ENTER, "E\nn\nt\ne\nr", ImVec2(x_size, 60.0f));

    ImGui::End();
  }

}

void ImGui_SInput_Display::DisplayVMButton(SInput::MOUSE::BUTTON button, std::string name, ImVec2 size)
{
  ImGui::PushID(2101 + button);
  if (SInput::VMouse(0)->ButtonPressed(button))
  {
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(171, 102, 102));
  }
  else
  {
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(116, 78, 80));
  }

  if (ImGui::Button(name.c_str(), size))
  {
    SInput::VMouse(0)->UpdateButton(button, SInput::MOUSE::ACTION::PRESSED, !is_active);
  }
  else
  {
    if (SInput::VMouse(0)->ButtonPressed(button))
    {
      SInput::VMouse(0)->UpdateButton(button, SInput::MOUSE::ACTION::RELEASED, !is_active);
    }
  }
  ImGui::PopStyleColor(1);
  ImGui::PopID();
}

void ImGui_SInput_Display::DisplayVMWheel(int dx, int dy, std::string name, ImVec2 size)
{
  ImGui::PushID(2115 + dx + dx * 2);
  if (dy > 0)
  {
    if (SInput::VMouse(0)->WheelUp())
    {
      ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(171, 102, 102));
    }
    else
    {
      ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(116, 78, 80));
    }
  }
  else if (dy < 0)
  {
    if (SInput::VMouse(0)->WheelDown())
    {
      ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(171, 102, 102));
    }
    else
    {
      ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(116, 78, 80));
    }
  }
  else if (dx > 0)
  {
    if (SInput::VMouse(0)->WheelRight())
    {
      ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(171, 102, 102));
    }
    else
    {
      ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(116, 78, 80));
    }
  }
  else if (dx < 0)
  {
    if (SInput::VMouse(0)->WheelLeft())
    {
      ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(171, 102, 102));
    }
    else
    {
      ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(116, 78, 80));
    }
  }

  if (ImGui::Button(name.c_str(), size))
  {
    SInput::VMouse(0)->UpdateMouseWheel(dx, dy, !is_active);
  }

  ImGui::PopStyleColor(1);
  ImGui::PopID();
}

void ImGui_SInput_Display::DisplayVirtualMouse()
{
  if (show_virt_mouse)
  {
    float x_offset = 8.0f;
    float x_step = 0.0f;
    float x_original_size = 28.0f;
    float x_size = 28.0f;
    float y_size = 28.0f;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);

    ImGui::Begin("Virtual Mouse", &show_virt_keyboard);

    ImGui::Columns(3, NULL, false);
    ImGui::SetColumnOffset(1, 57.0f);
    ImGui::SetColumnOffset(2, 166.0f);

    x_step = x_offset; x_size = 48.0f; y_size = 92.0f;
    DisplayVMButton(SInput::MOUSE::BUTTON::BUTTON_LEFT, "Left", ImVec2(x_size, y_size));
    y_size = 80.0f;
    DisplayVMButton(SInput::MOUSE::BUTTON::BUTTON_5, "B5", ImVec2(x_size, y_size));
    DisplayVMButton(SInput::MOUSE::BUTTON::BUTTON_4, "B4", ImVec2(x_size, y_size));

    ImGui::NextColumn();

    x_step = x_offset; x_size = x_original_size; y_size = x_original_size;
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVMWheel(0, 1, "^", ImVec2(x_size, y_size));

    x_step = x_offset;
    DisplayVMWheel(-1, 0, "<", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVMButton(SInput::MOUSE::BUTTON::BUTTON_MIDDLE, "Mid", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVMWheel(1, 0, ">", ImVec2(x_size, y_size));

    x_step = x_offset; x_size = x_original_size; y_size = x_original_size;
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVMWheel(0, -1, "v", ImVec2(x_size, y_size));

    x_step = x_offset; x_size = 100.0f; y_size = 52.0f;
    DisplayVMButton(SInput::MOUSE::BUTTON::BUTTON_6, "B6", ImVec2(x_size, y_size));
    DisplayVMButton(SInput::MOUSE::BUTTON::BUTTON_7, "B7", ImVec2(x_size, y_size));
    DisplayVMButton(SInput::MOUSE::BUTTON::BUTTON_8, "B8", ImVec2(x_size, y_size));

    ImGui::NextColumn();

    x_step = x_offset; x_size = 48.0f; y_size = 92.0f;
    DisplayVMButton(SInput::MOUSE::BUTTON::BUTTON_RIGHT, "Right", ImVec2(x_size, y_size));

    ImGui::End();
  }
}

void ImGui_SInput_Display::DisplayVGPButton(SInput::GAMEPAD::BUTTON button, std::string name, ImVec2 size)
{
  ImGui::PushID(2201 + button);
  if (SInput::VGamePad(0)->ButtonPressed(button))
  {
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(171, 102, 102));
  }
  else
  {
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(116, 78, 80));
  }

  if (ImGui::Button(name.c_str(), size))
  {
    SInput::VGamePad(0)->UpdateButton(0, button, SInput::GAMEPAD::ACTION::PRESSED, !is_active);
  }
  else
  {
    if (SInput::VGamePad(0)->ButtonPressed(button))
    {
      SInput::VGamePad(0)->UpdateButton(0, button, SInput::GAMEPAD::ACTION::RELEASED, !is_active);
    }
  }
  ImGui::PopStyleColor(1);
  ImGui::PopID();
}

void ImGui_SInput_Display::DisplayVirtualGamePad()
{
  if (show_virt_gamepad)
  {
    float x_offset = 8.0f;
    float x_step = 0.0f;
    float x_original_size = 28.0f;
    float x_size = 28.0f;
    float y_size = 28.0f;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);

    ImGui::Begin("Virtual GamePad", &show_virt_gamepad);

    ImGui::Columns(3, NULL, false);
    ImGui::SetColumnOffset(1, 73.0f);
    ImGui::SetColumnOffset(2, 144.0f);

    x_step = x_offset; x_size = 64.0f;
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_5, "LB", ImVec2(x_size, y_size));
    x_size = 64.0f; y_size = 60.0f;
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_9, "Left JS", ImVec2(x_size, y_size));
    x_size = x_original_size; y_size = x_original_size;
    ImGui::Dummy(ImVec2(x_size, y_size));
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_14, "Left", ImVec2(x_size, y_size));
    
    ImGui::NextColumn();

    x_step = x_offset; x_size = x_original_size; y_size = x_original_size;
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_size = 64.0f;
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_7, "Select", ImVec2(x_size, y_size));
    x_size = x_original_size;
    ImGui::Dummy(ImVec2(x_size, y_size));
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_11, "Up", ImVec2(x_size, y_size));
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_12, "Right", ImVec2(x_size, y_size));
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_13, "Down", ImVec2(x_size, y_size));

    ImGui::NextColumn();

    x_step = x_offset; x_size = x_original_size; y_size = x_original_size;
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 64.0f;
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_6, "RB", ImVec2(x_size, y_size));
    x_step = x_offset; 
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_8, "Start", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = x_original_size;
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_4, "Y", ImVec2(x_size, y_size));
    x_step = x_offset;
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_3, "X", ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_2, "B", ImVec2(x_size, y_size));
    x_step = x_offset;
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step);
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_1, "A", ImVec2(x_size, y_size));
    x_step = x_offset;
    ImGui::Dummy(ImVec2(x_size, y_size));
    x_step += x_size + x_offset; ImGui::SameLine(x_step); x_size = 64.0f; y_size = 60.0f;
    DisplayVGPButton(SInput::GAMEPAD::BUTTON::BUTTON_10, "Right JS", ImVec2(x_size, y_size));

    ImGui::End();
  }
}