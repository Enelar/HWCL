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
  struct pointer_interface : raw_pointer
  {
    virtual T &operator*() const = 0;
    virtual pointer_interface &Set(const T &val)
    {
      **this = val;
      return *this;
    }
    virtual string Context() const = 0;
  };

  template<typename T>
  struct pointer : pointer_interface<T>
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
    pointer_interface &Set(const T &);

    string Context() const;

    pointer SwitchContext(const string &new_context = "this") const;

    shared_ptr<pointer> Share() const;
  };

  template<typename T>
  struct extern_pointer : pointer_interface<T>
  {
  private:
    T *ptr;
  public:
    extern_pointer(void *_ptr, VAR_TYPE _type)
      : ptr(reinterpret_cast<T *>(_ptr))
    {
      throw_assert(ptr);
      type = _type;
    }
    T &operator*() const
    {
      return *ptr;
    }
    string Context() const
    {
      return "this";
    }
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
#include "../context/context.h"
#include "pointer.hpp"