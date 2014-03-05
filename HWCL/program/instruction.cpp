#include "instruction.h"
#include "../parser/parser.h"

using namespace program;

instruction::instruction(const std::string &_source, const std::string &_debug_name)
: source(_source), without_comment(_source)
#ifdef _DEBUG_
, DEBUG_TYPE(_debug_name)
#endif
{
#ifdef _DEBUG_
  while (DEBUG_TYPE.length() < 20)
    DEBUG_TYPE += '_';
#endif
  auto tokens = parser::Split(source, "--", true);
  if (tokens.size() > 1)
    without_comment = tokens[0];
}

const decltype(instruction::source) &instruction::Source() const
{
  return without_comment;
}

const decltype(instruction::source) &instruction::OriginalSource() const
{
  return source;
}

void instruction::Bind(vm::context &)
{

}