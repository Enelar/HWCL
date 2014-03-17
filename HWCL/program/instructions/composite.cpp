#include "composite.h"
#include "../../parser/parser.h"
#include "../../translator/translator.h"

using namespace program::instructions;

composite::composite(initializer_list<std::shared_ptr<instruction>> orig)
: instruction("")
{
  auto i = orig.begin(), e = orig.end();

  while (i != e)
  {
    childs.push_back(*i);
    i++;
  }
}


composite::composite(const string &str)
: instruction(str)
{
  auto instructions = parser::Split(str, ';');

  composite ret({});
  for (auto command : instructions)
  {
    try
    {
      ret.childs.push_back(translator::Translate(command));
    }
    catch (composite &cp)
    {
      ret.childs.merge(cp.childs);
    }
  }

  throw ret;
}

bool composite::Signature(const string &source)
{
  int i = 0;
  while (source[i] == ' ')
    i++;
  return source[i] == '(';
}
