#include "phase.h"
#include "../../parser/parser.h"

using namespace program::instructions;

phase::phase(const string &source)
: instruction(source, "phase")
{

}

bool phase::Signature(const string &source)
{
  return parser::CompareCommand(source, "PHASE");
}

void phase::Execute(vm::context &)
{

}

phase::phase(const deque<ub> &)
: instruction("")
{

}

deque<ub> phase::Serialize()
{
  todo("Serialize");
}