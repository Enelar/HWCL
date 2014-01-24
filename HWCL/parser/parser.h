#pragma once
#include "../stdafx.h"

#include "../program/cached_program.h"
#include <string>
#include <memory>

namespace parser
{
  class parser : object
  {
    program::program p;
    mutable std::unique_ptr<program::cached_program> compiled;
  public:
    parser(const std::string &source);

    program::cached_program Translate() const;

    ~parser();
  };


  std::vector<std::string> ContinueString(const std::vector<std::string> &, char delimeter = '&');
  std::vector<std::string> Split(const std::string &, char delimeter = '\n', bool forget_empty = false, bool remain_delimeter = false);
  std::vector<std::string> Split(const std::string &, const std::string delimeter, bool forget_empty = false, bool remain_delimeter = false);
  bool CompareCommand(const std::string &line, const std::string &mask);
}