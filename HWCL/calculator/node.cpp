#include "node.h"

using namespace calculator;

void node::Attach(node *const he, connect node::* _me)
{
  throw_assert(he);
  throw_assert(this); // lol

  connect
    &my = (this->*_me),
    &his = (he->*_me);

  throw_assert(!my.next);
  throw_assert(!his.prev);

  my.next = he;
  his.prev = this;
}

node *node::Deattach(connect node::* _me)
{
  throw_assert(this); // lol
  connect &my = (this->*_me);

  node *next = my.next;
  throw_assert(next);
  connect &his = (next->*_me);
  throw_assert(his.prev == this);

  his.prev = NULL;
  my.next = NULL;
  return next;
}

void node::AttachNext(node *const p)
{
  throw_assert(p);

  Attach(p, &node::next);
}

void node::AttachPrev(node *const p)
{
  throw_assert(p);

  p->AttachNext(this);
}

node *node::DeattachNext()
{
  return Deattach(&node::next);
}

node *node::DeattachPrev()
{
  return next.Backward()->DeattachNext();
}

void node::AttachDown(node *const p)
{
  throw_assert(p);

  Attach(p, &node::down);
}

void node::AttachUp(node *const p)
{
  throw_assert(p);

  p->AttachDown(this);
}

node *node::DeattachDown()
{
  return Deattach(&node::down);
}

node *node::DeattachUp()
{
  return down.Backward()->DeattachDown();
}

node *node::connect::Forward() const
{
  throw_assert(next);
  return next;
}

node *node::connect::Backward() const
{
  throw_assert(prev);
  return prev;
}

node::node(const token &_t)
: t(_t)
{

}