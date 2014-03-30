#pragma once

template<typename Type, typename Tuple, int level = -30>
struct get_type_pos
{
  typedef typename tuple_element<level, Tuple>::type selected_type;
  static constexpr bool same = is_same<selected_type, Type>::value;

  static int Get()
  {
    return GetA<int>();
  }

  template<typename T>
  static typename enable_if<!same, T>::type GetA()
  {
    return get_type_pos<Type, Tuple, level - 1>::Get();
  }

  template<typename T>
  static typename enable_if<same, T>::type GetA()
  {
    return level;
  }

  static int FaultFree()
  {
    return FaultFreeA<int>();
  }

  template<typename T>
  static typename enable_if<!same, T>::type FaultFreeA()
  {
    return get_type_pos<Type, Tuple, level - 1>::FaultFree();
  }

  template<typename T>
  static typename enable_if<same, T>::type FaultFreeA()
  {
    return level;
  }
};


template<typename Type, typename Tuple>
struct get_type_pos<Type, Tuple, -1>
{
  static int Get()
  {
    static_assert(false, "Type not found");
  }
  static int FaultFree()
  {
    return -1;
  }
};

template<typename Type, typename Tuple>
struct get_type_pos<Type, Tuple, -30>
{
  static const int size = tuple_size<Tuple>::value;
  static int Get()
  {
    return get_type_pos<Type, Tuple, size - 1>::Get();
  }
  static int FaultFree()
  {
    return get_type_pos<Type, Tuple, size - 1>::FaultFree();
  }
};