#pragma once
#include "../../stdafx.h"

#include <functional>
#include <list>

#include "calculator.h"
#include "../token_queue.h"

namespace calculator
{
  class node;
  class tree : algebra::token_queue
  {
    calculator::get_callback GetVariable;

    algebra::tokenqueue reverse_polish;
    void BuildReversePolish();
  public:
    void Build(const string &) override;
    double Calculate(calculator::get_callback);
  };
}