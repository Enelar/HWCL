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

composite::composite(const deque<ub> &)
: instruction("")
{

}


composite::composite(const string &str)
: instruction(str)
{
  auto new_str = [&str]()
  {
    word offset = 0;
    while (str[offset++] != '(')
      ;
    word back_offset = str.length();
    while (str[back_offset] != ')')
      back_offset--;

    return str.substr(offset, back_offset - offset);
  }();

  auto instructions = parser::Split(new_str, ';');

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
