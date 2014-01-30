#pragma once
#include "../stdafx.h"

#include <functional>
#include <list>

#include "calculator.h"

namespace calculator
{
  class node;
  class tree
  {
    calculator::get_callback GetVariable;

    node *root;
    word nodes_count;
  public:
    void Build(string);
    double Calculate(node *, calculator::get_callback);
    double Calculate(calculator::get_callback);
  };

  enum TAG
  {
    UNDEFINED,
    NUMBER,
    VARIABLE,
    SYMBOL,
    FLUSH,
    EMPTY
  };

  typedef pair<TAG, string> token;
  typedef list<token> tokenqueue;
}

#include "node.h"