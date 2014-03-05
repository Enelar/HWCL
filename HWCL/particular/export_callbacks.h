#pragma once
#include "export_header.h"

namespace particular
{
  typedef unsigned int proc_handle, prog_handle;

  enum PROC_STATUSES
  {
    UNDEFINED, // Invalid value
    STORING,  // Program save state performing
    RESTORING,  // Program load state performing
    PARSING, // Program transliteration
    COMPILING, // Linking with memory, compile instructions
    RUNNING, // Run state
    WAITING, // Wait for resource instruction
    PAUSED, // Execution paused
    STOPED, // Execution stopped (aborted)
    FINISHED, // Process finished

    INVALID_HANDLER, // System detected handler as invalid

    _FICTIVE_VALUE // Dont mess with comma and CVS
  };

  _HWCL_METHOD_ prog_handle CompileProgram(const char *filename);
  _HWCL_METHOD_ proc_handle ExecuteProgram(prog_handle);
  _HWCL_METHOD_ void VM_Step(double dt);
  _HWCL_METHOD_ void CloseHandle(proc_handle);
  _HWCL_METHOD_ PROC_STATUSES ProcessStatus(proc_handle);
}