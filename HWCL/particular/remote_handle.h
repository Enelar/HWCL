#pragma once
#include "../stdafx.h"

namespace particular
{
  struct remote_handle
  {
#define PROGRAM_HANDLE_CHECK_VALUE 0xC0DE
    word header = 0xC0DE;

    bool IsValid()
    {
      return header == PROGRAM_HANDLE_CHECK_VALUE;
    }

    template<typename T>
    static T &Undestand( int p )
    {
      auto *t = reinterpret_cast<remote_handle *>(p);
      if (!t->IsValid())
        throw invalid();
      return *reinterpret_cast<T *>(p);
    }

    struct invalid
    {};
  };
}