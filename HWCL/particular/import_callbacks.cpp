#include "import_callbacks.h"

particular::get_struct_field_callback CB = nullptr;
particular::request_get_struct_callback GSCB = nullptr;

_HWCL_METHOD_ void particular::SetStructFieldCallback(particular::get_struct_field_callback cb)
{
  CB = cb;
}

_HWCL_METHOD_ bool particular::GetStructCallback(particular::request_get_struct_callback cb)
{
  GSCB = cb;
  return true;
}