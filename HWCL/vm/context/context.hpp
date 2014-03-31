#pragma once

#include "context.h"

namespace vm
{
  template<typename T>
  shared_ptr<pointer_interface<T>> context::GetPointer(const std::string &name) const
  {
    auto ret = GetRawPointer(name);

    throw_assert(CheckPointerType<T>(*ret));
    return static_pointer_cast<vm::pointer<T>>(ret);
  }

  template<typename T>
  void context::AddLocal(const string &name, const pointer<T> &p)
  {
    AddLocal(name, p.Share());
  }

  template<typename T>
  void context::AddLocal(const string &name, shared_ptr<pointer<T>> p)
  {
    AddPointer(name, static_pointer_cast<raw_pointer>(p));
  }
};