#include "step.h"
#include "../../parser/parser.h"

using namespace program::instructions;

step::step(const string &source)
: instruction(source, "step")
{

}

bool step::Signature(const string &source)
{
  return parser::CompareCommand(source, "STEP");
}

void step::Execute(vm::context &)
{

}

step::step(const deque<ub> &orign)
: step(string{ orign.begin(), orign.end() })
{

}

deque<ub> step::Serialize()
{
  return{ Source().begin(), Source().end() };
}