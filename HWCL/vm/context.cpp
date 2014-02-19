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

void context::AddLocal(const std::string &var, const string &addr, const string &type)
{
  enum TYPE
  {
    NUMBER,
    LOGICAL,
    STRING
  } t;

  if (addr.find("NN") != string::npos)
    t = NUMBER;
  else if (addr.find("FL") != string::npos)
    t = LOGICAL;
  else if (addr.find("STR") != string::npos)
    t = STRING;
  else
    throw_message("Other types");

  if (type.find("ARRAY") != string::npos)
  {
    word start_index, end_index;
    auto GetIndexes = [&]()
    {
      auto spaces = parser::Split(type, '(');
      throw_assert(spaces.size() == 2);
      auto indexes = parser::Split(spaces[1], "..");
      stringstream ss;
      ss << indexes[0] << " " << indexes[1];
      ss >> start_index >> end_index;
    };
    GetIndexes();

    auto ConstructVar = [this](word start, word end, string name, string addr)
    {
      auto addr_parts = parser::Split(addr, '(');
      throw_assert(addr_parts.size() == 2);
      word offset = [addr_parts]()
      {
        stringstream ss;
        ss << addr_parts[1];
        word ret;
        ss >> ret;
        return ret;
      }();
      auto addr_base_name = addr_parts[0];

      auto NewVarName = [](string name, word offset)
      {
        stringstream ss;
        ss << name << "(" << offset << ")";
        return ss.str();
      };

      for (word i = start - 1; i < end; i++)
      {
        auto var = NewVarName(name, i + 1);
        auto new_addr = NewVarName(addr_base_name, i + offset);
        AddLocal(var, new_addr);
      }
    };
    ConstructVar(start_index, end_index, var, addr);
    return;
  }


  if (t == NUMBER)
  {
    AddLocal(var, addr);
    return;
  }
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