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

  vector<string> split;

  auto Set = [&]() -> std::string
  {
    split = parser::Split(tokens[1], '=', true);
    if (split.size() == 1)
      return "undefined";
    if (split.size() == 2)
      return split[1];
    throw syntax_error();
  };

  init_value = Set();
  name = split[0];

  if (tokens.size() == 2)
  {
    c.AddLocal(name);
    return;
  }

  throw_assert(tokens.size() == 4);

  if (tokens[2] == "=")
  {
    c.AddLocal(name);
    init_value = tokens[3];
    return;
  }
  if (ax::StrMasqEq(tokens[2].c_str(), "at") != 2)
    throw syntax_error();

  auto variable = tokens[3];
  c.AddLocal(name, variable);
}

#include <sstream>

void local::Execute(vm::context &c)
{
  if (init_value == "undefined")
    return;
  auto &var = c.Local(name);
  stringstream ss;
  ss << init_value;
  ss >> var;
}