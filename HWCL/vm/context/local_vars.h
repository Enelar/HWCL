#pragma once

#include "../../stdafx.h"

namespace vm
{
  namespace context_utils
  {
    struct local_vars
    {
      double NN[80];
      bool FL[127];
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