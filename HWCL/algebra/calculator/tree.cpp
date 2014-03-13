#include "tree.h"

using namespace calculator;
using namespace algebra;

#include <deque>





double tree::Calculate(::calculator::calculator::get_callback Get)
{
  const auto &polish_source = reverse_polish;
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