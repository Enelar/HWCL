#pragma once

#include "../export_header.h"
#include "param.h"

#include <string>

namespace particular
{
  _HWCL_METHOD_ struct import_center
  {
    static import_center &GetImportCenter();
    typedef void(*get_struct_callback)(int field_count, param *fields);
    typedef bool(*request_get_struct_callback)(const std::string &name, get_struct_callback);

    typedef int(*get_enum_value_callback)(const std::string &struct_name, const std::string &name);

    typedef bool(*get_bool_value_callback)(const std::string &name);

    virtual bool GetStructCallback(request_get_struct_callback) = 0;
    virtual bool GetEnumValueCallback(get_enum_value_callback) = 0;
  };

  struct import_center_with_storage : import_center
  {

    request_get_struct_callback rgscb = nullptr;
    get_enum_value_callback gevcb = nullptr;

    bool GetStructCallback(request_get_struct_callback) override;
    bool GetEnumValueCallback(get_enum_value_callback) override;
  };
}