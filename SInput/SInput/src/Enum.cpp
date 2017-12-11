
#include <SInput\Enum.hpp>

namespace SInput
{
  void Enum::addValue(const int value, const std::string& string)
  {
    strings.emplace(value, string);
    enums.emplace(string, value);
  }

  const std::string& Enum::toStr(const int value) const
  {
    return strings.at(value);
  }

  int Enum::toEnum(const std::string& string) const
  {
    auto it = enums.find(string);

    if (it != enums.end())
    {
      return it->second;
    }

    return -1;
  }

  const std::string& Enum::getName() const
  {
    return _name;
  }

  bool Enum::empty()
  {
    if (!strings.empty() || !enums.empty())
    {
      return false;
    }

    return true;
  }
}
