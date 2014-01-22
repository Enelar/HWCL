#include "sequence.h"
#include "../../parser/parser.h"

using namespace program::instructions;

sequence::sequence(const string &source)
: instruction(source)
{

}

bool sequence::Signature(const string &source)
{
  return parser::CompareCommand(source, "SEQUENCE");
}

void sequence::Execute(vm::context &)
{

}