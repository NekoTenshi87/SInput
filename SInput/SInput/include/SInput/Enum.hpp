// All content Copyright (c) DigiPen 2015
#pragma once

#include <string>
#include <unordered_map>

namespace SInput
{
  struct Enum
  {
  public:
    // Constructor
    Enum(const std::string& Name) : _name(Name) {}

    // Public Functions
    void addValue(const int value, const std::string& string);

    // Getter Functions
    const std::string& toStr(const int value) const;
    int toEnum(const std::string& string) const;

    // Public Data
    const std::string& getName() const;

    bool empty();

  private:

    const std::string _name;

    //Private Data
    std::unordered_map<int, std::string> strings;
    std::unordered_map<std::string, int> enums;
  };
}

//enum class color {red, blue, green};


//color r = red; // no compile
//color r = color::red; // compiles