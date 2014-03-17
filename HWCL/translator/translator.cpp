#include "translator.h"

using namespace translator;

template<typename T>
auto Translator(const std::string &source) -> std::shared_ptr<program::instruction>
{
  if (!T::Signature(source))
    return{};

  auto translated = std::make_unique<T>(source);
  std::shared_ptr<program::instruction> shared(translated.release());

  return shared;
}

#pragma region TranslationRoute
#include <tuple>

#include <deque>

template<class Tuple, int level = -1>
struct translation_route
{
  template<typename T>
  std::shared_ptr<program::instruction> Helper(const std::string &source) const
  {
    return{};
  }

  std::shared_ptr<program::instruction> operator()(const std::string &source) const
  {
    for (auto f : methods)
    {
      auto ret = f(source);
      if (ret)
        return ret;
    }

    throw unrecognized_instruction(source);
  }

  deque<function<std::shared_ptr<program::instruction>(const std::string &)>> methods;

  deque<function<std::shared_ptr<program::instruction>(const std::string &)>> GetMethods()
  {
    if (methods.size())
      return methods;
    static_assert(level >= 0, "Wrong template resolution");
    const int tuple_size = std::tuple_size<Tuple>::value;

    typedef std::tuple_element<level - 1, Tuple>::type selected_type;

    translation_route<Tuple, level - 1> t;
    decltype(GetMethods()) ret = t.GetMethods();
    ret.push_back(Translator<selected_type>);

    methods.swap(ret);
    return methods;
  }
};

template<class Tuple>
struct translation_route<Tuple, -1>
{
  static const int size = std::tuple_size<Tuple>::value;
  translation_route<Tuple, size> t;
  bool inited = false;

  std::shared_ptr<program::instruction> operator()(const std::string &source)
  {
    if (!inited)
    {
      t.GetMethods();
      inited = true;
    }
    return t(source);
  }
};


template<class Tuple>
struct translation_route<Tuple, 0>
{
  std::shared_ptr<program::instruction> operator()(const std::string &source)
  {
    throw unrecognized_instruction(source);
  }
  deque<function<std::shared_ptr<program::instruction>(const std::string &)>> GetMethods() const
  {
    return{};
  }
};
#pragma endregion TranslationRoute

#include "../program/instructions.h"

namespace
{
  using namespace program::instructions;
  typedef std::tuple
    <
    condition,
    program::instructions::end,
    external,
    jump,
    local,
    phase,
    read,
    send,
    sequence,
    set,
    step,

    composite,
    label,
    nop //should be last
    > supported_instructions_list;

  translation_route<supported_instructions_list> t;
}

std::shared_ptr<program::instruction> translator::Translate(const std::string &source)
{
  return t(source);
}