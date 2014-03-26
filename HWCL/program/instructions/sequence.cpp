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

sequence::sequence(const deque<ub> &)
: instruction("")
{

}

deque<ub> sequence::Serialize()
{
  todo("Serialize");
}