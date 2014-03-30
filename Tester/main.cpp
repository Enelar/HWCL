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

using namespace std;

#include <direct.h>

void main()
{
  auto &ic = particular::import_center::GetImportCenter();
  ic.GetStructCallback(&RequestStruct);
  ic.GetEnumValueCallback(&RequestEnumValue);

  const auto path = []()
  {
    const word size = 1000;
    char str[size];
    throw_assert(_getcwd(str, size));
    return string(str) + string("/../");
  }();

  ic.SetStoragesPath(
    path, 
    path,
    path);

  if (!ic.Imported())
    return;
  auto cc = ic.GetControlCenter();

  auto prog = cc.CompileProgram
  (
    "AIR"
  );
  auto proc = cc.ExecuteProgram(prog);

  while (1)
    cc.VM_Step(0.1);
}