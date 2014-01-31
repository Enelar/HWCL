#pragma once

namespace particular
{
  enum DATA_TYPE
  {
    DOUBLE,
    BYTE,
    ENUM,
    STRING
  };
  typedef void *(*get_struct_field_callback)(const char *struct_name, const char *field_name, char *data_type);

  void SetStructFieldCallback(get_struct_field_callback);


}