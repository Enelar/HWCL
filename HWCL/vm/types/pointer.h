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
  private:
    string context, addr;
    VAR_TYPE type;
    word offset;

    mutable context *origin = nullptr;
  public:
    pointer(string code);

    void Origin(context *const) const;
    pointer operator +(const word offset) const;
    T &operator*() const;
    pointer &Set(const string &);
    pointer &Set(const T &);
  };

  template<typename A, typename B>
  A pointer_convert(const B &b)
  {
    return ax::convert<A, B>(b);
  }
}

#include "../context.h"