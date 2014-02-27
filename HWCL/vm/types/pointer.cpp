#include "pointer.h"

using namespace vm;

template<>
bool vm::CheckPointerType<bool>(const raw_pointer &p)
{
  return p.Type() == BOOLEAN;
}

template<>
bool vm::CheckPointerType<floating_point>(const raw_pointer &p)
{
  return p.Type() == NUMBER;
}

template<>
bool vm::CheckPointerType<string>(const raw_pointer &p)
{
  return p.Type() == STRING;
}