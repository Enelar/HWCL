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

  throw_assert(init_value == "undefined");

  bool type_specialised = name.back() == ':';
  if (type_specialised)
    name.pop_back();

  word AT_pos = [&]()
  {
    word ret = 0;
    while (ax::StrMasqEq(tokens[ret].c_str(), "at") != 2)
    {
      ret++;
      if (ret == tokens.size())
        break;
    }
    return ret;
  }();

  if (AT_pos == tokens.size())
  { // wild variable: `SET A = 100`
    c.AddLocal(name); // numbers only
    return;
  }

  throw_assert(tokens.size() - 1 == AT_pos + 1);
  throw_assert(AT_pos >= 2);

  string element_type = "NUMBER";
  string additional;

  if (ax::StrMasqEq(tokens[2].c_str(), "ARRAY") != 5)
    element_type = tokens[2];
  if (AT_pos == 4)
    additional = tokens[3];
  else if (AT_pos == 5)
    additional == convert<string, initializer_list<string>>({ tokens[3], tokens[4] });

  string addr = tokens[AT_pos + 1];

  c.AddLocal(name, addr, additional);
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

local::local(const deque<ub> &orign)
: local(string{ orign.begin(), orign.end() })
{

}

deque<ub> local::Serialize()
{
  return{ Source().begin(), Source().end() };
}