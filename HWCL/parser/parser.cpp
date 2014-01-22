#include "parser.h"
#include "../translator/translator.h"
#include "../program/instructions/composite.h"
#include <sstream>

parser::parser::parser(const std::string &_source)
{
  auto source = Split(_source);

  for (auto line : source)
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

std::vector<std::string> parser::Split(const std::string &source, char delimeter)
{
  std::stringstream ss;
  ss << source;

  std::vector<std::string> ret;

  ret.push_back("");

  auto GetLine = [&ss, delimeter]() -> std::string
  {
    const word buf_len = 1000;
    char buf[buf_len];
    ss.getline(buf, buf_len, delimeter);
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

bool parser::CompareCommand(const std::string &line, const std::string &mask)
{
  int i = 0;

  auto IsSpace = [](const char &ch)
  {
    switch (ch)
    {
    case ' ':
    case '\t':
    case '\r':
    case '\b':
    case '\n':
      return true;
    }
    return false;
  };

  while (IsSpace(line[i]))
    ++i;

  return ax::StrMasqEq(line.c_str() + i, mask.c_str()) == mask.length();
}
