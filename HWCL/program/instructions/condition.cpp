#include "condition.h"
#include "../../parser/parser.h"
#include "../../algebra/comparator/comparator.h"
#include "../../translator/translator.h"


using namespace program::instructions;

condition::condition(const string &source)
: instruction(source, "condition")
{
  auto t0 = parser::Split(Source(), "IF");
  throw_assert(t0.size() == 2);

  auto t1 = parser::Split(t0[1], "THEN");
  throw_assert(t1.size() == 2);
  auto condition_string = t1[0];

  auto t2 = parser::Split(t1[1], "ELSE");
  throw_assert(t2.size() < 3);
  if (t2.size() == 1)
    t2.push_back("-- ELSE STATEMENT NOT FOUND");
  auto then_string = t2[0];
  auto else_string = t2[1];

  then = translator::Translate(then_string);
  otherwise = translator::Translate(else_string);

  comp = make_shared<algebra::comparator>(condition_string);
  comp->Build();
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

  comp->Calculate(GetC);
}

void condition::Bind(vm::context &c)
{
  then->Bind(c);
  otherwise->Bind(c);
}