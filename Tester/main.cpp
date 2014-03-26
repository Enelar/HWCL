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

#include <functional>
#include <memory>

using namespace std;

struct a
{
  a()
  {

  }
  a(int)
  {

  }
  a(int, int)
  {

  }
};

template<typename T>
struct constructor
{
  template<typename... _Types>
  auto construct(_Types&&... _Args) -> T *
  {
    return new T(forward<_Types>(_Args)...);
  }
};

template<typename... _Types>
void F(_Types&&... _Args)
{
}

void main()
{
  //function<void(int)> test = &F;
  //typedef void (*ft)(int);
 // ft f = &F<int>;
  auto t = typeid(&F<int>).name();
  constructor<a> fabr;
  a
    *t1 = fabr.construct(),
    *t2 = fabr.construct(4),
    *t3 = fabr.construct<int>(5.0),
    *t4 = fabr.construct<int, int>(4, 4);
  //typedef constructor<a> AC
  //auto *F = &AC::construct;
  //std::function<a *(void)> f1 = ;
  //std::function<a *(int)> f2 = constructor<a>::construct;


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