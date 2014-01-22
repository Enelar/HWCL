#include "external.h"
#include "../../parser/parser.h"

using namespace program::instructions;

external::external(const string &source)
: instruction(source, "external")
{

}

bool external::Signature(const string &source)
{
  return parser::CompareCommand(source, "EXTERNAL");
}

void external::Execute(vm::context &)
{

}