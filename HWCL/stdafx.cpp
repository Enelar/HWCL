#include "stdafx.h"
#include <sstream>

bool KnownBoolNames(const string &name)
{
  if (name == "ON")
    return true;
  if (name == "OFF")
    return false;
  _asm int 3;
  return true;
}

