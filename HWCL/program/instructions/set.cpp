#include "set.h"
#include "../../parser/parser.h"

using namespace program::instructions;

set::set(const string &source)
: instruction(source, "set")
{

}

bool set::Signature(const string &source)
{
  return parser::CompareCommand(source, "SET");
}

void set::Execute(vm::context &)
{

}