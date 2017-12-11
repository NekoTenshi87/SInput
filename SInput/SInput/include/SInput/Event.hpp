#pragma once

namespace SInput
{
  #ifdef ENUM_NAME
  #undef ENUM_NAME
  #endif

  #define ENUM_NAME(NAME) NAME ,
  struct EVENTS
  {
    enum
    {
      UNKNOWN = -1,
      #include <SInput\EventEnums.inl>
      NUMBEROFEVENTS
    };
  };
  #undef ENUM_NAME





}