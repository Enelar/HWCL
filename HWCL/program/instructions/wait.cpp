#include "wait.h"
#include "../../parser/parser.h"

using namespace program::instructions;

wait::wait(const string &source)
: instruction(source, "wait")
{
  // TODO: Parse instruction
  // WAIT 1 sec AS condition -> false, until -> 1 sec
  // WAIT (a>3), UNTIL 60 AS condition -> a>3, until -> 60 sec
}

bool wait::Signature(const string &source)
{
  return parser::CompareCommand(source, "WAIT");
}

void wait::Execute(vm::context &c)
{
  if (!active)
  { // first time executed
    if (!proc)
      throw wait_instruction{ until, false };
    active = true;
  }
  if (proc->Calculate(nullptr))
  {
    active = false;
    return;
  }
  throw wait_instruction{ until, true };
}

wait::wait(const deque<ub> &)
: instruction("")
{

}

deque<ub> wait::Serialize()
{
  todo("Serialize");
}