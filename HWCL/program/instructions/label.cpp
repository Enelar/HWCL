#include "label.h"
#include "../../parser/parser.h"

using namespace program::instructions;

#include "composite.h"
#include "../../translator/translator.h"
#include <sstream>

namespace
{
  int SearchDelimeter(const string &source)
  {
    auto i = source.begin(), e = source.end();

    enum
    {
      SPACE,
      LABEL_NAME
    } state = SPACE;

    auto IsAlph = [](const char &ch)
    {
      return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    };

    auto IsNum = [](const char &ch)
    {
      return ch >= '0' && ch <= '9';
    };

    while (i != e)
    {
      auto ch = *i;

      switch (state)
      {
      case SPACE:
        if (ch == ' ')
          break;
        if (!IsAlph(ch) && !IsNum(ch)) REFACTOR
          return -1;
        state = LABEL_NAME;
        break;
      case LABEL_NAME:
        if (IsAlph(ch) || IsNum(ch))
          break;
        if (ch != ':')
          return -1;
        return i - source.begin();
      }
      i++;
    };
    return -1;
  }

  void TryCompositeLabel(const string &source)
  {
    int delimeter = SearchDelimeter(source);

    if (delimeter == -1)
      return;

    std::string label, command;
    auto Splitter = [&label, &command, &source]()
    {
      std::stringstream ss;
      ss << source;

      char buf[1000];
      ss.getline(buf, 1000, ':');
      int offset = 0;

      while (buf[offset] == ' ')
        offset++;
      label = buf + offset;

      ss.getline(buf, 1000, ':');
      command = buf;
    };

    Splitter();

    composite ret
    {
      {
        std::make_shared<program::instructions::label>(label),
        translator::Translate(command)
      }
    };

    // we should give that information to program translator
    throw ret;
  }
}

label::label(const string &source)
: instruction(source, "label")
{
  TryCompositeLabel(source);
}

bool label::Signature(const string &source)
{
  return SearchDelimeter(source) > 0;
}

void label::Execute(vm::context &)
{

}

void label::Bind(vm::context &)
{
  throw label_instruction{source};
}
