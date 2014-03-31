#pragma once
#include "pointer.h"

#include "../context/context.hpp"

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

    auto offset_str = parser::Split(parts[1], '(');
    throw_assert(parts.size() == 2);
    stringstream ss;
    ss << offset_str[1];
    ss >> offset;

    context = parts[0];
    addr = offset_str[0];

    if (addr.find("NN") != string::npos)
      type = NUMBER;
    else if (addr.find("FL") != string::npos)
      type = BOOLEAN;
    else if (addr.find("STR") != string::npos)
      type = STRING;
    else
      throw_message("Other types");
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
    if (Context() != "this")
    {
      auto external = origin->routes.External(Context());
      auto switched = SwitchContext();
      switched.Origin(external.get());
      return *switched;
    }

    void *ret;

    if (Type() == NUMBER)
      ret = origin->local.NN + offset;
    else if (Type() == BOOLEAN)
      ret = origin->local.FL + offset;
    else if (Type() == STRING)
      todo("String access");
    else
      todo("Other types");

    throw_assert(CheckPointerType<T>(*this));
    return *reinterpret_cast<T *>(ret);
  }

  template<typename T>
  pointer_interface<T> &pointer<T>::Set(const T &val)
  {
    **this = val;
    return *this;
  }

  template<typename T>
  string pointer<T>::Context() const
  {
    return context;
  }

  template<typename T>
  pointer<T> pointer<T>::SwitchContext(const string &new_context) const
  {
    pointer ret = *this;
    ret.context = new_context;
    return ret;
  }

  template<typename T>
  shared_ptr<pointer<T>> pointer<T>::Share() const
  {
    return make_shared<pointer<T>>(*this);
  }

  template<>
  bool CheckPointerType<bool>(const raw_pointer &p);
  template<>
  bool CheckPointerType<floating_point>(const raw_pointer &p);
  template<>
  bool CheckPointerType<string>(const raw_pointer &p);
  template<>
  bool CheckPointerType<int>(const raw_pointer &p);
}

#include "../context/context.h"