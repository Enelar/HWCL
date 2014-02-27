#pragma once
#include "../../stdafx.h"

namespace vm
{
  enum VAR_TYPE
  {
    NUMBER,
    BOOLEAN,
    DATE,
    STRING
  };

  struct context;
  template<typename T>
  struct pointer
  {
  public:
  private:
    string context, addr;
    VAR_TYPE type;
    word offset;

    mutable vm::context *origin = nullptr;
  public:
    pointer(string code);

    void Origin(vm::context *const) const;
    pointer operator +(const word offset) const;
    T &operator*() const;
    pointer &Set(const T &);

    VAR_TYPE Type() const;

  };

  template<typename T>
  bool CheckPointerType(const pointer<T> &)
  {
    IMPLEMENTATION_REQUIRED
  }

  template<typename A, typename B>
  A pointer_convert(const B &b)
  {
    return ax::convert<A, B>(b);
  }
}

#include "../context.h"
#include "pointer.hpp"