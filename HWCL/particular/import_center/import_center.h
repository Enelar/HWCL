#pragma once

#include "../export_header.h"
#include "param.h"

#include <string>

#include "../control_center/control_center.h"

namespace particular
{
  struct _HWCL_METHOD_ import_center
  {
    static import_center &GetImportCenter();
    typedef void(*get_struct_callback)(int field_count, param *fields);
    typedef bool(*request_get_struct_callback)(const std::string &name, get_struct_callback);

    typedef int(*get_enum_value_callback)(const std::string &struct_name, const std::string &name);

    typedef bool(*get_bool_value_callback)(const std::string &name);

    virtual bool Imported() const = 0;
    control_center GetControlCenter() const;

    virtual bool GetStructCallback(request_get_struct_callback) = 0;
    virtual bool GetEnumValueCallback(get_enum_value_callback) = 0;
    virtual void SetStoragesPath(const string_param &cl_files, const string_param &compiled_files, const string_param &states) = 0;
  };

#if CPP11_SUPPORTED
  struct import_center_with_storage : import_center
  {
    static import_center_with_storage &GetImportCenter();
    request_get_struct_callback rgscb = nullptr;
    get_enum_value_callback gevcb = nullptr;
    std::string
      cl_files_path,
      compiled_files_path,
      state_files_path;

    bool GetStructCallback(request_get_struct_callback) override;
    bool GetEnumValueCallback(get_enum_value_callback) override;
    void SetStoragesPath(const string_param &cl_files, const string_param &compiled_files, const string_param &states) override;

    bool Imported() const override;
  };
#endif
}