#pragma once

namespace particular
{
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


  _HWCL_METHOD_ class process
  {
    PROC_STATUSES Status();
  };
}