#include "../header.h"


bool RequestStruct(const char *name, particular::get_struct_callback cb)
{
  cb(0, nullptr);
  return true;
}

void main()
{
  particular::GetStructCallback(&RequestStruct);
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