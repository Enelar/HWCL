#include "pointer.h"

using namespace vm;

template<>
bool vm::CheckPointerType<bool>(const pointer<bool> &p)
{
  return p.Type() == BOOLEAN;
}

template<>
bool vm::CheckPointerType<float>(const pointer<float> &p)
{
  return p.Type() == NUMBER;
}

template<>
bool vm::CheckPointerType<string>(const pointer<string> &p)
{
  return p.Type() == STRING;
}