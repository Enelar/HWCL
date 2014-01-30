#include "stdafx.h"
#include <sstream>

template<>
string convert(const vector<string> &a)
{
  std::stringstream ss;

  for (auto obj : a)
    ss << obj;
  return ss.str();
}

template<>
double convert(const string &a)
{
  stringstream ss;
  ss << a;
  double ret;
  ss >> ret;
  return ret;
}

template<>
string convert(const double &a)
{
  stringstream ss;
  ss << a;
  return ss.str();
}

