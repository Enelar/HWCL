#include "labels.h"

using namespace vm::context_utils;

void labels::Add(const std::string &name, word eip)
{
  auto find = data.find(name);

  throw_assert(find == data.end());
  data.insert({ name, eip });
}

word labels::Find(const std::string &name) const
{
  auto find = data.find(name);

  throw_assert(find != data.end());
  return find->second;
}

decltype(labels::data) *labels::operator->()
{
  return &data;
}

const decltype(labels::data) *labels::operator->() const
{
  return &data;
}
