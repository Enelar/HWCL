#include "executer.h"
#include "tree.h"

using namespace calculator;

namespace
{
  struct end_of_queue
  {
  };
}

executer::executer(node::nextT _root)
: root(_root)
{
}

node::nextT executer::Execute()
{
  auto cur = root;
  int cur_level = 0;

  try
  {
    do
    {
      auto level = GetLevel(cur_level);
      level.push_back(cur);
      cur = Next(cur);

      if (commands.back() != NEXT)
        if (commands.back() == UP)
          cur_level++;
        else
          cur_level--;
    } while (true);
  }
  catch (end_of_queue &e)
  {
    return GetLevel(0).front();
  }

  auto IsBegin = [this](node::nextT p)
  {
    return p == root;
  };

  auto IsEnd = [cur](node::nextT p)
  {
    return p == cur;
  };

  unique_ptr<token> registers[3];

  for (auto level : turing_tape)
  {
    for (word i = 0; i < level.size(); i++)
    {
      auto it = level.begin() + i;
      auto &el = *it;
      if (el->Alone())
      {
        level.erase(it);
        i--;
        continue;
      }

      auto tok = el->Token();
      if (tok.first == VARIABLE)
      {
        el->Token(Recognize(el->Token()));
        continue;
      }
      if (tok.first == SYMBOL)
        registers[2] = make_unique<token>(tok);
      if (tok.first == VARIABLE)
        registers[2] = make_unique<token>(tok);
      auto next = Next(el);
      throw_assert(next);
      registers[3] = make_unique<token>(next->Token());

      if (el->Edge())
      {
        throw_assert(registers[2]->first == VARIABLE);
        if (registers[3]->second != "(")
          throw syntax_error();
        try
        {
          auto param = VacuumBraces(next);
          auto result = token{ NUMBER, convert<string>(param.first) };

          Replace(el, param.second, make_shared<node>(result));
        }
        catch (cant_vacuum)
        {
          return GetLevel(0).front();
        }
        continue;
      }

      auto prev = [el]()
      {
        auto ret = el->Back();
        if (ret)
          return ret;
        ret = el->Up();
        if (ret)
          return ret;
        return el->Down();
      }();

      if (prev->Token().first != NUMBER)
        continue;

      auto
        a = convert<double>(prev->Token().second),
        b = convert<double>(next->Token().second);
      token result;
      
      switch (tok.second[0])
      {
      case '+':
        result = { NUMBER, convert<string>(a + b) };
      case '-':
        result = { NUMBER, convert<string>(a - b) };
      case '*':
        result = { NUMBER, convert<string>(a * b) };
      case '/':
        result = { NUMBER, convert<string>(a / b) };
      case '^':
        result = { NUMBER, convert<string>(pow(a, b)) };
      default:
        dead_space();
      }

      Replace(prev, next, make_shared<node>(result));
      i--;
    }
  }
  dead_space();
}

#include <set>

token executer::Recognize(token t)
{
  if (t.first != VARIABLE)
    return t;
  std::set<string> functions = { "SQRT" };
  if (functions.find(t.second) != functions.end())
    return t;
  return token{ NUMBER, convert<string>(t.second) };
}

node::nextT executer::Next(node::nextT n)
{
  throw_assert(n);


  if (n->next.next)
  {
    commands.push_back(NEXT);
    return n->next.next;
  }
  if (n->down.next)
  {
    commands.push_back(DOWN);
    return n->down.next;
  }

  if (!n->next.prev)
    throw end_of_queue();

  commands.push_back(UP);
  return n->down.prev;
}

executer::token_map::const_reference executer::GetLevel(int lvl)
{
  int offset = zero_level_offset + lvl;

  if (offset < 0)
  {
    throw_assert(lvl - offset == -1);
    turing_tape.push_front({});
    offset++;
    return GetLevel(lvl);
  }
  if (offset == turing_tape.size())
  {
    turing_tape.push_back({});
    return GetLevel(lvl);
  }
  throw_assert(offset < turing_tape.size());

  return turing_tape.at(offset);
}

pair<double, node::nextT> executer::VacuumBraces(node::nextT origin)
{
  node::nextT cur = origin;
  word deeplevel = 0;

  auto GetNext = [this](node::nextT p)
  {
    try
    {
      return Next(p);
    }
    catch (end_of_queue)
    {
      auto ret = make_unique<node>(token(EMPTY, "after brace vacuum"));
      return p->AttachNext(ret.release());
    }
  };

  try
  {
    cur = Next(origin);
    auto tok = cur->Token();
    if (tok.second == "(")
      deeplevel++;
    if (tok.second == ")")
      if (deeplevel)
        deeplevel--;
      else
      {
        auto sequence = Erase(origin, cur);
        throw_assert(sequence);
        tree t;
        auto result = t.Calculate(sequence.get(), GetVariable);
        return pair<double, node::nextT>{ result, GetNext(cur) };
      }
  }
  catch (end_of_queue)
  {
    throw cant_vacuum();
  }

  dead_space();
}

node::nextT executer::Erase(node::nextT, node::nextT)
{
  todo(ERASE);
}

node::nextT executer::Replace(node::nextT, node::nextT, node::nextT value)
{
  todo(Replace);
}
