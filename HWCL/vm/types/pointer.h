#pragma once
#include "../../stdafx.h"
#include "pointer_var_type.h"

namespace vm
{
  struct context;
  struct raw_pointer : object
  {
  protected:
    VAR_TYPE type;
    mutable vm::context *origin = nullptr;
  public:
    VAR_TYPE Type() const
    {
      return type;
    }
    void Origin(vm::context *const _origin) const
    {
      origin = _origin;
    }
  };

  template<typename T>
  struct pointer : raw_pointer
  {
  public:
  private:
    string context, addr;
    word offset;

  public:
    pointer(string code);
    pointer(const pointer &) = default;

    pointer operator +(const word offset) const;
    T &operator*() const;
    pointer &Set(const T &);

    string Context() const;

    pointer SwitchContext(const string &new_context = "this") const;

    shared_ptr<pointer> Share() const;
  };

  template<typename T>
  bool CheckPointerType(const raw_pointer &)
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