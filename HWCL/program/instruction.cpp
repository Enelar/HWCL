#include "instruction.h"

using namespace program;

instruction::instruction(const std::string &_source, const std::string &_debug_name)
: source(_source)
#ifdef _DEBUG_
, debug_name(_debug_name)
#endif
{

}