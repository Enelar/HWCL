#pragma once

#include "../stdafx.h"

template<>
string convert(const initializer_list<string> &a);
template<>
string convert(const deque<string> &a);
template<>
double convert(const string &a);
template<>
string convert(const double &a);

namespace parser
{
  std::vector<std::string> Split(const std::string &, const char delimeter = '\n', const bool forget_empty = false, const bool remain_delimeter = false);
  std::vector<std::string> Split(const std::string &, const std::string &delimeter, const bool forget_empty = false, const bool remain_delimeter = false);
  bool CompareCommand(const std::string &line, const std::string &mask);
};
