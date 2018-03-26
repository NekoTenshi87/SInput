#include <SInput\Binding.hpp>

namespace SInput
{
  void Binding::addValue(int value, int type)
  {
    enum_to_type[value] = type;
    type_to_enum[type] = value;
  }

  int Binding::toType(const int value) const
  {
    auto it = enum_to_type.find(value);

    if (it != enum_to_type.end())
    {
      return it->second;
    }

    return -1;
  }

  int Binding::toEnum(const int type) const
  {
    auto it = type_to_enum.find(type);

    if (it != type_to_enum.end())
    {
      return it->second;
    }

    return -1;
  }

  const std::string& Binding::getName() const
  {
    return m_name;
  }

  bool Binding::empty() const
  {
    if (!enum_to_type.empty() || !type_to_enum.empty())
    {
      return false;
    }

    return true;
  }
}

