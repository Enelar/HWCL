#include "cached_program.h"

using namespace program;

cached_program::cached_program(const ::program::program &p)
: original(std::make_shared<::program::program>(p))
{
  
}