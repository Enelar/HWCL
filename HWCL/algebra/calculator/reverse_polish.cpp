#include "tree.h"

using namespace calculator;
using namespace algebra;

#include "../../parser/parser.h"
#include <set>
#include <deque>

#pragma region ConvertToReversePolish
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
    if (s == "OR" || s == "AND")
      return -1;
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
      if (t.first == SYMBOL || t.first == OPERATOR)
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
#pragma endregion /* Converting to Reverse polish notation */

void tree::BuildReversePolish()
{
  reverse_polish = GetReversePolish(queue);
}

