#include "import_callbacks.h"

particular::get_struct_field_callback CB = nullptr;

_HWCL_METHOD_ void particular::SetStructFieldCallback(particular::get_struct_field_callback cb)
{
  CB = cb;
}