#include "parser.h"
#include "../translator/translator.h"
#include "../program/instructions/composite.h"
#include "../vm/process.h"
#include <sstream>

parser::parser::parser(const std::string &_source)
{
  code = ContinueString(Split(_source));
}

program::cached_program parser::parser::Translate() const
{
  if (!compiled)
  {
    program::program p;
    for (auto line : code)
    {
      if (!line.length())
        continue;

      try
      {
        auto instruction = translator::Translate(line);
        p.code.push_back(instruction);
      }
      catch (program::instructions::composite &c)
      {
        for (auto instruction : c.childs)
          p.code.push_back(instruction);
      }
      catch (translator::unrecognized_instruction)
      {
        throw;
      }
    }

    compiled.swap(
      std::make_unique<program::cached_program>(p));
  }

  return *compiled;
}

parser::parser::~parser()
{

}

std::vector<std::string> parser::ContinueString(const std::vector<std::string> &source, const char delimeter)
{
  std::vector<std::string> ret;

  auto i = source.begin(), e = source.end();

  ret.push_back(*i++);
  while (i != e)
  {
    auto &src = *i++;
    if (src[0] == delimeter)
      ret.back() = convert<string, initializer_list<string>>({ ret.back(), src.substr(1) });
    else
      ret.push_back(src);
  }
  return ret;
}