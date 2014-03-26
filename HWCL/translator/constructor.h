#pragma once

template<class ConstructingObjectT>
struct partial_constructor
{
  template<typename Parent, typename... _Args>
  static Parent *construct(_Args &&...arg)
  {
    return new ConstructingObjectT(forward<_Args>(arg)...);
  }

  template<typename... _Args>
  static function<ConstructingObjectT *(_Args&&...)> GetConstructMethod()
  {
    auto F = [](_Args&&... arg)
    {
      return construct(forward<_Args>(arg)...);
    };
    return F;
  }

  template<typename Parent, typename... _Args>
  static function<Parent *(_Args&&...)> ParentConstruct()
  {
    return GetConstructMethod<_Args...>();
  }
};

template<class ConstructingObjectT, class Parent = nullptr_t>
struct constructor
{
  template<typename... _Args>
  static Parent *construct(_Args &&...arg)
  {
    return 
      partial_constructor<ConstructingObjectT>
      ::construct<Parent, _Args...>(forward<_Args>(arg)...);
  }

  template<typename... _Args>
  static function<Parent *(_Args&&...)> GetConstructMethod()
  {
    return
      partial_constructor<ConstructingObjectT>
      ::ParentConstruct<Parent, _Args...>();
  }

  template<typename... _Args>
  static function<Parent *(_Args&&...)> GetConstructMethod()
  {
    return
      GetConstructMethod<_Args...>();
  }
};

template<class ConstructingObjectT>
struct constructor<ConstructingObjectT, nullptr_t>
: public constructor<ConstructingObjectT, ConstructingObjectT>
{
};