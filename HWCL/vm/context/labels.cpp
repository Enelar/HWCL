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

labels::labels(const deque<ub> &orig)
{
  serializer<deque<ub>> ret{ orig };
  auto count = ret.De<word>();

  for (word i = 0; i < count; i++)
  {
    typedef decltype(data.find("")) pair;
    auto str = serializer<decltype(declval<pair>()->first)>::De(ret.De());
    auto val = serializer<decltype(declval<pair>()->second)>::De(ret.De());
    data.insert({ str, val });
  }
}

deque<ub> labels::Serialize() const
{
  serializer<deque<ub>> ret;

  ret.Se(serializer<word>::Se(data.size()));

  for (auto el : data)
  {
    ret.Se(serializer<decltype(el.first)>::Se(el.first));
    ret.Se(serializer<decltype(el.second)>::Se(el.second));
  }

  return ret.res;
}
