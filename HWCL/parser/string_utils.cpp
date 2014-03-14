#include "string_utils.h"

template<>
string convert(const vector<string> &a)
{
  std::stringstream ss;

  for (auto obj : a)
    ss << obj;
  return ss.str();
}

template<>
double convert(const string &a)
{
  stringstream ss;
  ss << a;
  double ret;
  ss >> ret;
  return ret;
}

template<>
string convert(const double &a)
{
  stringstream ss;
  ss << a;
  return ss.str();
}

namespace
{
  string AddBefore(const char ch, const string &source)
  {
    auto ret = convert<string, vector<string>>({ " ", source });
    ret[0] = ch;
    return ret;
  }
}


std::vector<std::string> parser::Split(const std::string &source, const char delimeter, const bool forget_empty, const bool remain_delimeter)
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
  } while (++pos, ++i != e);

  return vector<string>{out.begin(), out.end()};
}

std::vector<std::string> parser::Split(const std::string &str, const std::string &delimeter, const bool forget_empty, const bool remain_delimeter)
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

    word comp = ax::StrMasqEq(delimeter.c_str(), i->c_str());
    if (comp == i->length())
    {
      *next = convert<string, vector<string>>({ *i, *next });
      i->clear();
    }

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
