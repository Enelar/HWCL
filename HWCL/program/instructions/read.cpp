#include "read.h"
#include "set.h"
#include "../../parser/parser.h"

using namespace program::instructions;

read::read(const string &source)
: instruction(source, "read")
{

}

bool read::Signature(const string &source)
{
  return parser::CompareCommand(source, "READ");
}

void read::Bind(vm::context &c)
{
  auto tokens = parser::Split(Source(), ' ', true);
  if (tokens.size() < 4)
    throw syntax_error();
  auto dest = tokens[1];
  auto source = tokens[3];

  auto actual_code = convert<string, initializer_list<string>>(
  {
    "SET ",
    dest,
    " = ",
    source
  });

  compiled = make_unique<set>(actual_code);
  compiled->Bind(c);
}

void read::Execute(vm::context &c)
{
  throw_assert(compiled);
  compiled->Execute(c);
}

read::read(const deque<ub> &orign)
: read(string{ orign.begin(), orign.end() })
{

}

deque<ub> read::Serialize()
{
  return{ Source().begin(), Source().end() };
}