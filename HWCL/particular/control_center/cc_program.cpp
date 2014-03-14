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

#include <fstream>
#include "../../translator/translator.h"
#include "../../parser/parser.h"

::program::cached_program particular::program::GetCode() const
{
  const import_center_with_storage &ic =
    static_cast<import_center_with_storage &>(import_center::GetImportCenter());

  auto IsFileExsists = [](const string &filename)
  {
    fstream f(filename);
    return f.is_open();
  };

  auto compiled_file = 
    convert<string, vector<string>>(
    {
      ic.compiled_files_path,
      *filename
    });

  if (IsFileExsists(compiled_file))
    return ::program::program(compiled_file);

  auto source_file =
    convert<string, vector<string>>(
    {
      ic.state_files_path,
      *filename
    });

  auto CompileProgram = [](const string &filename)
  {
    auto ReadFile = [](const string &filename)
    {
      std::ifstream f(filename);

      throw_assert(f.is_open());
      std::stringstream ss;
      std::string buf;

      while (getline(f, buf))
        ss << buf << std::endl;
      return ss.str();
    };

    parser::parser p(ReadFile(filename));
    return p.Translate();
  };

  auto ret = CompileProgram(source_file);
  ret->Dump(compiled_file);
  return ret;
}