#include "../header.h"

bool RequestStruct(const particular::string_param &name, particular::import_center::get_struct_callback cb)
{
  cb(0, nullptr);
  return true;
}

int RequestEnumValue(const particular::string_param &struct_name, const particular::string_param &name)
{
  return 0;
}

void main()
{
  auto &ic = particular::import_center::GetImportCenter();
  ic.GetStructCallback(&RequestStruct);
  ic.GetEnumValueCallback(&RequestEnumValue);
  ic.SetStoragesPath(
    "w:/documents/SourceSafe/_NH3_VN-3/Data/CL/", 
    "w:/documents/SourceSafe/_NH3_VN-3/Data/CL/", 
    "w:/documents/SourceSafe/_NH3_VN-3/Data/CL/");

  if (!ic.Imported())
    return;
  auto cc = ic.GetControlCenter();

  auto prog = cc.CompileProgram
  (
    "AP103J"
  );
  auto proc = cc.ExecuteProgram(prog);

  while (1)
    cc.VM_Step(0);
}