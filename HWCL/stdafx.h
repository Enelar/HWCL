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
