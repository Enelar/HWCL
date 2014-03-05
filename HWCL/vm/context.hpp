#pragma once

#include "context.h"

namespace vm
{
  template<typename T>
  shared_ptr<pointer_interface<T>> context::GetPointer(const std::string &name) const
  {
    auto pointer = pointers.find(name);

    if (pointer == pointers.end())
    {
      auto parts = parser::Split(name, '.');
      throw_assert(parts.size() == 2);
      auto external = External(parts[0]);
      return external->GetPointer<T>(parts[1]);
    }

    auto ret = pointer->second;

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