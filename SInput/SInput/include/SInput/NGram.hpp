#pragma once

#include <SInput\DeviceList.hpp>
#include <SInput\Device.hpp>
#include <SInput\Serialize.hpp>
#include <list>
#include <unordered_map>
#include <vector>

namespace SInput
{
  struct NGramNodeKeyData
  {
    KEYBOARD::KEY key = KEYBOARD::KEY::UNKNOWN_KEY;
    int times_seen = 0;
    float percent = 0.0f;

    void clear() { key = KEYBOARD::KEY::UNKNOWN_KEY; times_seen = 0; percent = 0; }
    //bool operator() (NGramNodeKeyData a, NGramNodeKeyData b) { return (a.percent > b.percent); }
  };

  inline bool NGramNodeKeyComp(NGramNodeKeyData a, NGramNodeKeyData b) { return a.percent > b.percent; }

  struct NGramNodeKey
  {
    NGramNodeKeyData data;
    NGramNodeKey* children[KEYBOARD::KEY::NUMBEROFKEYS];
  };

  struct NGramNodeMouseData
  {
    MOUSE::BUTTON button = MOUSE::BUTTON::UNKNOWN_BUTTON;
    int times_seen = 0;
    float percent = 0.0f;

    void clear() { button = MOUSE::BUTTON::UNKNOWN_BUTTON; times_seen = 0; percent = 0; }
    //bool operator() (NGramNodeMouseData a, NGramNodeMouseData b) { return (a.percent > b.percent); }
  };

  inline bool NGramNodeMouseComp(NGramNodeMouseData a, NGramNodeMouseData b) { return a.percent > b.percent; }

  struct NGramNodeMouse
  {
    NGramNodeMouseData data;
    NGramNodeMouse* children[MOUSE::BUTTON::NUMBEROFMOUSEBUTTONS];
  };

  struct NGramNodeGamePadData
  {
    GAMEPAD::BUTTON button = GAMEPAD::BUTTON::UNKNOWN_BUTTON;
    int times_seen = 0;
    float percent = 0.0f;

    void clear() { button = GAMEPAD::BUTTON::UNKNOWN_BUTTON; times_seen = 0; percent = 0; }
    //bool operator() (NGramNodeGamePadData a, NGramNodeGamePadData b) { return (a.percent > b.percent); }
  };

  inline bool NGramNodeGamePadComp(NGramNodeGamePadData a, NGramNodeGamePadData b) { return a.percent > b.percent; }

  struct NGramNodeGamePad
  {
    NGramNodeGamePadData data;
    NGramNodeGamePad* children[GAMEPAD::BUTTON::NUMBEROFGPBUTTONS];
  };

  class NGram
  {
    public:
      NGram();
      ~NGram();

      void AddKeysToNGrams(std::list<SerializeKey> key_data);
      void AddMouseToNGrams(std::list<SerializeMouse> mouse_data);
      void AddGamePadToNGrams(std::list<SerializeGamePad> gamepad_data);

      //void AddToTriGramKeys(KEYBOARD::KEY key1, KEYBOARD::KEY key2, KEYBOARD::KEY key3);
      //void AddToBiGramKeys(KEYBOARD::KEY key1, KEYBOARD::KEY key2);
      void AddToUniGramKeys(KEYBOARD::KEY key);

      void AddToUniGramMouse(MOUSE::BUTTON button);

      void AddToUniGramGamePad(GAMEPAD::BUTTON button);

      std::vector<NGramNodeKeyData> GetUniGramKeysResult();
      std::vector<NGramNodeMouseData> GetUniGramMouseResult();
      std::vector<NGramNodeGamePadData> GetUniGramGamePadResult();

      void CalcUniGramKeys();
      void CalcUniGramMouse();
      void CalcUniGramGamePad();

    private:
      //NGramNodeKey* Tri_Gram_Keys[KEYBOARD::KEY::NUMBEROFKEYS] = { nullptr };
      //NGramNodeKey* Bi_Gram_Keys[KEYBOARD::KEY::NUMBEROFKEYS] = { nullptr };
      NGramNodeKeyData Uni_Gram_Keys[KEYBOARD::KEY::NUMBEROFKEYS];
      std::vector<NGramNodeKeyData> Uni_Gram_Keys_Result;

      //void ClearTriKeys(NGramNodeKey* node);
      //void ClearBiKeys();
      void ClearUniKeys();
      
      //std::unordered_map<MOUSE::BUTTON, NGramNodeMouse*> Tri_Gram_Mouse;
      //std::unordered_map<MOUSE::BUTTON, NGramNodeMouse*> Bi_Gram_Mouse;
      NGramNodeMouseData Uni_Gram_Mouse[MOUSE::BUTTON::NUMBEROFMOUSEBUTTONS];
      std::vector<NGramNodeMouseData> Uni_Gram_Mouse_Result;

      //void ClearTriMouse();
      //void ClearBiMouse();
      void ClearUniMouse();

      //std::unordered_map<GAMEPAD::BUTTON, NGramNodeGamePad*> Tri_Gram_GamePad;
      //std::unordered_map<GAMEPAD::BUTTON, NGramNodeGamePad*> Bi_Gram_GamePad;
      NGramNodeGamePadData Uni_Gram_GamePad[GAMEPAD::BUTTON::NUMBEROFGPBUTTONS];
      std::vector<NGramNodeGamePadData> Uni_Gram_GamePad_Result;

      //void ClearTriGamePad();
      //void ClearBiGamePad();
      void ClearUniGamePad();
  };

  extern NGram N_Gram;
}