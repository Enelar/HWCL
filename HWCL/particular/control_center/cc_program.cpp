#include "program.h"
#include "../../program/cached_program.h"

#include "../import_center/import_center.h"

particular::program::~program()
{
  delete filename;
}

particular::program::program(const std::string &f)
: filename(new std::string{ f })
{
}

template<>
string convert(const word &a)
{
  stringstream ss;
  ss << a;
  return ss.str();
}

#include <fstream>
#include "../../translator/translator.h"
#include "../../parser/parser.h"

::program::cached_program particular::program::GetCode() const
{
  auto &ic = import_center_with_storage::GetImportCenter();

  auto IsFileExsists = [](const string &filename)
  {
    fstream f(filename);
    return f.is_open();
  };

  auto compiled_file = 
    convert<string, initializer_list<string>>(
    {
      ic.compiled_files_path,
      *filename,
      ".PCCL"
    });

  if (IsFileExsists(compiled_file))
    return ::program::program(compiled_file);

  auto source_file = 
    convert<string, initializer_list<string>>(
    {
      ic.cl_files_path,
      *filename,
      ".CL"
    });

  auto CompileProgram = [](const string &filename)
  {
    auto ReadFile = [](const string &filename) -> string
    {
      std::ifstream f(filename);

      if (!f.is_open())
      {
        DebugOutput(
        {
          "FILE ",
          filename,
          " NOT FOUND. EMULATING EMPTY."
        });
        return "-- FILE NOT FOUND";
      }

      f.seekg(0, f.end);

      bword length = [&f]()
      {
        bword length = f.tellg();
        throw_assert(length < WORD_MAX + 1);
        return length;
      }();

      f.seekg(0, f.beg);

      unique_ptr<char[]> buf(new MEMLEAK char[(word)length + 1]);

      char *b = buf.get();
      f.read(b, length);

      if (!f)
        length = f.gcount();

      for (word i = 0; i < length; i++)
        b[i] = toupper(b[i]);
      b[length] = 0;

      return b;
    };

    parser::parser p(ReadFile(filename));
    return p.Translate();
  };

  auto ret = CompileProgram(source_file);
  ret->Dump(compiled_file);
  return ret;
}