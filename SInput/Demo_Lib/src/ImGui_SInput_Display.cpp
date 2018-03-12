
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

    }
    if (ImGui::CollapsingHeader("Combination Detection"))
    {

    }
    if (ImGui::CollapsingHeader("Stat Tracking"))
    {

    }
    if (ImGui::CollapsingHeader("N-Grams"))
    {

    }
    if (ImGui::CollapsingHeader("Pattern Recognition"))
    {

    }
    if (ImGui::CollapsingHeader("Full Scene Replay"))
    {

    }
    if (ImGui::CollapsingHeader("Single Source Rewind"))
    {

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