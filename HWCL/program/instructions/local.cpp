#include "local.h"
#include "../../parser/parser.h"

using namespace program::instructions;

local::local(const string &source)
: instruction(source, "local")
{

}

bool local::Signature(const string &source)
{
  return parser::CompareCommand(source, "LOCAL");
}

void local::Bind(vm::context &c)
{
  auto tokens = parser::Split(Source(), ' ', true);
  throw_assert(parser::CompareCommand(tokens[0], "LOCAL"));

  if (tokens.size() < 2)
    throw syntax_error();

  auto name = tokens[1];

  auto Set = [&]() -> std::string
  {
    auto set = parser::Split(name, '=', true);
    if (set.size() == 1)
      return "undefined";
    if (set.size() == 2)
      return set[1];
    throw syntax_error();
  };

  init_value = Set();

  if (tokens.size() == 2)
  {
    c.AddLocal(name);
    return;
  }

  throw_assert(tokens.size() == 4);

  if (tokens[2] == "=")
    return;
  if (ax::StrMasqEq(tokens[2].c_str(), "at") != 2)
    throw syntax_error();
  auto addr = tokens[3];

  if (addr[0] != 'N' || addr[1] != 'N')
    todo("Other types");
  throw_assert(addr[2] == '(' && addr[5] == ')');
  word offset = (addr[3] - '0') * 10 + (addr[4] - '0') - 1;
  
  c.AddLocal(name, offset);
}

void local::Execute(vm::context &)
{
}