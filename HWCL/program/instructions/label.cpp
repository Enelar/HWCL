#include "label.h"
#include "../../parser/parser.h"

using namespace program::instructions;

label::label(const string &source)
: instruction(source, "label")
{

}

bool label::Signature(const string &source)
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
      if (!IsAlph(ch))
        return false;
      state = LABEL_NAME;
      break;
    case LABEL_NAME:
      if (IsAlph(ch) || IsNum(ch))
        break;
      return ch == ':';
    }
    i++;
  };
  return false;
}

void label::Execute(vm::context &)
{

}