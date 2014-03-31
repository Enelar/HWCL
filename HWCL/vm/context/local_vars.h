#pragma once

#include "../../stdafx.h"
#include <array>

namespace vm
{
  namespace context_utils
  {
    struct local_vars
    {
      array<double, 80> NN;
      array<bool, 127> FL;
      double DAY;
      // time TIME[4];
      string STR = string(64, 0); // fill 64 byte with zeros

      vector<double> local_NN;

      local_vars() = default;
      local_vars(const deque<ub> &);
      deque<ub> Serialize() const;
    };

    
  }
}