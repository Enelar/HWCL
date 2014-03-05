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

template<class Tuple, int level = -1>
struct translation_route
{
  template<typename T>
  std::shared_ptr<program::instruction> Helper(const std::string &source)
  {
    return{};
  }

  std::shared_ptr<program::instruction> operator()(const std::string &source)
  {
    static_assert(level >= 0, "Wrong template resolution");
    const int tuple_size = std::tuple_size<Tuple>::value;

    typedef std::tuple_element<level - 1, Tuple>::type selected_type;

    auto ret = Translator<selected_type>(source);

    if (ret)
      return ret;

    translation_route<Tuple, level - 1> t;
    return t(source);
  }
};

template<class Tuple>
struct translation_route<Tuple, -1>
{
  std::shared_ptr<program::instruction> operator()(const std::string &source)
  {
    const int size = std::tuple_size<Tuple>::value;
    translation_route<Tuple, size> t;
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
};
#pragma endregion TranslationRoute

#include "../program/instructions.h"

std::shared_ptr<program::instruction> translator::Translate(const std::string &source)
{
  using namespace program::instructions;
  typedef std::tuple
  <
    label, // should be first, in case it contains other command
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
    nop //should be last
  > supported_instructions_list;

  translation_route<supported_instructions_list> t;
  return t(source);
}