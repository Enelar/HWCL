#pragma once
#include "../stdafx.h"

#include <deque>

namespace algebra
{
  enum TAG
  {
    UNDEFINED,
    NUMBER,
    VARIABLE,
    FUNCTION,
    EXTERN_CONTEXT,
    STRUCT,
    SYMBOL,
    OPERATOR,
    // SYSTEM:
    FLUSH,
    EMPTY
  };

  typedef pair<TAG, string> token;
  typedef deque<token> tokenqueue;

  struct token_queue
  {
    tokenqueue queue;
    word nodes_count;

    virtual void Build(const string &);
    token_queue &operator=(const tokenqueue &tq)
    {
      queue = tq;
      nodes_count = tq.size();
      return *this;
    }

    operator tokenqueue() const
    {
      return queue;
    }
  };
}