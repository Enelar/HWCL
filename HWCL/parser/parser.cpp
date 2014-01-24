#include "parser.h"
#include "../translator/translator.h"
#include "../program/instructions/composite.h"
#include "../vm/process.h"
#include <sstream>

parser::parser::parser(const std::string &_source)
{
  auto source = ContinueString(Split(_source));

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

namespace
{
  string AddBefore(char ch, string source)
  {
    auto ret = convert<string, vector<string>>({ " ", source });
    ret[0] = ch;
    return ret;
  }
}

std::vector<std::string> parser::ContinueString(const std::vector<std::string> &source, char delimeter)
{
  std::vector<std::string> ret;

  auto i = source.begin(), e = source.end();

  ret.push_back(*i++);
  while (i != e)
  {
    auto &src = *i++;
    if (src[0] == delimeter)
      ret.back() = convert<string, vector<string>>({ ret.back(), src.substr(1) });
    else
      ret.push_back(src);
  }
  return ret;
}

std::vector<std::string> parser::Split(const std::string &source, char delimeter, bool forget_empty, bool remain_delimeter)
{
  std::stringstream ss;
  ss << source;

  std::list<std::string> ret;

  auto GetLine = [&ss, delimeter]() -> std::string
  {
    const word buf_len = 1000;
    char buf[buf_len];
    ss.getline(buf, buf_len, delimeter);
    return buf;
  };

  do
    ret.push_back(GetLine());
  while (!ss.eof());

  vector<string> out;

  auto i = ret.begin(), e = ret.end();
  word pos = 0;

  do
  {
    if (remain_delimeter && i != ret.begin())
      *i = AddBefore(delimeter, *i);
    if (!forget_empty || *i != "")
      out.push_back(*i);
  }
  while (++pos, ++i != e);

  return vector<string>{out.begin(), out.end()};
}

std::vector<std::string> parser::Split(const std::string &str, const std::string delimeter, bool forget_empty, bool remain_delimeter)
{
  throw_assert(delimeter.length() > 0);
  char del = delimeter[0];
  const word delimeter_length = delimeter.length();
  if (delimeter_length == 1)
    return Split(str, del, forget_empty, remain_delimeter);
  auto tokens = Split(str, del, false, true);
  list<string> operational{ tokens.begin() + 1, tokens.end() }, ret;

  if (!forget_empty || tokens[0] != "")
    ret.push_back(tokens[0]);

  auto i = operational.begin(), e = operational.end(); 

  if (i == e)
    return std::vector<std::string>{ ret.begin(), ret.end() };

  while (true)
  {
    auto next = i;
    if (++next == e)
      break;

    *i = i->substr(0, i->length() - 1);
    *next = AddBefore(del, *next);
    ++i;
  }

  i = operational.begin();

  while (i != e)
  {
    if (delimeter_length != ax::StrMasqEq(i->c_str(), delimeter.c_str()))
    {
      if (ret.size())
        ret.back() = convert<string, vector<string>>({ ret.back(), *i });
      else if (i->length() || !forget_empty)
        ret.push_back(*i);
    }
    else if (remain_delimeter)
      ret.push_back(*i);
    else
      ret.push_back(i->substr(delimeter_length));
    i++;
  }

  return vector<string>{ ret.begin(), ret.end() };
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
