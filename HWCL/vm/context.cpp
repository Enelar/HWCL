#include "context.h"
#include "process.h"

using namespace vm;

void context::Label(const std::string &name, word eip)
{
  auto find = labels.find(name);

  throw_assert(find == labels.end());
  labels.insert({ name, eip });
}

word context::Label(const std::string &name)
{
  auto find = labels.find(name);

  throw_assert(find != labels.end());
  return find->second;
}

double &context::Local(const std::string &name)
{
  auto find = alias.find(name);
  if (find == alias.end())
    throw runtime_error(convert<string, vector<string>>({ "Undefined variable", name }));
  auto offset = find->second;
  if (offset < 80)
    return local.NN[offset];
  todo(Alias without NN mapping);
}

void context::AddLocal(const std::string &name)
{
  DebugOutput(
  {
    "SYSTEM: CREATE LOCAL VARIABLE ",
    name
  });
  alias.insert({ name, last_wild++ });
}

void context::AddLocal(const std::string &name, word index)
{
  DebugOutput(
  {
    "SYSTEM: CREATE LOCAL VARIABLE ",
    name,
    " AT ",
    ToString(index)
  });
  alias.insert({ name, index });
}