#include "parser.h"

parser::parser::parser(const std::string &source)
{

}

program::cached_program parser::parser::Translate() const
{
  if (!compiled)
    compiled.swap(
      std::make_unique<program::cached_program>(p));
  return *compiled;
}

parser::parser::~parser()
{

}