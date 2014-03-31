#include "context.h"
#include "process.h"
#include "../../parser/parser.h"
#include "..\types\pointer.h"

using namespace vm;

double &context::Local(const std::string &name)
{
  {
    auto find = routes.alias.find(name);
    if (find != routes.alias.end())
      return Local(name);
  }

  auto tokens = parser::Split(name, '.');

  if (tokens.size() == 1) // local context
  {
    if (name == "DAY")
      return local.DAY;
    auto find = routes.localpoint.find(name);
    if (find == routes.localpoint.end())
      throw runtime_error(convert<string, deque<string>>({ "Undefined variable", name }));
    auto offset = find->second;
    if (offset < 80)
      return local.NN[offset];
    // Extra local variables
    offset -= 80;
    return local.local_NN[offset];
  }

  if (tokens.size() != 2)
    throw runtime_error(convert<string, deque<string>>({ "Undefined variable", name }));
  auto context = routes.External(tokens[0]);
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
  routes.localpoint.insert({ name, last_wild++ });
  local.local_NN.push_back(0);
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
    routes.AddAlias(name, addr);
    return;
  }

  if (addr[0] != 'N' || addr[1] != 'N')
    todo("Other types");
  throw_assert(addr[2] == '(' && addr[5] == ')');
  word offset = (addr[3] - '0') * 10 + (addr[4] - '0') - 1;

  routes.localpoint.insert({ name, offset });
}

void context::AddLocal(const string &name, void *addr, VAR_TYPE type)
{
  todo(Direct pointers);
}

void context::AddLocal(const std::string &var, const string &addr, const string &type)
{
  if (type.find("ARRAY") != string::npos)
  {
    todo(array);
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

  {
    pointer<floating_point> p = addr;
    if (CheckPointerType<floating_point>(p))
    {
      AddLocal(var, p);
      return;
    }
  }
  {
    pointer<bool> p = addr;
    if (CheckPointerType<bool>(p))
    {
      AddLocal(var, p);
      return;
    }
  }
  {
    pointer<string> p = addr;
    if (CheckPointerType<string>(p))
    {
      AddLocal(var, p);
      return;
    }
  }

  dead_space();
}



int context::EnumWorkAround(const string &namelist, const string &name)
{
  int ret;

  if (!EnumWorkAround(namelist, name, ret))
    throw_message("Enum name not found");
  return ret;
}

bool context::EnumWorkAround(const string &namelist, const string &name, int &ret )
{
  auto i_enum = enums.find(namelist);
  if (i_enum == enums.end())
  {
    auto parts = parser::Split(namelist, '.');
    if (parts.size() != 2)
      return false;
    auto external = routes.External(parts[0]);
    try
    {
      ret = external->EnumWorkAround(parts[1], name);
      return true;
    }
    catch (...)
    {
      return false;
    }
  }
  auto i_field = i_enum->second.find(name);
  if (i_field == i_enum->second.end())
    return false;
  ret = i_field->second;
  return true;
}

VAR_TYPE context::GetType(const std::string &name) const
{
  {
    auto ts = routes.dynamic_typing.find(name);
    if (ts != routes.dynamic_typing.end())
      return ts->second;
  }
  {
    auto p = routes.pointers.find(name);
    if (p != routes.pointers.end())
      return p->second->Type();
  }

  {
    auto parts = parser::Split(name, '.');
    throw_assert(parts.size() == 2);
    auto external = routes.External(parts[0]);
    return external->GetType(parts[1]);
  }
}

shared_ptr<raw_pointer> context::GetRawPointer(const std::string &name) const
{
  auto pointer = routes.pointers.find(name);

  if (pointer == routes.pointers.end())
  {
    auto parts = parser::Split(name, '.');
    if (parts.size() != 2)
      throw context::variable_not_found();
    auto external = routes.External(parts[0]);
    return external->GetRawPointer(parts[1]);
  }

  auto ret = pointer->second;
  return ret;
}