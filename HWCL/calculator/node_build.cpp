#include "node.h"

using namespace calculator;

namespace
{
  bool IsDownToken(token t)
  {
    const auto a = t.second;
    return a == "^";
  }

  bool IsUpToken(token t)
  {
    const auto a = t.second;
    return a == "+" || a == "-";
  }

  bool IsBlaToken(token t)
  {
    const auto a = t.second;
    return a == "*" || a == "/";
  }
}

tokenqueue node::Process(const tokenqueue &q)
{
  throw_assert(q.size());

  auto token = q.front();
  auto ret = make_unique<node>(token);

  if (IsDownToken(token))
    AttachDown(ret.get());
  else if (IsUpToken(token) && !down.prev)
    AttachUp(ret.get());
  else
    AttachNext(ret.get());

  auto saved = ret.release();
  if (q.size() == 1)
    return{};
  tokenqueue next_q = saved->Process({ ++q.begin() , q.end() });
  throw_assert(!next_q.size());

  return next_q;
}

node *node::Build(tokenqueue q)
{
  auto ret = make_unique<node>(token{ NUMBER, "1" });

  q.push_front({ SYMBOL, "*" });
  tokenqueue next_q = ret->Process(q);
  throw_assert(!next_q.size());

  return ret.release();
}