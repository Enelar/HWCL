#pragma once
#include "../../stdafx.h"

#include <functional>

#include "../../vm/types/pointer.h"
#include "../calculator_interface.h"
#include "../token_queue.h"
#include "../calculator/tree.h"


namespace algebra 
{
  class node;
  class comparator : calculator_interface<bool, function<shared_ptr<vm::raw_pointer>(string)>>
  {
  public:
    typedef ArgumentT get_callback;
    get_callback GetVariable;

    unique_ptr<calculator::tree> tq;
    bool CheckPart(const tokenqueue &);
    bool CheckPart(const list<tokenqueue> &);
  public:
    comparator(const string &);
    void Build();
    bool Calculate(get_callback) override;
  };
}