#include "node.h"

using namespace calculator;

node::nextT node::Attach(node *const he, connect node::* _me)
{
  throw_assert(he);
  throw_assert(this); // lol

  connect
    &my = (this->*_me),
    &his = (he->*_me);

  throw_assert(!my.next);
  throw_assert(!his.prev);

  my.next.reset(he);
  his.prev.reset(this);

  return my.next;
}

node::nextT node::Deattach(connect node::* _me)
{
  throw_assert(this); // lol
  connect &my = (this->*_me);

  auto next = my.next;
  throw_assert(next);

  connect &his = (next.get()->*_me);
  throw_assert(his.prev.get() == this);

  his.prev = NULL;
  my.next = NULL;
  return next;
}

node::nextT node::AttachNext(node *const p)
{
  throw_assert(p);

  return Attach(p, &node::next);
}

node::nextT node::AttachPrev(node *const p)
{
  throw_assert(p);

  return p->AttachNext(this);
}

node::nextT node::DeattachNext()
{
  return Deattach(&node::next);
}

node::nextT node::DeattachPrev()
{
  return next.Backward()->DeattachNext();
}

node::nextT node::AttachDown(node *const p)
{
  throw_assert(p);

  return Attach(p, &node::down);
}

node::nextT node::AttachUp(node *const p)
{
  throw_assert(p);

  return p->AttachDown(this);
}

node::nextT node::DeattachDown()
{
  return Deattach(&node::down);
}

node::nextT node::DeattachUp()
{
  return down.Backward()->DeattachDown();
}

node *node::connect::Forward() const
{
  throw_assert(next);
  return next.get();
}

node *node::connect::Backward() const
{
  throw_assert(prev);
  return prev.get();
}

node::node(const token &_t)
: t(_t)
{

}

node::nextT node::Back() const
{
  return next.prev;
}

node::nextT node::Forward() const
{
  return next.next;
}

node::nextT node::Up() const
{
  return down.prev;
}
node::nextT node::Down() const
{
  return down.next;
}

bool node::Alone() const
{
  return !Back() && !Forward() && !Down() && !Up();
}
bool node::Edge() const
{
  return !!Back() + !!Forward() + !!Down() + !!Up() == 1;
}

token node::Token() const
{
  return t;
}

token node::Token(token next)
{
  ax::Swap<>(t, next);
  return next;
}
