#include "program.h"

const decltype(program::program::code) &program::program::Code() const
{
  return code;
}

#include <fstream>
#include "../translator/translator.h"

::program::program::program(const string &filename)
{
  ifstream f(filename, std::ios::binary);

  throw_assert(f.is_open());

  auto ReadByte = [&f]() -> ub
  {
    char ch;
    f.read(&ch, 1);
    return ch;
  };

  auto ReadDeque = [&f](word size) -> deque<ub>
  {
    char buf[BYTE_MAX];
    throw_assert(BYTE_MAX >= size);
    f.read(buf, size);

    return{ buf, buf + size };    
  };

  while (true)
  {
    ub id, size;
    id = ReadByte();
    if (f.eof())
      break;
    size = ReadByte();

    deque<ub> buf = ReadDeque(size);

    if (!id)
    {
      string codes(buf.begin(), buf.end());
      code.push_back(translator::Translate(codes));
      continue;
    }

    auto instr = translator::Translate(id, buf);
    code.push_back(instr);
  }
}

void program::program::Dump(const string &filename) const
{
  ofstream f(filename, std::ios::binary);

  throw_assert(f.is_open());

  for (auto instr : code)
  {
    auto codes = instr->Serialize();
    throw_assert(codes.size() <= 255);
    codes.push_front((ub)codes.size());
    auto id = translator::InstructionCode(instr);
    codes.push_front((ub)id);

    copy(codes.begin(), codes.end(), ostream_iterator<ub>(f, ""));
  }

  f.close();
}