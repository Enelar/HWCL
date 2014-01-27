#pragma once
#include "../stdafx.h"

#include <functional>
#include <list>

namespace calculator
{
  class node;
  class tree
  {
    function<double(string)> GetVariable;

    node *root;
  public:
    void Build(string);
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