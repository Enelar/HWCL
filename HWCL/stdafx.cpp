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