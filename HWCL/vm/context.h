#pragma once
#include "../stdafx.h"

#include <string>

namespace vm
{
  struct context : object
  {
    word NN[80];
    bool FL[127];
    // time TIME[4];
    std::string STR = std::string(64, 0); // fill 64 byte with zeros
  };
}