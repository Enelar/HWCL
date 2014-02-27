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

  struct raw_pointer : object
  {
  protected:
    VAR_TYPE type;
  public:
    VAR_TYPE Type() const
    {
      return type;
    }
  };

  struct context;
  template<typename T>
  struct pointer : raw_pointer
  {
  public:
  private:
    string context, addr;
    word offset;

    mutable vm::context *origin = nullptr;

    pointer(const pointer &) = default;
  public:
    pointer(string code);

    void Origin(vm::context *const) const;
    pointer operator +(const word offset) const;
    T &operator*() const;
    pointer &Set(const T &);

    string Context() const;

    pointer SwitchContext(const string &new_context = "this") const;
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

#define HWCL_POINTER_DEFINED
#include "../context.h"
#include "pointer.hpp"