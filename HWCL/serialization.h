#include "stdafx.h"

template<typename T>
struct abstract_serializer
{
};

template<typename T, typename Enable = void>
struct serializer;

template<typename T>
struct serializer<T, typename enable_if<is_trivially_copyable<T>::value, T>::type>
  : abstract_serializer<T>
{
  deque<ub> Se(const T &orig)
  {
    deque<ub> ret;
    ub *begin = &orig;
    copy_n(begin, sizeof(T), ret.begin());
    return ret;
  }

  T De(const deque<ub> &orig)
  {
    vector<ub> align(orig.begin(), orig.end());
    T ret;
    memcpy(&ret, &align[0], sizeof(T));
    return ret;
  }
};

template<>
struct serializer<string>
{
  deque<ub> Se(const string &str)
  {
    return{ str.begin(), str.end() };
  }

  string De(const deque<ub> &orig)
  {
    return{ orig.begin(), orig.end() };
  }
};
