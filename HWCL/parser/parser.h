#pragma once
#include "../stdafx.h"

#include "../program/cached_program.h"
#include <memory>

namespace parser
{
  class parser : object
  {
    program::program p;
    std::weak_ptr<program::cached_program> compiled;
  public:
    parser(const std::string &source);

    program::cached_program Copy() const;

    ~parser();
  };
}