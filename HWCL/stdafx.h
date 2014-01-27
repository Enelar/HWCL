#pragma once

#include <ax\def.h>

using ax::object;
using ax::convert;

using namespace std;

#include <string>

#include <vector>
#include <list>
#include <map>

#include <memory>

template<>
string convert(const vector<string> &a);