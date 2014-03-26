#include "program.h"

const decltype(program::program::code) &program::program::Code() const
{
  return code;
}

#include <fstream>
#include "../translator/translator.h"

::program::program::program(const string &filename)
{
  ifstream f(filename);

  throw_assert(f.is_open());

  while (!f.eof())
  {
    ub id, size;
    f >> id >> size;
    istream_iterator<ub> start(f);
    deque<ub> buf(size);
    copy_n(start, size, buf.begin());

    auto instr = translator::Translate(id, buf);
    code.push_back(instr);
  }
}

void program::program::Dump(const string &filename) const
{
  ofstream f(filename);

  throw_assert(f.is_open());

  for (auto instr : code)
  {
    auto codes = instr->Serialize();
    throw_assert(codes.size() <= 255);
    codes.push_front(codes.size());
    auto id = translator::InstructionCode(instr);
    codes.push_front(id);
    f.write((char *)&codes[0], codes.size());
  }

  f.close();
}