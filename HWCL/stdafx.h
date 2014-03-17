#pragma once

#include <ax\def.h>

using ax::object;
using ax::convert;

using namespace std;

#include <string>
#include <sstream>

#include <vector>
#include <deque>
#include <map>

#include <memory>

#include "parser\string_utils.h"

namespace vm
{
  typedef double floating_point;
};

bool KnownBoolNames(const string &name);
void DebugOutput(const initializer_list<string> &a);

