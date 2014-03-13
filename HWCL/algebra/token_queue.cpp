#include "token_queue.h"
#include <functional>

using namespace algebra;

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

  typedef function<void(word)> move_callback;
  typedef function<void(tokenqueue &ret, tokenqueue &res, move_callback Move)> vacuum_callback;
  tokenqueue Vacuum(tokenqueue res, vacuum_callback callback, TAG affects = UNDEFINED, int min_size = 1)
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
      if (affects != UNDEFINED && res.front().first != affects)
      {
        Move(1);
        continue;
      }
      if (min_size && res.size() < min_size)
      {
        Move(res.size());
        break;
      }
      callback(ret, res, Move);
    }


    return ret;
  }

  struct vacuum_number
  {
    bool
    comma_allowed,
    e_allowed;
    word ret_state = -1;
    void operator()(tokenqueue &ret, tokenqueue &res, move_callback Move)
    {
      if (ret_state != ret.size())
      {
        comma_allowed = true;
        e_allowed = true;
        ret_state = ret.size();
      }
      auto i = res.begin();
      auto
        a = *i++,
        b = *i++,
        c = *i++;

      if (c.first != NUMBER)
      {
        Move(1);
        return;
      }

      if ((b.second == "." && !comma_allowed) || (b.second != "." && b.second != "E") || !e_allowed)
      {
        Move(1);
        return;
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
      res.push_front({ NUMBER, str });
      ret_state = ret.size();
    }
  };

  void VacuumVariable(tokenqueue &ret, tokenqueue &res, move_callback Move)
  {
    auto i = res.begin();
    auto
      a = *i++,
      b = *i++;

    if (b.first != NUMBER)
      if (b.first != VARIABLE || !IsNum(a.second.back()))
      {
        Move(1);
        return;
      }

    auto str = convert<string, vector<string>>({ a.second, b.second });
    res.pop_front();
    res.pop_front();
    res.push_front({ VARIABLE, str });
  }


  void VacuumContext(tokenqueue &ret, tokenqueue &res, move_callback Move)
  {
    auto i = res.begin();
    auto
      a = *i++,
      b = *i++;

    if (b.first != VARIABLE || a.second != "!")
    {
      Move(1);
      return;
    }

    auto str = convert<string, vector<string>>({ a.second, b.second });
    res.pop_front();
    res.pop_front();
    res.push_front({ VARIABLE, str });
  }

  void VacuumStruct(tokenqueue &ret, tokenqueue &res, move_callback Move)
  {
    auto i = res.begin();
    auto
      a = *i++,
      b = *i++,
      c = *i++;

    if (b.second != "." || c.first != VARIABLE)
    {
      Move(1);
      return;
    }

    auto str = convert<string, vector<string>>({ a.second, b.second, c.second });
    res.pop_front();
    res.pop_front();
    res.pop_front();
    res.push_front({ VARIABLE, str });
  }

  void VacuumPower(tokenqueue &ret, tokenqueue &res, move_callback Move)
  {
    auto i = res.begin();
    auto
      a = *i++,
      b = *i++;

    if (a.second != "*" || b.second != "*")
    {
      Move(1);
      return;
    }

    res.pop_front();
    res.pop_front();
    res.push_front({ SYMBOL, "^" });
  }
}

#pragma endregion /* Vacuuming token of queue */


void algebra::token_queue::Build(const string &s)
{
  queue = Explode(s);
  queue = Vacuum(queue, VacuumVariable, VARIABLE, 2);
  vacuum_number VacuumNumber;
  queue = Vacuum(queue, VacuumNumber, NUMBER, 3);
  queue = Vacuum(queue, VacuumStruct, VARIABLE, 3);
  queue = Vacuum(queue, VacuumContext, SYMBOL, 2);
  queue = Vacuum(queue, VacuumPower, SYMBOL, 2);
}