#include "control_center.h"
#include "particular_vm.h"

extern particular_vm computer;

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