#include "import_callbacks.h"

using namespace particular;

request_get_struct_callback GSCB = nullptr;
get_enum_value_callback GECB = nullptr;


_HWCL_METHOD_ bool particular::GetStructCallback(request_get_struct_callback cb)
{
  GSCB = cb;
  return true;
}

_HWCL_METHOD_ bool particular::GetEnumValueCallback(get_enum_value_callback cb)
{
  GECB = cb;
  return true;
}