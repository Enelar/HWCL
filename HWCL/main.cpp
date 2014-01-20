#include "parser\parser.h"
#include "vm\vm.h"

void main()
{
  std::string source = "SET A=0";

  parser::parser p(source);
  auto prog = p.Translate();

  vm::virtual_machine computer;
  auto proc = computer.Execute(prog);

  while (!computer.Idle())
    computer.Cycle();
}