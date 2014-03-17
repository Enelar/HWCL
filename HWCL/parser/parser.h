#pragma once
#include "../stdafx.h"

#include "../program/cached_program.h"
#include <string>
#include <memory>

namespace parser
{
  class parser : object
  {
    std::vector<std::string> code;

    mutable std::unique_ptr<program::cached_program> compiled;
  public:
    parser(const std::string &source);

    program::cached_program Translate() const;

    ~parser();
  };

  std::vector<std::string> ContinueString(const std::vector<std::string> &, const char delimeter = '&');
}