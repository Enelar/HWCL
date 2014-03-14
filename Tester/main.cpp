#include "../header.h"


bool RequestStruct(const std::string &name, particular::import_center::get_struct_callback cb)
{
  cb(0, nullptr);
  return true;
}

int RequestEnumValue(const std::string &struct_name, const std::string &name)
{
  return 0;
}

void main()
{
  auto &ic = particular::import_center::GetImportCenter();
  ic.GetStructCallback(&RequestStruct);
  ic.GetEnumValueCallback(&RequestEnumValue);

  if (!ic.Imported())
    return;
  auto cc = ic.GetControlCenter();

  auto prog = cc.CompileProgram
  (
    "w:/documents/SourceSafe/_NH3_VN-3/Data/CL/"
    "AP103J.CL"
  );
  auto proc = cc.ExecuteProgram(prog);

  while (1)
    cc.VM_Step(0);
}