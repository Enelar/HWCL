#include "program.h"

const decltype(program::program::code) &program::program::Code() const
{
  return code;
}