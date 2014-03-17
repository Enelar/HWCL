#include "string_utils.h"

template<>
string convert(const initializer_list<string> &a)
{
  string ret;

  for (auto obj : a)
    ret += obj;

  return ret;
}

template<>
string convert(const deque<string> &a)
{
  string ret;

  for (auto obj : a)
    ret += obj;

  return ret;
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
    string ret = source;
    ret.insert(0, " ");
    ret[0] = ch;
    return ret;
  }
}

#include <deque>

std::string parser::Trim(const std::string &str, const std::string &whitespace)
{ // http://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
  const auto strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::string::npos)
    return ""; // no content

  const auto strEnd = str.find_last_not_of(whitespace);
  const auto strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}


vector<string> parser::Split(const std::string &source, const char delimeter, const bool forget_empty, const bool remain_delimeter)
{
  string t;
  t += delimeter;
  return Split(source, t, forget_empty, remain_delimeter);
}

std::vector<std::string> parser::Split(const std::string &str, const std::string &delimeter, const bool forget_empty, const bool remain_delimeter)
{
  throw_assert(delimeter.length() > 0);
  char del = delimeter[0];
  const word delimeter_length = delimeter.length();

  deque<string> ret;

  auto Hook = [&](const string &str)
  {
    auto EmptyHook = [forget_empty, &ret](const string &str)
    {
      if (forget_empty && !str.length())
        return;
      ret.push_back(str);
    };

    if (remain_delimeter)
    {
      EmptyHook(str);
      return;
    }

    if (str.substr(0, delimeter_length) == delimeter)
      EmptyHook(str.substr(delimeter_length));
    else
      EmptyHook(str);
  };

  word i = 0, pos;
  while (i < str.length())
  {
    pos = str.find(delimeter, i + 1);
    if (pos == str.npos)
      break;

    Hook(str.substr(i, pos - i));

    i = pos;
  }

  Hook(str.substr(i));
  return{ ret.begin(), ret.end() };
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
