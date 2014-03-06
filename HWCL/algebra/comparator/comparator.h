#pragma once
#include "../../stdafx.h"

#include <functional>

#include "../../vm/types/pointer.h"
#include "../calculator_interface.h"
#include "../token_queue.h"

namespace algebra 
{
  class node;
  class comparator : calculator_interface<vm::floating_point, function<shared_ptr<vm::raw_pointer>(string)>>
  {
  public:
    typedef ArgumentT get_callback;
    get_callback GetVariable;

    token_queue tq;
    bool CheckPart(const token_queue &);
    bool CheckPart(const list<token_queue> &);
  public:
    comparator(const string &);
    void Build();
    double Calculate(get_callback) override;
  };
}