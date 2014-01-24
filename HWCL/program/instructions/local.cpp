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
  vector<string> split;

  auto Set = [&]() -> std::string
  {
    split = parser::Split(name, '=', true);
    if (split.size() == 1)
      return "undefined";
    if (split.size() == 2)
      return split[1];
    throw syntax_error();
  };

  init_value = Set();

  if (tokens.size() == 2)
  {
    c.AddLocal(split[0]);
    return;
  }

  throw_assert(tokens.size() == 4);

  if (tokens[2] == "=")
  {
    c.AddLocal(split[0]);
    init_value = tokens[3];
    return;
  }
  if (ax::StrMasqEq(tokens[2].c_str(), "at") != 2)
    throw syntax_error();

  auto variable = tokens[3];
  c.AddLocal(name, variable);
}

void local::Execute(vm::context &)
{
}