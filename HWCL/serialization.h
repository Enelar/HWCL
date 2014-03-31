#include "stdafx.h"

template<typename T, typename Enable = void>
struct serializer;

template<typename T>
struct serializer<T, typename enable_if<is_const<T>::value>::type>
  : serializer<typename remove_const<T>::type>
{

};

template<typename T>
struct serializer<T, typename enable_if<is_trivially_copyable<T>::value>::type>
{
  static deque<ub> Se(const T &orig)
  {
    deque<ub> ret;
    const ub *begin = (const ub *)&orig;
    copy_n(begin, sizeof(T), ret.begin());
    return ret;
  }

  static T De(const deque<ub> &orig)
  {
    vector<ub> align(orig.begin(), orig.end());
    T ret;
    memcpy(&ret, &align[0], sizeof(T));
    return ret;
  }

  static T DeR(deque<ub> &orig)
  {
    T ret = De(orig);
    orig.erase(orig.begin(), orig.begin() + sizeof(T));
    return ret;
  }
};

template<>
struct serializer<string>
{
  static deque<ub> Se(const string &str)
  {
    return{ str.begin(), str.end() };
  }

  static string De(const deque<ub> &orig)
  {
    return{ orig.begin(), orig.end() };
  }

  static string DeR(deque<ub> &orig)
  {
    string str = De(orig);
    orig.clear();
    return str;
  }
};

template<>
struct serializer<deque<ub>>
{
  deque<ub> res;

  deque<ub> Se(const deque<ub> &orig)
  {
    auto size = serializer<hword>::Se(orig.size());

    res.insert(res.end(), size.begin(), size.end());
    res.insert(res.end(), orig.begin(), orig.end());

    return res;
  }

  deque<ub> De(const deque<ub> &orig)
  {
    res.insert(res.end(), orig.begin(), orig.end());
    return De();
  }

  template<typename T = deque<ub>>
  T De()
  {
    return serializer<T>::DeR(res);
  }

  template<>
  deque<ub> De<deque<ub>>()
  {
    throw_assert(res.size() != 0);
    auto size = serializer<hword>::De(res);
    res.erase(res.begin(), res.begin() + sizeof(hword));
    deque<ub> ret{ res.begin(), res.begin() + size };
    res.erase(res.begin(), res.begin() + sizeof(size));
    return ret;
  }
};
