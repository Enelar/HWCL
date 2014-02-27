#pragma once
#include "export_header.h"

#include <cstring>

namespace particular
{
#include "../vm/types/pointer_var_type.h"
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
    }

    ~param()
    {
      if (name)
        delete[] name;
    }
  };

  typedef void(*get_struct_callback)(int field_count, param *fields);
  typedef bool(*request_get_struct_callback)(const char *name, get_struct_callback);
  _HWCL_METHOD_ bool GetStructCallback(request_get_struct_callback);

  typedef void *(*get_struct_field_callback)(const char *struct_name, const char *field_name, char *data_type);


  _HWCL_METHOD_ void SetStructFieldCallback(get_struct_field_callback);
}