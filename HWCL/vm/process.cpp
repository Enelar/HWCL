#include "process.h"

using namespace vm;

process::process(program::cached_program &_p)
: p(_p)
{

}

void process::Execute(word instructions)
{
  auto code = p.Code();
  while (instructions >= 0)
  {
    --instructions;
    word instruction_id = eip++;
    if (instruction_id >= code.size())
      throw finished();
    auto current_instruction = code[instruction_id];

    try
    {
      current_instruction->Execute(c);
    }
    catch (program::goto_instruction g)
    {
      eip = g.eip;
    }
  }
}

void process::Bind()
{
  for (auto instruction : p.Code())
  {
    try
    {
      instruction->Bind(c);
    }
    catch (program::label_instruction label)
    {
      //eip = 
    }
  }
}
