#include "tree.h"

using namespace calculator;

#include "../parser/parser.h"
#include <set>
#include <deque>

namespace
{
  token RecognizeFunction(token t)
  {
    if (t.first != VARIABLE)
      return t;
    const auto &str = t.second;
    set<string> functions = { "SQRT" };
    if (str[0] == '!')
      return token{ EXTERN_CONTEXT, str };
    if (functions.find(t.second) != functions.end())
      return token{ FUNCTION, str };
    if (str.find('.') != -1)
      return token{ STRUCT, str };
    return t;
  }
  int Level(string s)
  {
    if (s == "^")
      return 2;
    if (s == "*" || s == "/")
      return 1;
    return 0;
  }
  tokenqueue GetReversePolish(tokenqueue q)
  {
    tokenqueue ret;
    tokenqueue stack;
    bool on_exit_state = false;

    auto PopBraces = [&stack, &ret, &on_exit_state]()
    {
      while (stack.size())
      {
        auto t = stack.back();
        if (t.first == SYMBOL)
        {
          if (t.second == "(")
          {
            if (on_exit_state)
              throw syntax_error();
            stack.pop_back();
            return;
          }
        }
        stack.pop_back();
        ret.push_back(t);
      }
      if (!on_exit_state)
        throw syntax_error();
    };

    for (auto t : q)
    {
      if (t.first == NUMBER)
      {
        ret.push_back(t);
        continue;
      }
      if (t.first == SYMBOL)
      {
        if (t.second == "(")
        {
          stack.push_back(t);
          continue;
        }
        if (t.second == ")")
        {
          PopBraces();
          continue;
        }
        while (stack.size() && Level(stack.back().second) > Level(t.second))
        {
          ret.push_back(stack.back());
          stack.pop_back();
        }
        stack.push_back(t);
      }
      if (t.first == VARIABLE)
      {
        auto func = RecognizeFunction(t);
        if (func.first == FUNCTION)
          stack.push_back(func);
        else
          ret.push_back(func);
      }
    }

    on_exit_state = true;
    if (stack.size())
      PopBraces();
    if (stack.size())
      throw syntax_error();

    return ret;
  }
}



double tree::Calculate(::calculator::calculator::get_callback Get)
{
  auto polish_source = GetReversePolish(queue);
  deque<token> input{ polish_source.begin(), polish_source.end() };
  std::vector<token> stack;
  token result;
  double res;

  auto TokenToNumber = [Get](token t)
  {
    if (t.first == NUMBER)
      return convert<double>(t.second);
    if (t.first != VARIABLE && t.first != STRUCT && t.first != EXTERN_CONTEXT)
      throw_message("Cant convert token to variable");
    return Get(t.second);
  };

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
        throw syntax_error();
      double
        a = TokenToNumber(stack[stack.size() - 2]),
        b = TokenToNumber(stack[stack.size() - 1]);

      switch (token.second[0])
      {
      case '+':
        res = a + b;
        break;
      case '-':
        res = a - b;
        break;
      case '*':
        res = a * b;
        break;
      case '/':
        res = a / b;
        break;
      case '^':
        res = pow(a, b);
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
      if (token.second == "SQRT")
      {
        res = sqrt(TokenToNumber(stack[stack.size() - 1]));
        stack.pop_back();
      }
      else
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
    throw calculation_failed();
  return TokenToNumber(stack.front());
}

double tree::Calculate(node *r, ::calculator::calculator::get_callback Get)
{
  double ret;
  root = r;
  try
  {
    ret = Calculate(Get);
  }
  catch (...)
  {
    root = NULL;
    throw;
  }

  root = NULL;
  return ret;
}