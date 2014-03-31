#include "../types/pointer.h"

using namespace vm::context_utils;
using namespace vm;

void routes::AddAlias(const string &a, const string &b)
{
  alias.insert({ a, b });
}

vm::mapped_context routes::External(const string &name) const
{
  auto find = external.find(name);
  if (find == external.end())
    throw runtime_error(convert<string, deque<string>>({ "Undefined external", name }));
  return find->second;
}

void routes::AddPointer(const string &name, const shared_ptr<raw_pointer> p, context *c)
{
  p->Origin(c);

  dynamic_typing.insert({ name, p->Type() });
  pointers.insert({ name, p });
}

routes::routes(const deque<ub> &)
{

}
deque<ub> routes::Serialize() const
{
  return{};
}