#pragma once
#include "calculator_interface.h"

namespace algebra
{
  template<typename ret_type, typename req_type>
  calculator_interface<ret_type, req_type>::calculator_interface(const string &expression)
    : src_str(expression)
  {

  }

  template<typename ret_type, typename req_type>
  calculator_interface<ret_type, req_type>::~calculator_interface()
  {

  }
}