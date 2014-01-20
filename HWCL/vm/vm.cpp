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
  auto IsProcSuspendend = [this](const word &id)
  {
    return suspended.find(id) != suspended.end();
  };

  decltype(suspended) to_remove;

  for (auto pair : tasks)
  {
    const auto id = pair.first;
    const auto &prog = pair.second;

    if (IsProcSuspendend(id))
      continue;

    try
    {
      prog->Execute();
    }
    catch (vm::process::finished)
    {
      to_remove.insert(id);
    }
  }

  for (auto id : to_remove)
    tasks.erase(id);
}

bool virtual_machine::Idle() const
{
  word running = tasks.size() - suspended.size();
  return !running;
}