#include "external.h"
#include "../../parser/parser.h"
#include "../../vm/process.h"

using namespace program::instructions;

external::external(const string &source)
: instruction(source, "external")
{

}

bool external::Signature(const string &source)
{
  return parser::CompareCommand(source, "EXTERNAL");
}

namespace
{
  string RemoveCommas(string a)
  {
    string ret;
    auto i = a.begin(), e = a.end();

    while (i != e)
    {
      if (*i != ',')
        ret += *i;
      i++;
    }
    return ret;
  }
  string AddSpaceAfterComma(const string &str)
  {
    string ret;
    for (auto ch : str)
    {
      ret += ch;
      if (ch == ',')
        ret += ' ';
    }
    return ret;
  }
}

void external::Bind(vm::context &c)
{
  auto name = parser::Split(AddSpaceAfterComma(Source()), ' ', true);
  throw_assert(name.size() > 1);

  word i = 1;
  while (i < name.size())
  {
    auto t = RemoveCommas(name[i]);
    try
    {
      c.External(t);
    }
    catch (vm::runtime_error)
    {
      throw external_instruction{ t };
    }
    i++;
  }
}

void external::Execute(vm::context &)
{

}