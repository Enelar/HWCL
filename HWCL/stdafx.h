#pragma once

#include <ax\def.h>

using ax::object;
using ax::convert;

using namespace std;

#include <string>
#include <sstream>

#include <vector>
#include <list>
#include <map>

#include <memory>

template<>
string convert(const vector<string> &a);
template<>
double convert(const string &a);
template<>
string convert(const double &a);

namespace parser
{
  std::vector<std::string> ContinueString(const std::vector<std::string> &, char delimeter = '&');
  std::vector<std::string> Split(const std::string &, char delimeter = '\n', bool forget_empty = false, bool remain_delimeter = false);
  std::vector<std::string> Split(const std::string &, const std::string delimeter, bool forget_empty = false, bool remain_delimeter = false);
  bool CompareCommand(const std::string &line, const std::string &mask);
};

