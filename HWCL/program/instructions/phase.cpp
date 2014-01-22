#include "phase.h"
#include "../../parser/parser.h"

using namespace program::instructions;

phase::phase(const string &source)
: instruction(source)
{

}

bool phase::Signature(const string &source)
{
  return parser::CompareCommand(source, "PHASE");
}

void phase::Execute(vm::context &)
{

}