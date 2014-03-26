#pragma once

#include "constructor.h"
#include <tuple>
#include <deque>

template<class Parent, class Tuple, int level = -1>
struct fabric
{
  typedef typename tuple_element<level - 1, Tuple>::type selected_type;
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
    return GenFunctor<selected_type, _Args...>();
  }

  template<typename selected_type, typename... _Args>
  static function<Parent *(_Args &&...)> GenFunctor()
  {
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

  template<int id, typename Ret, typename... _Args>
  static deque<function<Ret(_Args...)>> GetMethodFunctors()
  {
    auto ret = fabric<Parent, Tuple, level - 1>::GetMethodFunctors<id, Ret, _Args...>();
    ret.push_back(method_extracter<id>::GetMethodFunctor<selected_type, Ret, _Args...>());
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

  template<int id, typename Ret, typename... _Args>
  static deque<function<Ret(_Args...)>> GetMethodFunctors()
  {
    return fabric<Parent, Tuple, size>::GetMethodFunctors<id, Ret, _Args...>();
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

  template<int id, typename Ret, typename... _Args>
  static deque<function<Ret(_Args...)>> GetMethodFunctors()
  {
    return{};
  }
};

template<int method_id>
struct method_extracter
{
  template<class selected_type, typename Ret, typename... _Args>
  static function<Ret(_Args...)> GetMethodFunctor()
#ifndef _SPECIALIZE
    {
      implementation_required("You should specializate fabric<" TOSTRING(decltype(selected_type))
        ">::method_extracter<" TOSTRING(method_id) ">"
        );
    }
#else
      ;
#endif
};
