#pragma once

#include "context.h"

namespace vm
{
  template<typename T>
  shared_ptr<pointer<T>> context::GetPointer(const std::string &name) const
  {
    auto pointer = pointers.find(name)->second;
    throw_assert(CheckPointerType<T>(*pointer));
    return static_pointer_cast<vm::pointer<T>>(pointer);
  }

  template<typename T>
  void context::AddLocal(const string &name, const pointer<T> &p)
  {
    AddLocal(name, p.Share());
  }

  template<typename T>
  void context::AddLocal(const string &name, shared_ptr<pointer<T>> p)
  {
    AddPointer(name, static_pointer_cast<raw_pointer>(p));  }
};