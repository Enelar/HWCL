#include "particular_vm.h"

using namespace particular;

function<void(int, particular::param *)> ActualHook = nullptr;

void GetStructLoopBack(int count, particular::param *p)
{
  throw_assert(ActualHook);
  ActualHook(count, p);
}

vm::context::mapped_context particular_vm::GetExternalContext(const string &name)
{
  auto find = already_mapped.find(name);
  if (find != already_mapped.end())
    return find->second;

  unique_ptr<vm::extern_context> res = make_unique<vm::extern_context>();
  res->GetEnumField = [=](const string &a, const string &b)
  {
    return this->GetEnumValue(a, b);
  };

  auto StructCatched = [&res](int count, particular::param *params)
  {
    for (int i = 0; i < count; i++)
    {
      particular::param &p = params[i];
      res->AddLocal(p.name, p.addr, p.type);
    }
  };
  ActualHook = StructCatched;
  throw_assert(ic.rgscb);
  bool found = (*ic.rgscb)(name.c_str(), GetStructLoopBack);
  auto ret = vm::context::mapped_context(res.release());
  already_mapped.insert({ name, ret });
  return ret;
}

int particular_vm::GetEnumValue(const string &struct_name, const string &name)
{
  throw_assert(ic.gevcb);
  return (*ic.gevcb)(struct_name.c_str(), name.c_str());
}
