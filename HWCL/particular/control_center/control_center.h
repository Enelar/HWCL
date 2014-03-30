#pragma once

#include "../export_header.h"
#include "program.h"
#include "process.h"

#include <string>

#include "../import_center/string_param.h"


namespace particular
{
  class _HWCL_METHOD_ control_center
  {
  public:
    program CompileProgram(const string_param &filename);
    process ExecuteProgram(const program &);
    void VM_Step(double dt);
  };
}