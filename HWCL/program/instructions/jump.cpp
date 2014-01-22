#include "jump.h"
#include "../../parser/parser.h"

using namespace program::instructions;

jump::jump(const string &source)
: instruction(source, "goto")
{

}

bool jump::Signature(const string &source)
{
  return parser::CompareCommand(source, "GOTO");
}

void jump::Execute(vm::context &)
{

}