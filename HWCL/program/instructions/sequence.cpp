#include "sequence.h"
#include "../../parser/parser.h"

using namespace program::instructions;

sequence::sequence(const string &source)
: instruction(source, "sequence")
{

}

bool sequence::Signature(const string &source)
{
  return parser::CompareCommand(source, "SEQUENCE");
}

void sequence::Execute(vm::context &)
{

}

sequence::sequence(const deque<ub> &orign)
: sequence(string{ orign.begin(), orign.end() })
{

}

deque<ub> sequence::Serialize()
{
  return{ Source().begin(), Source().end() };
}