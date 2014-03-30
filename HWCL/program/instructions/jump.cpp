#include "jump.h"
#include "../../parser/parser.h"

using namespace program::instructions;

jump::jump(const string &source)
: instruction(source, "goto")
{
  auto split = parser::Split(source, "GOTO");
  name = parser::Trim(split.back());
}

bool jump::Signature(const string &source)
{
  return parser::CompareCommand(source, "GOTO");
}

void jump::Execute(vm::context &c)
{
  word eip = c.Label(name);
  throw goto_instruction{ eip };
}

void jump::Bind(vm::context &c)
{

}