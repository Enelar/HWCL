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