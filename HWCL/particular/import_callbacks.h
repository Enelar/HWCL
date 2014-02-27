#pragma once
#include "export_header.h"

namespace particular
{
#include "../vm/types/pointer_var_type.h"
  typedef vm::VAR_TYPE DATA_TYPE;

  struct param
  {
    char *name;
    void *addr;
    DATA_TYPE type;

    ~param()
    {

    }
  };

  typedef void(*get_struct_callback)(int field_count, param *fields);
  typedef bool(*request_get_struct_callback)(const char *name, get_struct_callback);
  _HWCL_METHOD_ bool GetStructCallback(request_get_struct_callback);

  typedef void *(*get_struct_field_callback)(const char *struct_name, const char *field_name, char *data_type);


  _HWCL_METHOD_ void SetStructFieldCallback(get_struct_field_callback);
}