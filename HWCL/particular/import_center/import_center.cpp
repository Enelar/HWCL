#include "import_center.h"

using namespace particular;

static import_center_with_storage ic;

import_center &import_center::GetImportCenter()
{
  return ic;
}

import_center_with_storage &import_center_with_storage::GetImportCenter()
{
  return ic;
}

control_center import_center::GetControlCenter() const
{
  return control_center();
}

bool import_center_with_storage::GetStructCallback(request_get_struct_callback cb)
{
  rgscb = cb;
  return true;
}

bool import_center_with_storage::GetEnumValueCallback(get_enum_value_callback cb)
{
  gevcb = cb;
  return true;
}

void import_center_with_storage::SetStoragesPath(const string_param &cl_files, const string_param &compiled_files, const string_param &states)
{
  compiled_files_path = compiled_files;
  state_files_path = states;
  cl_files_path = cl_files;
}

#include "../../stdafx.h"

bool import_center_with_storage::Imported() const
{
  struct uninited
  {
  };

  auto Assert = [](const bool value)
  {
    if (!value)
      throw uninited();
  };

  try
  {
    Assert(!!rgscb);
    Assert(!!gevcb);
    Assert(!!compiled_files_path.length());
    Assert(!!state_files_path.length());
    Assert(!!cl_files_path.length());
  }
  catch (uninited)
  {
    return false;
  }

  return true;
}