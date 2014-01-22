#include "condition.h"
#include "../../parser/parser.h"

using namespace program::instructions;

condition::condition(const string &source)
: instruction(source)
{

}

bool condition::Signature(const string &source)
{
  return parser::CompareCommand(source, "IF");
}

void condition::Execute(vm::context &)
{

}