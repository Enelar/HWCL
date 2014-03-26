#include "set.h"
#include "../../parser/parser.h"
#include "../../algebra/calculator/calculator.h"
#include "../../vm/process.h"

using namespace program::instructions;

set::set(const string &source)
: instruction(source, "set")
{

}

set::~set()
{
  if (proc)
    delete proc;
}

bool set::Signature(const string &source)
{
  return parser::CompareCommand(source, "SET");
}

void set::Bind(vm::context &c)
{
  auto tokens = parser::Split(Source() , ' ', true);
  string expr = convert<string, deque<string>>({ tokens.begin() + 1, tokens.end() });

  auto t = parser::Split(expr, '=', true);
  auto name = t[0];
  variable = name;

  decltype(tokens) expr_tokens;
  throw_assert(t.size() == 2); // mean SET A=B=C
  expr_tokens.assign(t.begin() + 1, t.end());
  assignee = t[1];

  expr = convert<string, deque<string>>({ expr_tokens.begin(), expr_tokens.end() });
  proc = NEW calculator::calculator(expr);
}

void set::Execute(vm::context &c)
{
  throw_assert(proc);

  auto type = c.GetType(variable);

  if (type == vm::STRING)
  {
    auto p = c.GetPointer<string>(variable);
    auto parts = parser::Split(assignee, '"');
    throw_assert(parts.size() >= 2);
    throw_assert(parts.size() < 3); // 0"1"2

    p->Set(parts[1]);
    return;
  }

  if (type == vm::BOOLEAN)
  {
    auto p = c.GetPointer<bool>(variable);
    if (parser::Split(assignee, '.').size() == 2)
    {
      auto val = c.GetPointer<bool>(assignee);
      p->Set(**val);
      return;
    }
    p->Set(KnownBoolNames(assignee));
    return;
  }

  if (type == vm::ENUM)
  {
    auto p = c.GetPointer<int>(variable);
    auto val = c.EnumWorkAround(variable, assignee);
    p->Set(val);
    return;
  }

  if (type == vm::NUMBER)
  {
    auto p = c.GetPointer<vm::floating_point>(variable);

    calculator::calculator::get_callback GetC = [&](string name) -> vm::floating_point
    {
      return **c.GetPointer<vm::floating_point>(variable);
    };

    double res = proc->Calculate(GetC);

    p->Set(res);
    return;
  }

  dead_space();
}

set::set(const deque<ub> &)
: instruction("")
{

}

deque<ub> set::Serialize()
{
  todo("Serialize");
}