#include "parser\parser.h"
#include "vm\vm.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "program\instructions\end.h"

struct base
{
  int d;
};

struct a : base
{
  int b;
  virtual void c() {}
};

void main()
{
  int a::* test = &a::b;
  int a::* test2 = &a::d;

  a *a = new ::a;
  base *t = a;


  std::string source = []()->std::string
  {
    std::ifstream f;
    f.open("AIR.CL");

    throw_assert(f.is_open());
    std::stringstream ss;
    std::string buf;

    while (getline(f, buf))
      ss << buf << std::endl;
    return ss.str();
  }();

  parser::parser p(source);
  auto prog = p.Translate();

  vm::virtual_machine computer;
  auto proc = computer.Execute(prog);

  while (!computer.Idle())
    computer.Cycle();
}