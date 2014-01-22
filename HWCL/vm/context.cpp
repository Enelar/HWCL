#include "context.h"

using namespace vm;

void context::Label(const std::string &name, word eip)
{
  auto find = labels.find(name);

  throw_assert(find == labels.end());
  labels.insert({ name, eip });
}

word context::Label(const std::string &name)
{
  auto find = labels.find(name);

  throw_assert(find != labels.end());
  return find->second;
}