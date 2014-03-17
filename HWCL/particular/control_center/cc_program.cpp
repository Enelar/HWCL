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
  auto &ic = import_center_with_storage::GetImportCenter();

  auto IsFileExsists = [](const string &filename)
  {
    fstream f(filename);
    return f.is_open();
  };

  auto compiled_file = 
    convert<string, vector<string>>(
    {
      ic.compiled_files_path,
      *filename,
      ".PCCL"
    });

  if (IsFileExsists(compiled_file))
    return ::program::program(compiled_file);

  auto source_file = 
    convert<string, vector<string>>(
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
      std::stringstream ss;
      std::string buf;

      while (getline(f, buf))
      {
        for (auto ch : buf)
          ss << static_cast<decltype(ch)>(toupper(ch));
        ss << std::endl;
      }
      return ss.str();
    };

    parser::parser p(ReadFile(filename));
    return p.Translate();
  };

  auto ret = CompileProgram(source_file);
  ret->Dump(compiled_file);
  return ret;
}