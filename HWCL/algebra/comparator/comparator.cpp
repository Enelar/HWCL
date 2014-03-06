#include "comparator.h"

using namespace algebra;

namespace
{
  tokenqueue ConditionOperators(const tokenqueue &src)
  {
    tokenqueue ret;
    for (auto token : src)
    {
      if (token.first == VARIABLE &&
        (token.second == "OR" || token.second == "AND"))
        token.first = OPERATOR;

      ret.push_back(token);
    }
    return ret;
  }
}

void comparator::Build()
{
  tq.Build(src_str);
  tq = ConditionOperators(tq);
}

namespace
{
  list<tokenqueue> SplitByBraces(const token_queue &src)
  {
    list<tokenqueue> ret;
    tokenqueue cur;
    bool in_brace = false, need_operator = false;

    for (auto token : src.queue)
    {
      if (need_operator)
        throw_sassert(token.first == OPERATOR, "Expected operator");
      if (token.first == OPERATOR && !in_brace)
      {
        ret.push_back(cur);
        ret.push_back({ token });
        cur.clear();
        continue;
      }
      if (token.first == SYMBOL)
      {
        if (token.second == "(")
        {
          throw_sassert(!in_brace, "Double braces in condition no yet supported");
          throw_sassert(!cur.size(), "Only supporting braces after OR/AND token");
          in_brace = true;
          continue;
        }
        if (token.second == ")")
        {
          throw_sassert(in_brace, "Missbrace found");
          throw_sassert(cur.size(), "Empty braces");
          in_brace = false;
          need_operator = true;
          continue;
        }
      }
      cur.push_back(token);
    }
    if (cur.size())
      ret.push_back(cur);
    throw_sassert(ret.size(), "Empty condition found");
    return ret;
  }
  vector<list<tokenqueue>> SplitByOperators(const list<tokenqueue> &src)
  {
    vector<list<tokenqueue>> ret;

    for (auto part : src)
    {
      ret.push_back({});
      auto &this_part = ret.back();
      this_part.push_back({});

      for (auto token : part)
      {
        if (token.first == OPERATOR)
        {
          throw_sassert(this_part.back().size(), "Found empty part near OR/AND statement");
          this_part.push_back({ token });
          this_part.push_back({});
          continue;
        }
        auto &this_queue = this_part.back();
        this_queue.push_back(token);
      }
      throw_sassert(this_part.front().size(), "Found empty part in condition token queue");
    }
    return ret;
  }
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

double comparator::Calculate(comparator::get_callback GetC)
{
  GetVariable = GetC;  auto tokens = SplitByOperators(SplitByBraces(tq));  word i_brace, e_brace = tokens.size();

  if (e_brace == 1)
    return CheckPart(tokens[0]);
  throw_assert(e_brace % 2 == 1); // 'A' 'OR' 'B' 'OR' 'C' - cant be % 2

  bool total_result;

  for (i_brace = 0; i_brace < e_brace; i_brace+=2)
  {
    bool result = CheckPart(tokens[i_brace]);

    if (!i_brace)
      total_result = result;
    if (!total_result)
    if (!result)
      total_result = false;

    if (i_brace + 1 >= e_brace)
      return total_result;

    auto next = tokens[i_brace + 1];
    if (next.begin()->front().second == "OR")
    {
      if (total_result)
        return true;
    }
    else
      if (!total_result)
        return false;
  }
  return total_result;
}

bool comparator::CheckPart(const tokenqueue &src)
{
  auto tokens = convert<tokenqueue>(src);
  throw_assert(tokens.size());
  if (tokens.size() == 1)
  {
    auto pointer = GetVariable(tokens.front().second);
    throw_assert(pointer->Type() == vm::BOOLEAN);
    return **static_pointer_cast<vm::pointer_interface<bool>>(pointer);
  }

  throw_assert(tokens.size() == 3); // A = B, A > B, A < B

  auto ToPointer = [this](const decltype(tokens.front()) &a)
  {
    auto str = a.second;
    return GetVariable(str);
  };

  int res = ComparePointers(ToPointer(tokens.front()), ToPointer(tokens.back()));
  auto op = 
    **
    static_pointer_cast
    <
      vm::pointer_interface<string>
    >
    (
      ToPointer
      (
        *
        (
          ++tokens.begin()
        )
      )
    );
  if (op == "=")
    return !res;
  if (op == "<")
    return res < 0;
  if (op == ">")
    return res > 0;
  dead_space();

}

bool comparator::CheckPart(const list<tokenqueue> &tokens)
{
  word i_brace, e_brace = tokens.size();

  if (e_brace == 1)
    return CheckPart(tokens.front());
  throw_assert(e_brace % 2 == 1); // 'A' 'OR' 'B' 'OR' 'C' - cant be % 2

  bool total_result;

  auto i = tokens.begin();
  for (i_brace = 0; i_brace < e_brace; i_brace += 2, ++i, ++i)
  {
    auto token = i;
    bool result = CheckPart(*i);

    if (!i_brace)
      total_result = result;
    if (!total_result)
    if (!result)
      total_result = false;

    if (i_brace + 1 >= e_brace)
      return total_result;

    auto next = i;
    next++;
    if (next->front().second == "OR")
    {
      if (total_result)
        return true;
    }
    else
    if (!total_result)
      return false;
  }
  return total_result;
}

comparator::comparator(const string &str)
: calculator_interface(str)
{

}