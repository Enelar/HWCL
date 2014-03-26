#include "condition.h"
#include "../../parser/parser.h"
#include "../../algebra/comparator/comparator.h"
#include "../../translator/translator.h"
#include "composite.h"
#include "label.h"

static word id = 0;

using namespace program::instructions;

namespace
{
  composite MakeComposite(std::string str)
  {
    try
    {
      auto t = translator::Translate(str);
      return composite({ t });
    }
    catch (composite &e)
    {
      return e;
    }
    dead_space();
  }
  string ElseLabel()
  {
    stringstream ss;
    ss << "HWCLCONDITIONELSE" << id;
    return ss.str();
  }

  string EndLabel()
  {
    stringstream ss;
    ss << "HWCLCONDITIONEND" << id;
    return ss.str();
  }

  decltype(translator::Translate(string())) MakeLabel(string name)
  {
    return make_shared<label>(name);
  }

  decltype(translator::Translate(string())) MakeGoto(string name)
  {
    stringstream ss;
    ss << "GOTO " << name;
    return translator::Translate(ss.str());
  }

}

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

  comp = make_shared<algebra::comparator>(condition_string);
  comp->Build();

  try
  {
    then = translator::Translate(then_string);
    otherwise = translator::Translate(else_string);
    return;
  }
  catch (composite &)
  {
  }

  auto
    then_composite = MakeComposite(then_string),
    else_composite = MakeComposite(else_string);

  auto
    else_label = ElseLabel(),
    end_label = EndLabel();
  id++;

  then = translator::Translate("-- EMPTY THEN");
  otherwise = MakeGoto(else_label);

  composite ret({});
  for (auto t : then_composite.childs)
    ret.childs.push_back(t);
  ret.childs.push_back(MakeGoto(end_label));
  ret.childs.push_back(MakeLabel(else_label));
  for (auto t : else_composite.childs)
    ret.childs.push_back(t);
  ret.childs.push_back(MakeLabel(end_label));
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

condition::condition(const deque<ub> &)
: instruction("")
{

}

deque<ub> condition::Serialize()
{
  todo("Serialize");
}