#pragma once
#include "../stdafx.h"

#include "../program/cached_program.h"
#include "context.h"

namespace vm
{
  class virtual_machine;
  class process : object
  {
    program::cached_program p;
    word eip = 0; // next instruction

    context c;

  public:
    process(program::cached_program &);

    static const word default_instruction_execution_count = 30;
    void Execute(word instructions = default_instruction_execution_count);
    void Bind( virtual_machine & );

    struct finished {};
  };

  struct runtime_error
  {
    string error_name;
    runtime_error(const string &_n)
      : error_name(_n)
    {}
  };
}

#ifdef _DEBUG_
#include <windows.h>
#include <sstream>
#include<iomanip>
#endif

template<>
string convert(const vector<string> &a);
void DebugOutput(const vector<string> &a);
string ToString(const word &t);