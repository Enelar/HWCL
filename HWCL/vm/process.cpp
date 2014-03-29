#include "process.h"
#include "vm.h"

using namespace vm;

process::process(program::cached_program &_p)
: p(_p)
{

}

void process::Execute(flt clock, word instructions)
{
  if (suspend_until > clock)
    return;

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
    catch (program::goto_instruction &g)
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
    catch (program::wait_instruction &w)
    {
      suspend_until = w.clock;
      if (w.continues)
        --eip;
    }
  }
}

void process::Bind( virtual_machine &_vm )
{
  auto code = p.Code();
  word bind_eip = 0, size = code.size();


  for (; bind_eip < size; bind_eip++)
  {
    auto instruction = code[bind_eip];

    try
    {
      instruction->Bind(c);
    }
    catch (program::label_instruction label)
    {
      c.Label(label.name, bind_eip);
    }
    catch (program::external_instruction ext)
    {
      DebugOutput(
      {
        "SYSTEM: EXTERNAL CONTEXT REQUEST ",
        ext.name,
        "\n"
      });
      bind_eip--;
      auto context = _vm.GetExternalContext(ext.name);
      c.external.insert({ ext.name, context });
    }
  }
}


void DebugOutput(const initializer_list<string> &a)
{
#ifdef _DEBUG_
  OutputDebugString(convert<string>(a).c_str());
#endif
}

string ToString(const word &t)
{
  std::stringstream ss;
  ss << std::setfill(' ') << std::setw(3) << t;
  return ss.str();
}