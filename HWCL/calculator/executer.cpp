#include "executer.h"

using namespace calculator;

executer::executer(const node *root)
{
  
}

const node *executer::Next(const node *n)
{
  throw_assert(n);


  if (n->next.next)
  {
    commands.push_back(NEXT);
    return n->next.next;
  }
  if (n->down.next)
    return n->down.next;

  throw_assert(n->next.prev); // not end of queue
  return n->down.prev;
}

executer::token_map::const_iterator executer::GetLevel(int)
{
  todo(Get level);
}