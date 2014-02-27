#pragma once

#include "context.h"

namespace vm
{
  template<>
  void context::AddLocal(const string &name, const pointer<double> &p);
  template<>
  void context::AddLocal(const string &name, const pointer<bool> &p);
  template<>
  void context::AddLocal(const string &name, const pointer<string> &p);
};