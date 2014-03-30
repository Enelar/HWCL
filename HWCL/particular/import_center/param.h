#pragma once

#include "../export_header.h"
#include "string_param.h"

namespace particular
{
#include "../../vm/types/pointer_var_type.h"
  typedef vm::VAR_TYPE DATA_TYPE;

  struct param
  {
    string_param name;
    void *addr;
    DATA_TYPE type;

    param(char *n)
      : name(n), addr(NULL)
    {

    }

    param(const param &a)
      : name(a.name)
    {
      *this = a;
    }

    param &operator=(const param &a)
    {
      if (&a == this)
        return *this;
      name = a.name;

      addr = a.addr;
      type = a.type;
      return *this;
    }
  };
}