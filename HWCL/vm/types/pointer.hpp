#pragma once
#include "pointer.h"
#include "../../parser/parser.h"

namespace vm
{
  template<typename T>
  pointer<T>::pointer(string code)
  {
    auto parts = parser::Split(code, ".");
    if (parts.size() == 1)
    {
      parts.push_back(parts[0]);
      parts[0] = "this";
    }

    if (addr.find("NN") != string::npos)
      type = NUMBER;
    else if (addr.find("FL") != string::npos)
      type = BOOLEAN;
    else if (addr.find("STR") != string::npos)
      type = STRING;
    else
      throw_message("Other types");

    auto offset_str = parser::Split(parts[1], '(');
    throw_assert(parts.size() == 2);
    stringstream ss;
    ss << offset_str[0];
    ss >> offset;
  }

  template<typename T>
  void pointer<T>::Origin(vm::context *const _origin) const
  {
    origin = _origin;
  }

  template<typename T>
  pointer<T> pointer<T>::operator +(const word _offset) const
  {
    return{ context, addr, type, offset + _offset };
  }

  template<typename T>
  T &pointer<T>::operator*() const
  {
    throw_assert(origin);
    todo("Access addr");
  }

  template<typename T>
  pointer<T> &pointer<T>::Set(const T &val)
  {
    **this = val;
    return *this;
  }

  template<typename T>
  VAR_TYPE pointer<T>::Type() const
  {
    return type;
  }

  template<>
  bool CheckPointerType<bool>(const pointer<bool> &p)
  {
    return p.Type() == BOOLEAN;
  }

  template<>
  bool CheckPointerType<float>(const pointer<float> &p)
  {
    return p.Type() == NUMBER;
  }

  template<>
  bool CheckPointerType<string>(const pointer<string> &p)
  {
    return p.Type() == STRING;
  }

}

#include "../context.h"