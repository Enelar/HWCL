#include "../header.h"


void main()
{
  auto prog = 
  particular::CompileProgram
  (
    "w:/documents/SourceSafe/_NH3_VN-3/Data/CL/"
    "AP103J.CL"
  );
  auto proc = particular::ExecuteProgram(prog);

  while (1)
    particular::VM_Step(0);
}