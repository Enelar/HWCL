#include "translator.h"

using namespace translator;

template<typename T>
auto Translator(const std::string &source) -> std::shared_ptr<program::instruction>
{
  if (!T::Signature(source))
    return{};

  auto translated = make_unique<T>(source);//MakeUnique<T>(source);
  std::shared_ptr<program::instruction> shared(translated.release());

  return shared;
}

#include "fabric.h"
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

  typedef fabric<program::instruction, supported_instructions_list> Fabric;
}

enum METHODS
{
  TRANSLATE_FROM_SOURCE,
  TRANSLATE_FROM_SERIALIZATION
};

template<>
template<class selected_type, typename Ret, typename... _Args>
function<Ret(_Args...)>
  method_extracter<TRANSLATE_FROM_SOURCE>
  ::GetMethodFunctor()
{
  return[](_Args &&... args) -> Ret
  {
    return Translator<selected_type>(forward<_Args>(args)...);
  };
}

template<>
template<class selected_type, typename Ret, typename... _Args>
function<Ret(_Args...)>
  method_extracter<TRANSLATE_FROM_SERIALIZATION>
  ::GetMethodFunctor()
{
  return[](_Args &&... args) -> Ret
  {
    return make_shared<selected_type>(forward<_Args>(args)...);
  };
}



std::shared_ptr<program::instruction> translator::Translate(const std::string &source)
{
  static auto methods = 
    Fabric::GetMethodFunctors
    <
      TRANSLATE_FROM_SOURCE, 
      std::shared_ptr<program::instruction>,
      decltype(source)
    >();

  for (auto method : methods)
  {
    auto ret = method(source);
    if (ret)
      return ret;
  }

  dead_space();
}

std::shared_ptr<program::instruction> Translate(const ub id, const deque<ub> &code)
{
  static auto methods =
    Fabric::GetMethodFunctors
    <
      TRANSLATE_FROM_SERIALIZATION,
      std::shared_ptr<program::instruction>,
      decltype(code)
    >();

  throw_assert(id >= 0);
  throw_sassert(id < methods.size(), "Instruction unsupported");

  auto method = methods[id];

  auto ret = method(code);

  throw_sassert(ret, "Object wont be constructed");
  return ret;

  dead_space();
}

word translator::InstructionCode(std::shared_ptr<program::instruction> &ins)
{
  return ins->code;
}