#pragma once

#include "../export_header.h"
#include <cstring>

namespace particular
{
#include "../../vm/types/pointer_var_type.h"
  typedef vm::VAR_TYPE DATA_TYPE;

  struct param
  {
    char *name;
    void *addr;
    DATA_TYPE type;

    param(char *_name)
      : name(NULL)
    {
      int length = strlen(_name);
      name = new char[length + 1];
      memcpy(name, _name, length + 1);
    }

    param(const param &a)
    {
      *this = a;
    }

    param &operator=(const param &a)
    {
      if (&a == this)
        return *this;
      int length = strlen(a.name);
      name = new char[length + 1];
      memcpy(name, a.name, length + 1);

      addr = a.addr;
      type = a.type;
      return *this;
    }

    ~param()
    {
      if (name)
        delete[] name;
    }
  };
}