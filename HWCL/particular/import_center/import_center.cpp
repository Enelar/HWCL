#include "import_center.h"

using namespace particular;

static import_center_with_storage ic;

import_center &import_center::GetImportCenter()
{
  return ic;
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