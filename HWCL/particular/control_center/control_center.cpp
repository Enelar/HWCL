#include "control_center.h"
#include "../particular_vm.h"

using namespace particular;
extern particular_vm computer;

#include <memory>
#include "../../program/cached_program.h"

process control_center::ExecuteProgram(const particular::program &ph)
{
  auto source = ph.GetCode();

  auto handler = computer.Execute(source);

  return process({ handler });
}

void control_center::VM_Step(double dt)
{
  computer.Cycle();
}