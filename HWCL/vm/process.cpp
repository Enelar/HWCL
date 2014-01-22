#include "process.h"

using namespace vm;

process::process(program::cached_program &_p)
: p(_p)
{

}

#ifdef _DEBUG_
#include <windows.h>
#include <sstream>
#include<iomanip>
#endif


void DebugOutput(const vector<string> &a)
{
#ifdef _DEBUG_
  std::stringstream ss;

  for (auto obj : a)
    ss << obj;
  OutputDebugString(ss.str().c_str());
#endif
}


string ToString(const word &t)
{
  std::stringstream ss;
  ss << std::setfill(' ') << std::setw(3) << t;
  return ss.str();
}

void process::Execute(word instructions)
{
  auto code = p.Code();
  while (instructions > 0)
  {
    --instructions;
    word instruction_id = eip++;
    if (instruction_id >= code.size())
      throw finished();
    auto current_instruction = code[instruction_id];

    try
    {
#ifdef _DEBUG_
      DebugOutput(
      {
        ToString(instruction_id),
        " EXECUTING: ",
        current_instruction->Source(),
        "\n"
      });
#endif

      current_instruction->Execute(c);
    }
    catch (program::goto_instruction g)
    {
#ifdef _DEBUG_
      DebugOutput(
      {
        ToString(instruction_id),
        " GOTO ",
        ToString(g.eip),
        "\n"
      });
#endif
      eip = g.eip;
      if (instruction_id + 1 == g.eip)
        return; // self goto
    }
  }
}

void process::Bind()
{
  word bind_eip = 0;
  for (auto instruction : p.Code())
  {
    try
    {
      instruction->Bind(c);
    }
    catch (program::label_instruction label)
    {
      c.Label(label.name, bind_eip);
    }
    bind_eip++;
  }
}
