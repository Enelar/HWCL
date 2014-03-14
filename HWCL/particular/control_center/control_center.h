#pragma once

#include "../export_header.h"
#include "program.h"
#include "process.h"

#include <string>

namespace particular
{
  class _HWCL_METHOD_ control_center
  {
  public:
    program CompileProgram(const std::string &filename);
    process ExecuteProgram(const program &);
    void VM_Step(double dt);
  };
}