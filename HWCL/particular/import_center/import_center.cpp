#include "import_center.h"

using namespace particular;

static import_center_with_storage ic;

import_center &import_center::GetImportCenter()
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

#include "../../stdafx.h"

bool import_center_with_storage::Imported() const
{
  auto *mem = reinterpret_cast<const ub *const>(this);
  // in case of pointer to virtual table
  for (word i = WORD_SIZE; i < sizeof(*this); i++)
    if (!mem[i])
      return false;
  return true;
}