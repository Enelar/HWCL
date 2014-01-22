#include "local.h"
#include "../../parser/parser.h"

using namespace program::instructions;

local::local(const string &source)
: instruction(source)
{

}

bool local::Signature(const string &source)
{
  return parser::CompareCommand(source, "LOCAL");
}

void local::Execute(vm::context &)
{

}