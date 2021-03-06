#include "vm.h"

using namespace vm;

process_handler virtual_machine::Execute(program::cached_program &prog)
{
  auto p = std::make_shared<process>(prog);

  p->Bind(*this);

  ax::GrowId(last_pid);
  tasks.insert({last_pid, p});

  process_handler ret(p);
  return ret;
}

void virtual_machine::Cycle(flt dt)
{
  if (dt > 0)
    clock += dt;

  auto IsProcSuspendend = [this](const word &id)
  {
    return suspended.find(id) != suspended.end();
  };

  decltype(suspended) to_remove;

  for (auto pair : tasks)
  {
    const auto id = pair.first;
    const auto &pro� = pair.second;

    if (IsProcSuspendend(id))
      continue;

    try
    {
      pro�->Execute(clock);
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

context::mapped_context virtual_machine::GetExternalContext(const string &)
{
  return make_shared<context>();
}

int virtual_machine::GetEnumValue(const string &enum_name, const string &value_name)
{
  return 0;
}