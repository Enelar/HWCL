#include "tree.h"

using namespace calculator;

#include <vector>

#pragma region Vacuum
namespace
{
  bool IsChar(char ch)
  {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
  }

  bool IsNum(char ch)
  {
    return (ch >= '0' && ch <= '9');
  }

  tokenqueue Explode(string s)
  {
    tokenqueue ret;
    auto i = s.begin(), e = s.end();

    string summator;

    TAG tag = UNDEFINED, prev;

    while (i != e)
    {
      auto ch = *i;
      if (tag != FLUSH)
        prev = tag;
      switch (tag)
      {
      case UNDEFINED:
        if (IsChar(ch))
          tag = VARIABLE;
        else if (IsNum(ch))
          tag = NUMBER;
        else
          tag = SYMBOL;
        continue;
      case SYMBOL:
        summator += ch;
        tag = FLUSH;
        i++;
        break;
      case NUMBER:
        if (IsNum(ch))
          summator += ch;
        else
          tag = FLUSH;
        break;
      case VARIABLE:
        if (IsChar(ch))
          summator += ch;
        else
          tag = FLUSH;
        break;

      default:
        dead_space();
      }

      if (tag == FLUSH)
      {
        auto len = summator.length();
        ret.push_back({ prev, summator });
        summator = "";
        tag = UNDEFINED;
        continue;
      }

      i++;
    }
    if (summator.length())
      ret.push_back({ prev, summator });

    return ret;
  }

  tokenqueue VacuumNumber(tokenqueue res)
  {
    tokenqueue ret;

    auto Move = [&ret, &res](word count)
    {
      while (count-- > 0 && res.size())
      {
        ret.push_back(res.front());
        res.pop_front();
      }
    };

    bool comma_allowed = true, e_allowed = true;

    while (res.size())
    {
      if (res.front().first != NUMBER)
      {
        comma_allowed = true;
        e_allowed = true;
        Move(1);
        continue;
      }
      if (res.size() < 3)
      {
        Move(res.size());
        continue;
      }
      auto i = res.begin();
      auto
        a = *i++,
        b = *i++,
        c = *i++;

      if (c.first != NUMBER)
      {
        Move(1);
        continue;
      }

      if ((b.second == "." && !comma_allowed) || (b.second != "." && b.second != "E") || !e_allowed)
      {
        Move(1);
        continue;
      }

      if (b.second == ".")
        comma_allowed = false;
      if (b.second == "E")
      {
        comma_allowed = false;
        e_allowed = false;
      }

      auto str = convert<string, vector<string>>({ a.second, b.second, c.second });
      res.pop_front();
      res.pop_front();
      res.pop_front();
      res.push_front({NUMBER, str});
    }
    return ret;
  }

  tokenqueue VacuumVariable(tokenqueue res)
  {
    tokenqueue ret;

    auto Move = [&ret, &res](word count)
    {
      while (count-- > 0 && res.size())
      {
        ret.push_back(res.front());
        res.pop_front();
      }
    };

    while (res.size())
    {
      if (res.front().first != VARIABLE)
      {
        Move(1);
        continue;
      }
      if (res.size() < 2)
      {
        Move(res.size());
        continue;
      }
      auto i = res.begin();
      auto
        a = *i++,
        b = *i++;

      if (b.first != NUMBER)
      {
        Move(1);
        continue;
      }

      auto str = convert<string, vector<string>>({ a.second, b.second });
      res.pop_front();
      res.pop_front();
      res.push_front({ VARIABLE, str });
    }
    return ret;
  }

  tokenqueue VacuumContext(tokenqueue res)
  {
    tokenqueue ret;

    auto Move = [&ret, &res](word count)
    {
      while (count-- > 0 && res.size())
      {
        ret.push_back(res.front());
        res.pop_front();
      }
    };

    while (res.size())
    {
      if (res.front().first != SYMBOL)
      {
        Move(1);
        continue;
      }
      if (res.size() < 2)
      {
        Move(res.size());
        continue;
      }
      auto i = res.begin();
      auto
        a = *i++,
        b = *i++;

      if (b.first != VARIABLE || a.second != "!")
      {
        Move(1);
        continue;
      }

      auto str = convert<string, vector<string>>({ a.second, b.second });
      res.pop_front();
      res.pop_front();
      res.push_front({ VARIABLE, str });
    }
    return ret;
  }

  tokenqueue VacuumStruct(tokenqueue res)
  {
    tokenqueue ret;

    auto Move = [&ret, &res](word count)
    {
      while (count-- > 0 && res.size())
      {
        ret.push_back(res.front());
        res.pop_front();
      }
    };

    while (res.size())
    {
      if (res.front().first != VARIABLE)
      {
        Move(1);
        continue;
      }
      if (res.size() < 3)
      {
        Move(res.size());
        continue;
      }
      auto i = res.begin();
      auto
        a = *i++,
        b = *i++,
        c = *i++;

      if (b.second != "." || c.first != VARIABLE)
      {
        Move(1);
        continue;
      }

      auto str = convert<string, vector<string>>({ a.second, b.second, c.second });
      res.pop_front();
      res.pop_front();
      res.pop_front();
      res.push_front({ VARIABLE, str });
    }
    return ret;
  }

  tokenqueue VacuumPower(list<pair<TAG, string>> res)
  {
    tokenqueue ret;

    auto Move = [&ret, &res](word count)
    {
      while (count-- > 0 && res.size())
      {
        ret.push_back(res.front());
        res.pop_front();
      }
    };

    while (res.size())
    {
      if (res.front().first != SYMBOL)
      {
        Move(1);
        continue;
      }
      if (res.size() < 2)
      {
        Move(res.size());
        continue;
      }
      auto i = res.begin();
      auto
        a = *i++,
        b = *i++;

      if (a.second != "*" || b.second != "*")
      {
        Move(1);
        continue;
      }

      res.pop_front();
      res.pop_front();
      res.push_front({ SYMBOL, "^" });
    }
    return ret;
  }
}
#pragma endregion /* Vacuuming token of queue */

void tree::Build(string s)
{
  queue = Explode(s);
  queue = VacuumPower(VacuumContext(VacuumStruct(VacuumNumber(VacuumVariable(queue)))));
  root = node::Build(queue);
  nodes_count = queue.size();
}

#include "executer.h"
#include "../parser/parser.h"
#include <set>

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

    auto PopBraces = [&stack, &ret]()
    {
      while (stack.size())
      {
        auto t = stack.back();
        if (t.first == SYMBOL)
        {
          if (t.second == "(")
          {
            stack.pop_back();
            return;
          }
        }
        stack.pop_back();
        ret.push_back(t);
      }
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

    try
    {
      PopBraces();
    }
    catch (syntax_error)
    {
    }
    if (stack.size())
    {
      throw syntax_error();
    }

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

  throw_assert(stack.size() == 1);
  return TokenToNumber(stack.front());

  // reverse polish notation
  dead_space();
  word remain_iterations = nodes_count;


  shared_ptr<node> safe_node(root);
  root = NULL;


  while (remain_iterations--)
  {
    executer ex(safe_node);
    auto ret = ex.Execute();
    throw_assert(ret);
    safe_node.swap(ret);

    if (!ret->Alone())
      continue;

    auto token = ret->Token();
    if (token.first != TAG::NUMBER)
      break;
    return [token]()
    {
      stringstream ss;
      ss << token.second;
      double ret;
      ss >> ret;
      return ret;
    }();
  }
  
  throw_assert(safe_node.unique())
  root = safe_node.get();
  safe_node.reset();

  throw calculation_failed();
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