#pragma once

#include <IMGUI\imgui.h>
#include <string>
#include <iostream>
#include <sstream>

static std::stringbuf log_buffer;
static size_t old_log_pos = 0;

struct ExampleAppLog
{
  ExampleAppLog() { std::clog.rdbuf(&log_buffer); }

  ImGuiTextBuffer     Buf;
  ImGuiTextFilter     Filter;
  ImVector<int>       LineOffsets;        // Index to lines offset
  bool                ScrollToBottom;

  void    Clear() { Buf.clear(); LineOffsets.clear(); }

  void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
  {
    int old_size = Buf.size();
    va_list args;
    va_start(args, fmt);
    Buf.appendv(fmt, args);
    va_end(args);
    for (int new_size = Buf.size(); old_size < new_size; old_size++)
      if (Buf[old_size] == '\n')
        LineOffsets.push_back(old_size);
    ScrollToBottom = true;
  }

  void    AddLog()
  {
    std::string string_temp(log_buffer.str());
    std::string log_string = string_temp.substr(old_log_pos, string_temp.size() - old_log_pos);

    int old_size = Buf.size();
    old_log_pos = string_temp.size();

    Buf.append(log_string.c_str());

    for (int new_size = Buf.size(); old_size < new_size; old_size++)
      if (Buf[old_size] == '\n')
        LineOffsets.push_back(old_size);
    //ScrollToBottom = true;
  }

  void    Draw(const char* title, bool* p_open = NULL)
  {
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin(title, p_open);
    ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    ImGui::TextUnformatted(Buf.begin());

    if (ScrollToBottom)
      ImGui::SetScrollHere(1.0f);
    ScrollToBottom = false;
    ImGui::EndChild();
    ImGui::End();
  }
};

class ImGui_SInput_Display
{
  public:
    ImGui_SInput_Display() {}
    ~ImGui_SInput_Display() {}

    void DisplaySInputWindow();
    void DisplayDebbugWindow();

    bool is_active = false;
    bool show_log_window = true;
    bool show_keys = true;
    bool show_mouse_buttons = true;
    bool show_mouse_scroll = true;
    bool show_mouse_pos = true;
    bool show_gamepad_buttons = true;
    bool show_gamepad_connect = true;
    bool show_gamepad_axis = true;
    bool show_pnp_detection = true;

    bool show_num_times_triggered = true;
    bool show_avg_time_pressed = true;
    bool show_percent_of_usage = true;
    bool show_most_common_next = true;
    int num_most_common_next = 5;

    bool use_single_bind = true;

    ImVec4 color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

