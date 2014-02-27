#include "../stdafx.h"
#include "export_callbacks.h"
#include "../vm/vm.h"

using namespace particular;

#include <hash_map>

hash_map<prog_handle, program::cached_program> compilator_cache;

#include "../parser\parser.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <math.h>

#include "process_handle.h"
#include "program_handle.h"

template<>
program_handle convert(const prog_handle &a)
{
  return remote_handle::Undestand<program_handle>(a);
}

template<>
process_handle convert(const prog_handle &a)
{
  return remote_handle::Undestand<process_handle>(a);
}

template<typename B, typename A>
B convertp(A *a)
{
  IMPLEMENTATION_REQUIRED
}

template<>
prog_handle convertp(program_handle *a)
{
  return reinterpret_cast<prog_handle>(a);
}

template<>
proc_handle convertp(process_handle *a)
{
  return reinterpret_cast<proc_handle>(a);
}

_HWCL_METHOD_ prog_handle particular::CompileProgram(const char *filename)
{
  std::string source = [filename]()->std::string
  {
    std::ifstream f;
    f.open(filename);

    throw_assert(f.is_open());
    std::stringstream ss;
    std::string buf;

    while (getline(f, buf))
      ss << buf << std::endl;
    return ss.str();
  }();

  parser::parser p(source);
  auto prog = p.Translate();

  do
  {
    auto hash = rand();
    if (compilator_cache.find(hash) != compilator_cache.end())
      continue;
    compilator_cache.insert({ hash, prog });
    return convertp<prog_handle>(NEW program_handle(hash));
  } while (true);

  dead_space();
}

#include "process_handle.h"
#include "program_handle.h"
#include "import_callbacks.h"
#include <functional>

extern particular::request_get_struct_callback GSCB;
function<void(int, particular::param *)> ActualHook = nullptr;

void GetStructLoopBack(int count, particular::param *p)
{
  throw_assert(ActualHook);
  ActualHook(count, p);
}

struct particular_vm : vm::virtual_machine
{
  std::map<string, vm::context::mapped_context> already_mapped;

  virtual vm::context::mapped_context GetExternalContext(const string &name) override
  {
    auto find = already_mapped.find(name);
    if (find != already_mapped.end())
      return find->second;

    unique_ptr<vm::extern_context> res = make_unique<vm::extern_context>();
    auto StructCatched = [&res](int count, particular::param *params)
    {
      for (int i = 0; i < count; i++)
      {
        particular::param &p = params[i];
        res->AddLocal(p.name, p.addr, p.type);
      }
    };
    ActualHook = StructCatched;
    bool found = (*GSCB)(name.c_str(), GetStructLoopBack);
    auto ret = vm::context::mapped_context(res.release());
    already_mapped.insert({ name, ret });
    return ret;
  }
};

particular_vm computer;

_HWCL_METHOD_ proc_handle particular::ExecuteProgram(prog_handle ph)
{
  auto h = convert<program_handle>(ph);

  auto source = [h]()
  {
    auto f = compilator_cache.find(h.hash);
    return f->second;
  }();

  auto ret = NEW process_handle({ computer.Execute(source) });
  return convertp<proc_handle>(ret);
}

_HWCL_METHOD_ void particular::VM_Step(double dt)
{
  computer.Cycle();
}

_HWCL_METHOD_ void particular::CloseHandle(prog_handle ph)
{
  auto h = convert<process_handle>(ph);
  delete &h;
}

_HWCL_METHOD_ PROC_STATUSES particular::ProcessStatus(prog_handle)
{
  return UNDEFINED;
}