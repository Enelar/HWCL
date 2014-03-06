#include "condition.h"
#include "../../parser/parser.h"
#include "../../algebra/comparator/comparator.h"

using namespace program::instructions;

condition::condition(const string &source)
: instruction(source, "condition")
{

}

bool condition::Signature(const string &source)
{
  return parser::CompareCommand(source, "IF");
}

void condition::Execute(vm::context &c)
{
  algebra::comparator::get_callback GetC = [&c](const string &name)
  {
    return c.GetRawPointer(name);
  };
  algebra::comparator comp(Source());
  comp.Build();
  comp.Calculate(GetC);
}