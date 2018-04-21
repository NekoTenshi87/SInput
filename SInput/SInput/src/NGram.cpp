#include <SInput\NGram.hpp>
#include <algorithm>
#include <stack>

namespace SInput
{
  NGram N_Gram;

  NGram::NGram() {}

  NGram::~NGram() {}

  void NGram::AddKeysToNGrams(std::list<SerializeKey> key_data)
  {
    for (auto data : key_data)
    {
      AddToUniGramKeys(data.key);
    }
  }

  void NGram::AddMouseToNGrams(std::list<SerializeMouse> mouse_data)
  {
    for (auto data : mouse_data)
    {
      AddToUniGramMouse(data.button);
    }
  }

  void NGram::AddGamePadToNGrams(std::list<SerializeGamePad> gp_data)
  {
    for (auto data : gp_data)
    {
      AddToUniGramGamePad(data.button);
    }
  }

  void NGram::AddToUniGramKeys(KEYBOARD::KEY key)
  {
    if (Uni_Gram_Keys[key].key == KEYBOARD::KEY::UNKNOWN_KEY)
    {
      Uni_Gram_Keys[key].key = key;
    }

    ++Uni_Gram_Keys[key].times_seen;
  }

  void NGram::AddToUniGramMouse(MOUSE::BUTTON button)
  {
    if (Uni_Gram_Mouse[button].button == MOUSE::BUTTON::UNKNOWN_BUTTON)
    {
      Uni_Gram_Mouse[button].button = button;
    }

    ++Uni_Gram_Mouse[button].times_seen;
  }

  void NGram::AddToUniGramGamePad(GAMEPAD::BUTTON button)
  {
    if (Uni_Gram_GamePad[button].button == GAMEPAD::BUTTON::UNKNOWN_BUTTON)
    {
      Uni_Gram_GamePad[button].button = button;
    }

    ++Uni_Gram_GamePad[button].times_seen;
  }


  //void NGram::ClearTriKeys(NGramNodeKey* node)
  //{

  //}

  void NGram::ClearUniKeys()
  {
    for (int i = 0; i < KEYBOARD::KEY::NUMBEROFKEYS; ++i)
    {
      Uni_Gram_Keys[i].clear();
    }
  }

  void NGram::ClearUniMouse()
  {
    for (int i = 0; i < MOUSE::BUTTON::NUMBEROFMOUSEBUTTONS; ++i)
    {
      Uni_Gram_Mouse[i].clear();
    }
  }

  void NGram::ClearUniGamePad()
  {
    for (int i = 0; i < GAMEPAD::BUTTON::NUMBEROFGPBUTTONS; ++i)
    {
      Uni_Gram_GamePad[i].clear();
    }
  }

  void NGram::CalcUniGramKeys()
  {
    Uni_Gram_Keys_Result.clear();

    int total_seen = 0;

    for (int i = 0; i < KEYBOARD::KEY::NUMBEROFKEYS; ++i)
    {
      if (Uni_Gram_Keys[i].times_seen > 0)
      {
        Uni_Gram_Keys_Result.push_back(Uni_Gram_Keys[i]);
        total_seen += Uni_Gram_Keys[i].times_seen;
      }
    }

    for (size_t i = 0; i < Uni_Gram_Keys_Result.size(); ++i)
    {
      Uni_Gram_Keys_Result[i].percent = (float)(Uni_Gram_Keys_Result[i].times_seen) / (float)(total_seen);
    }

    std::sort(Uni_Gram_Keys_Result.begin(), Uni_Gram_Keys_Result.end(), NGramNodeKeyComp);
  }

  void NGram::CalcUniGramMouse()
  {
    Uni_Gram_Mouse_Result.clear();

    int total_seen = 0;

    for (int i = 0; i < MOUSE::BUTTON::NUMBEROFMOUSEBUTTONS; ++i)
    {
      if (Uni_Gram_Mouse[i].times_seen > 0)
      {
        Uni_Gram_Mouse_Result.push_back(Uni_Gram_Mouse[i]);
        total_seen += Uni_Gram_Mouse[i].times_seen;
      }
    }

    for (size_t i = 0; i < Uni_Gram_Mouse_Result.size(); ++i)
    {
      Uni_Gram_Mouse_Result[i].percent = (float)(Uni_Gram_Mouse_Result[i].times_seen) / (float)(total_seen);
    }

    std::sort(Uni_Gram_Mouse_Result.begin(), Uni_Gram_Mouse_Result.end(), NGramNodeMouseComp);
  }

  void NGram::CalcUniGramGamePad()
  {
    Uni_Gram_GamePad_Result.clear();

    int total_seen = 0;

    for (int i = 0; i < GAMEPAD::BUTTON::NUMBEROFGPBUTTONS; ++i)
    {
      if (Uni_Gram_GamePad[i].times_seen > 0)
      {
        Uni_Gram_GamePad_Result.push_back(Uni_Gram_GamePad[i]);
        total_seen += Uni_Gram_GamePad[i].times_seen;
      }
    }

    for (size_t i = 0; i < Uni_Gram_GamePad_Result.size(); ++i)
    {
      Uni_Gram_GamePad_Result[i].percent = (float)(Uni_Gram_GamePad_Result[i].times_seen) / (float)(total_seen);
    }

    std::sort(Uni_Gram_GamePad_Result.begin(), Uni_Gram_GamePad_Result.end(), NGramNodeGamePadComp);
  }

  std::vector<NGramNodeKeyData> NGram::GetUniGramKeysResult()
  {
    return Uni_Gram_Keys_Result;
  }

  std::vector<NGramNodeMouseData> NGram::GetUniGramMouseResult()
  {
    return Uni_Gram_Mouse_Result;
  }

  std::vector<NGramNodeGamePadData> NGram::GetUniGramGamePadResult()
  {
    return Uni_Gram_GamePad_Result;
  }
}