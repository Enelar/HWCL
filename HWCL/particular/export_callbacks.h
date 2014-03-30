#pragma once
#include "export_header.h"

namespace particular
{
  typedef unsigned int proc_handle, prog_handle;


  _HWCL_METHOD_ prog_handle CompileProgram(const char *filename);
  _HWCL_METHOD_ proc_handle ExecuteProgram(prog_handle);
  _HWCL_METHOD_ void VM_Step(double dt);
  
}