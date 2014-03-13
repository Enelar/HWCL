#pragma once
#include "../../stdafx.h"

#include <functional>
#include <list>

#include "calculator.h"
#include "../token_queue.h"

namespace calculator
{
  class node;
  class tree : public algebra::token_queue
  {
    calculator::get_callback GetVariable;
  public:
    algebra::tokenqueue reverse_polish;
  protected:
    void BuildReversePolish();
  public:
    void Build(const string &) override;
    double Calculate(calculator::get_callback);
  };
}