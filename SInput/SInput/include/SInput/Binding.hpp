#pragma once
#include <unordered_map>
#include <string>

namespace SInput
{
  class Binding
  {
    private:
      const std::string m_name;
      std::unordered_map<int, int> enum_to_type;
      std::unordered_map<int, int> type_to_enum;

    public:
      Binding(const std::string& Name) : m_name(Name) {}

      void addValue(int value, int type);
      
      int toType(const int value) const;
      int toEnum(const int type) const;

      const std::string& getName() const;

      bool empty() const;
  };
}
