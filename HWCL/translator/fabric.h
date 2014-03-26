#pragma once

#include "constructor.h"
#include <tuple>
#include <deque>

template<class Parent, class Tuple, int level = -1>
struct fabric
{
  template<typename... _Args>
  static Parent *Make(int id, _Args&&...args)
  {
    if (level != id + 1)
      return fabric<Parent, Tuple, level - 1>::Make(id, forward<_Args>(args)...);

    return ThisMaker(forward<_Args>(args)...);
  }

  template<typename... _Args>
  static Parent *ThisMaker(_Args &&...args)
  {
    auto f = FunctorThisMaker<_Args...>();
    return f(forward<_Args>(args)...);
  }

  template<typename... _Args>
  static function<Parent *(_Args &&...)> FunctorThisMaker()
  {
    typedef typename tuple_element<level - 1, Tuple>::type selected_type;
    auto ret = constructor<selected_type, Parent>::GetConstructMethod<_Args...>();
    return ret;
  }

  template<typename... _Args>
  static deque<function<Parent *(_Args &&...)>> GetFunctors()
  {
    auto ret = fabric<Parent, Tuple, level - 1>::GetFunctors<_Args...>();
    ret.push_back(FunctorThisMaker<_Args...>());
    return ret;
  }
};

template<class Parent, class Tuple>
struct fabric<Parent, Tuple, -1>
{
  static const int size = tuple_size<Tuple>::value;

  template<typename... _Args>
  static Parent *Make(int id, _Args&&...args)
  {
    return fabric<Parent, Tuple, size>::Make<_Args...>(id, forward<_Args>(args)...);
  }

  template<typename... _Args>
  static deque<function<Parent *(_Args &&...)>> GetFunctors()
  {
    return fabric<Parent, Tuple, size>::GetFunctors<_Args...>();
  }
};

template<class Parent, class Tuple>
struct fabric<Parent, Tuple, 0>
{
  template<typename... _Args>
  static Parent *Make(int id, _Args&&...args)
  {
    throw "OUT OF FABRIC RANGE";
  }

  template<typename... _Args>
  static deque<function<Parent *(_Args &&...)>> GetFunctors()
  {
    return{};
  }
};