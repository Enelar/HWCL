#include "cached_program.h"

using namespace program;

cached_program::cached_program(const ::program::program &p)
: original(std::make_shared<::program::program>(p))
{
  
}

const decltype(declval<::program::program>().Code()) &cached_program::Code() const
{
  return original->Code();
}

const ::program::program *cached_program::operator->() const
{
  return original.operator->();
}