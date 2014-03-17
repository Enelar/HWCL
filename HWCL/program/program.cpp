#include "program.h"

const decltype(program::program::code) &program::program::Code() const
{
  return code;
}

::program::program::program(const string &filename)
{
  //todo(Restore program);
}

void program::program::Dump(const string &filename) const
{
  //todo(Dump program);
}