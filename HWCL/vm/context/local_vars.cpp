#include "local_vars.h"

using namespace vm::context_utils;

template<typename T, int N>
struct serializer<array<T, N>, typename enable_if<is_trivially_copyable<T>::value>::type>
{
  static deque<ub> Se(const array<T, N> &orig)
  {
    deque<ub> ret;

    for (auto el : orig)
    {
      auto t = serializer<decltype(el)>::Se(el);
      ret.insert(ret.end(), t.begin(), t.end());
    }

    return ret;
  }

  static array<T, N> De(deque<ub> orig)
  {
    array<T, N> ret;
    for (word i = 0; i < N; i++)
    {
      ret[i] = serializer<T>::De(orig);
      orig.erase(orig.begin(), orig.end() + sizeof(T));
    }

    return ret;
  }
};


local_vars::local_vars(const deque<ub> &orig)
{
  serializer<deque<ub>> ret{ orig };
  auto serializedNN = ret.De();
  auto serializedFL = ret.De();
  auto serialized_localNN = ret.De();

  NN = serializer<decltype(NN)>::De(serializedNN);
  FL = serializer<decltype(FL)>::De(serializedFL);

  auto len = serializer<word>::DeR(serialized_localNN);
  for (word i = 0; i < len; i++)
    local_NN.push_back(serializer<double>::DeR(serialized_localNN));
}

deque<ub> local_vars::Serialize() const
{
  serializer<deque<ub>> ret;

  auto SerializeNN = [this]()
  {
    deque<ub> ret;

    for (auto el : NN)
    {
      auto t = serializer<decltype(el)>::Se(el);
      ret.insert(ret.end(), t.begin(), t.end());
    }

    return ret;
  };

  auto SerializeFL = [this]()
  {
    deque<ub> ret;

    for (auto el : FL)
    {
      auto t = serializer<decltype(el)>::Se(el);
      ret.insert(ret.end(), t.begin(), t.end());
    }

    return ret;
  };

  auto SerializeLocalNN = [this]()
  {
    deque<ub> ret = serializer<word>::Se(local_NN.size());

    for (auto el : local_NN)
    {
      auto t = serializer<decltype(el)>::Se(el);
      ret.insert(ret.end(), t.begin(), t.end());
    }

    return ret;
  };

  ret.Se(SerializeNN());
  ret.Se(SerializeFL());
  ret.Se(SerializeLocalNN());

  return ret;
}
