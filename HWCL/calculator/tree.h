#pragma once
#include "../stdafx.h"

#include <functional>
#include <list>

#include "calculator.h"

namespace calculator
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
    FLUSH,
    EMPTY
  };

  typedef pair<TAG, string> token;
  typedef list<token> tokenqueue;

  class node;
  class tree
  {
    calculator::get_callback GetVariable;

    tokenqueue queue;
    node *root;
    word nodes_count;
  public:
    void Build(string);
    double Calculate(node *, calculator::get_callback);
    double Calculate(calculator::get_callback);
  };
}

#include "node.h"