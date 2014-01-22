#include "nop.h"
#include "../../parser/parser.h"

using namespace program::instructions;

nop::nop(const string &source)
: instruction(source)
{

}

bool nop::Signature(const string &source)
{
  auto i = source.begin(), e = source.end();

  while (i != e)
  {
    if (*i != ' ')
      break;
    i++;
  }

  if (i == e)
    return true;

  // comment check

  if (e - i < 2)
    return false;

  return (*i == '-' && *(i + 1) == '-');
}

void nop::Execute(vm::context &)
{

}