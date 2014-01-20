#include "vm.h"

using namespace vm;

process_handler virtual_machine::Execute(program::cached_program &prog)
{
  auto p = std::make_shared<process>(prog);

  ax::GrowId(last_pid);
  tasks.insert({last_pid, p});

  process_handler ret(p);
  return ret;
}

void virtual_machine::Cycle()
{
}

bool virtual_machine::Idle() const
{
  word running = tasks.size() - suspended.size();
  return !running;
}