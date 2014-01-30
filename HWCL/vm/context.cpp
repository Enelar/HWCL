#include "context.h"
#include "process.h"
#include "../parser/parser.h"

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
  {
    auto find = alias.find(name);
    if (find != alias.end())
      return Local(name);
  }

  auto tokens = parser::Split(name, '.');

  if (tokens.size() == 1) // local context
  {
    if (name == "DAY")
      return local.DAY;
    auto find = localpoint.find(name);
    if (find == localpoint.end())
      throw runtime_error(convert<string, vector<string>>({ "Undefined variable", name }));
    auto offset = find->second;
    if (offset < 80)
      return local.NN[offset];
    // Extra local variables
    offset -= 80;
    return local_NN[offset];
  }

  if (tokens.size() != 2)
    throw runtime_error(convert<string, vector<string>>({ "Undefined variable", name }));
  auto context = External(tokens[0]);
  return context->Local(tokens[1]);
}

void context::AddLocal(const std::string &name)
{
  DebugOutput(
  {
    "SYSTEM: CREATE LOCAL VARIABLE ",
    name,
    "\n"
  });
  localpoint.insert({ name, last_wild++ });
  local_NN.push_back(0);
}

void context::AddLocal(const std::string &name, const string &addr)
{
  DebugOutput(
  {
    "SYSTEM: MAP LOCAL VARIABLE ",
    name,
    " AT ",
    addr,
    "\n"
  });

  if (addr[0] == '!') // external context
  {
    AddAlias(name, addr);
    return;
  }

  if (addr[0] != 'N' || addr[1] != 'N')
    todo("Other types");
  throw_assert(addr[2] == '(' && addr[5] == ')');
  word offset = (addr[3] - '0') * 10 + (addr[4] - '0') - 1;

  localpoint.insert({ name, offset });
}

void context::AddAlias(const string &a, const string &b)
{
  alias.insert({ a, b });
}

context::mapped_context context::External(const string &name)
{
  auto find = external.find(name);
  if (find == external.end())
    throw runtime_error(convert<string, vector<string>>({ "Undefined external", name }));
  return find->second;
}