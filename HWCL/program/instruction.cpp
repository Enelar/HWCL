#include "instruction.h"

using namespace program;

instruction::instruction(const std::string &_source, const std::string &_debug_name)
: source(_source)
#ifdef _DEBUG_
, DEBUG_TYPE(_debug_name)
#endif
{
#ifdef _DEBUG_
  while (DEBUG_TYPE.length() < 20)
    DEBUG_TYPE += '_';
#endif
}