#include "comparator.h"

using namespace algebra;

namespace
{
  tokenqueue ConditionOperators(const tokenqueue &src)
  {
    auto EmptyString = [](const string &str)
    {
      for (auto ch : str)
        if (ch != ' ')
          return false;
      return true;
    };

    tokenqueue ret;
    for (auto token : src)
    {
      if (token.first == VARIABLE &&
        (token.second == "OR" || token.second == "AND"))
        token.first = OPERATOR;
      if (token.first == SYMBOL && EmptyString(token.second))
        continue;
      ret.push_back(token);
    }
    return ret;
  }
}

struct comparator_tree : public calculator::tree
{
  void Build(const string &str) override
  {
    algebra::token_queue::Build(str);
    queue = ConditionOperators(queue);
    BuildReversePolish();
  }
};


void comparator::Build()
{
  tq = make_unique<comparator_tree>();
  tq->Build(src_str);
}

#include <deque>

namespace
{
  int ComparePointers(const shared_ptr<vm::raw_pointer> &a, const shared_ptr<vm::raw_pointer> &b)
  {
    auto CompareNumb = [](const vm::floating_point &a, const vm::floating_point &b)
    {
      if (a < b)
        return -1;
      if (a > b)
        return 1;
      if (a == b)
        return 0;
      dead_space();
    };

    auto CompareString = [](const string &a, const string &b)
    {
      if (a < b)
        return -1;
      if (a > b)
        return 1;
      if (a == b)
        return 0;
      dead_space();
    };

    throw_assert(a->Type() == b->Type());
    if (a->Type() == vm::STRING)
    {
      auto
        atyped = static_pointer_cast<vm::pointer_interface<string>>(a),
        btyped = static_pointer_cast<vm::pointer_interface<string>>(b);
      return CompareString(**atyped, **btyped);
    }

    vm::floating_point aval, bval;
    if (a->Type() == vm::BOOLEAN)
    {
      aval = **static_pointer_cast<vm::pointer_interface<bool>>(a);
      bval = **static_pointer_cast<vm::pointer_interface<bool>>(b);
    }
    else if (a->Type() == vm::NUMBER)
    {
      aval = **static_pointer_cast<vm::pointer_interface<bool>>(a);
      bval = **static_pointer_cast<vm::pointer_interface<bool>>(b);
    }
    else if (a->Type() == vm::ENUM)
    {
      aval = **static_pointer_cast<vm::pointer_interface<bool>>(a);
      bval = **static_pointer_cast<vm::pointer_interface<bool>>(b);
    }
    else
      dead_space();
    return CompareNumb(aval, bval);
  }
}

#include "../../vm/context.h"

bool comparator::Calculate(comparator::get_callback Get)
{
  const auto &polish_source = tq->reverse_polish;
  deque<token> input{ polish_source.begin(), polish_source.end() };
  std::vector<token> stack;
  token result;
  double res;

  while (input.size())
  {
    result.first = UNDEFINED;
    auto token = input.front();
    bool recognized = false;
    if (!recognized && (token.first == NUMBER || token.first == VARIABLE || token.first == EXTERN_CONTEXT || token.first == STRUCT))
      result = token, recognized = true;
    if (!recognized && token.first == SYMBOL)
    {
      recognized = true;
      if (stack.size() < 2)
        throw calculator::syntax_error();
      auto
        a = Get(stack[stack.size() - 2].second);
      auto type = a->Type();
      decltype(a) b;
      try
      {
        b = Get(stack[stack.size() - 1].second);
      }
      catch (vm::context::variable_not_found)
      {
        if (type == vm::BOOLEAN)
          todo(CONST POINTERS);
          //b = make_shared<vm::pointer<bool>>(KnownBoolNames(stack[stack.size() - 1].second));
        if (type == vm::ENUM)
          todo(ENUM);
        
      }
      int compare = ComparePointers(a, b);

      throw_assert(token.second.size() == 1);
      switch (token.second[0])
      {
      case '=':
        res = !compare;
        break;
      case '>':
        res = compare > 0;
        break;
      case '<':
        res = compare < 0;
        break;
      default:
        recognized = false;
      }

      if (recognized)
      {
        stack.pop_back();
        stack.pop_back();
      }
    }

    if (!recognized && token.first == FUNCTION)
    {
      recognized = true;
      todo(FUNCTION);
    }

    throw_assert(recognized);
    if (recognized)
    {
      input.pop_front();
      if (result.first != UNDEFINED)
        stack.push_back(result);
      else
        stack.push_back({ NUMBER, convert<string>(res) });
    }
  }

  if (stack.size() != 1)
    throw calculator::calculation_failed();
  auto front = stack.front();
  if (front.second == "0")
    return false;
  if (front.second == "1")
    return true;
  if (parser::Split(front.second, '.').size() != 2)
    return KnownBoolNames(front.second);

  auto p = Get(front.second);
  return **static_pointer_cast<vm::pointer_interface<bool>>(p);
}
comparator::comparator(const string &str)
: calculator_interface(str)
{

}