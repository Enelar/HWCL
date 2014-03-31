#pragma once

#include "context.h"

namespace vm
{
  struct extern_context : public context
  {
  public:
    void AddLocal(const string &name, void *ptr, VAR_TYPE t)
    {
      if (t == NUMBER)
      {
        typedef extern_pointer<vm::floating_point> pointer_t;
        auto p = make_shared<pointer_t>(ptr, t);
        routes.dynamic_typing.insert({ name, t });
        routes.pointers.insert({ name, p });
        return;
      }
      if (t == BOOLEAN)
      {
        typedef extern_pointer<bool> pointer_t;
        auto p = make_shared<pointer_t>(ptr, t);
        routes.dynamic_typing.insert({ name, t });
        routes.pointers.insert({ name, p });
        return;
      }
      if (t == STRING)
      {
        typedef extern_pointer<string> pointer_t;
        auto p = make_shared<pointer_t>(ptr, t);
        routes.dynamic_typing.insert({ name, t });
        routes.pointers.insert({ name, p });
        return;
      }
      if (t == ENUM)
      {
        typedef extern_pointer<int> pointer_t;
        auto p = make_shared<pointer_t>(ptr, t);
        routes.dynamic_typing.insert({ name, t });
        routes.pointers.insert({ name, p });
        return;
      }
      dead_space();
    }

    function<int(string, string)> GetEnumField; REFACTOR

    int EnumWorkAround(const string &namelist, const string &name) override
    {
        int ret;

        if (context::EnumWorkAround(namelist, name, ret))
          return ret;
        ret = GetEnumField(namelist, name);

        auto i_namelist = enums.find(namelist);
        if (i_namelist == enums.end())
        {
          enums.insert({ namelist, {} });
          i_namelist = enums.find(namelist);
          throw_assert(i_namelist != enums.end());
        }
        i_namelist->second.insert({ name, ret });
        return ret;
    }
  };
}