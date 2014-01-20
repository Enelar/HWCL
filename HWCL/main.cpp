#include "parser\parser.h"

void main()
{
  std::string source = "SET A=0";

  parser::parser p(source);
  auto prog = p.Translate();
}