#pragma once

#include "../../stdafx.h"

namespace vm
{
  namespace context_utils
  {
    struct labels
    {
      std::map<string, word> data;

      void Add(const std::string &, word);
      word Find(const std::string &) const;

      decltype(data) *operator->();
      const decltype(data) *operator->() const;
    };


  }
}