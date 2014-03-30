#include "box.h"

particular::box::box()
{
  AddLocal("DAY", &day, vm::NUMBER);
  AddLocal("TIME", &time, vm::NUMBER);
  AddLocal("HOUR", &hour, vm::NUMBER);
}