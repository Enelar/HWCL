#include "parser.h"
#include "../translator/translator.h"
#include <sstream>

parser::parser::parser(const std::string &_source)
{
  auto source = Split(_source);

  for (auto line : source)
  {
    try
    {
      auto instruction = translator::Translate(line);
      p.code.push_back(instruction);
    }
    catch (translator::unrecognized_instruction)
    {
      throw;
    }
  }
}

program::cached_program parser::parser::Translate() const
{
  if (!compiled)
    compiled.swap(
      std::make_unique<program::cached_program>(p));
  return *compiled;
}

parser::parser::~parser()
{

}

std::vector<std::string> parser::parser::Split(const std::string &source)
{
  std::stringstream ss;
  ss << source;

  std::vector<std::string> ret;

  ret.push_back("");

  auto GetLine = [&ss]() -> std::string
  {
    const word buf_len = 1000;
    char buf[buf_len];
    ss.getline(buf, buf_len, '\n');
    return buf;
  };

  do
  {
    std::string s = GetLine();
    if (s[0] != '&')
    {
      ret.push_back(s);
      continue;
    }
    word i = ret.size() - 1;
    ret[i] = ret[i] + s.substr(1);
  } while (!ss.eof());

  return ret;
}
