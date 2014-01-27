#include "tree.h"

using namespace calculator;

#include <vector>

namespace
{
  enum TAG
  {
    UNDEFINED,
    NUMBER,
    VARIABLE,
    SYMBOL,
    FLUSH
  };
  bool IsChar(char ch)
  {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
  }

  bool IsNum(char ch)
  {
    return (ch >= '0' && ch <= '9');
  }

  list<pair<TAG, string>> Explode(string s)
  {
    list<pair<TAG, string>> ret;
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

  list<pair<TAG, string>> VacuumNumber(list<pair<TAG, string>> res)
  {
    list<pair<TAG, string>> ret;

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

  list<pair<TAG, string>> VacuumVariable(list<pair<TAG, string>> res)
  {
    list<pair<TAG, string>> ret;

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

  list<pair<TAG, string>> VacuumContext(list<pair<TAG, string>> res)
  {
    list<pair<TAG, string>> ret;

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

      if (b.first != VARIABLE && a.second != "!")
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

  list<pair<TAG, string>> VacuumStruct(list<pair<TAG, string>> res)
  {
    list<pair<TAG, string>> ret;

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
      res.push_front({ NUMBER, str });
    }
    return ret;
  }

  list<pair<TAG, string>> VacuumPower(list<pair<TAG, string>> res)
  {
    list<pair<TAG, string>> ret;

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

void tree::Build(string s)
{
  auto queue = Explode(s);
  queue = VacuumPower(VacuumContext(VacuumStruct(VacuumNumber(VacuumVariable(queue)))));
}