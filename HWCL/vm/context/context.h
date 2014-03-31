#ifndef HWCL_CONTEXT_DECLARED

#ifndef HWCL_POINTER_DEFINED
#include "..\types\pointer.h"
#else

#include "../../stdafx.h"

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>
#include <functional>

#include "local_vars.h"
#include "labels.h"

namespace vm
{
  struct raw_pointer;
  struct context : object
  {
    context_utils::local_vars local;
    context_utils::labels labels;

    map<string, VAR_TYPE> dynamic_typing;

    typedef shared_ptr<context> mapped_context;
  protected:
    struct case_insesitive_cmp
    {
      bool operator() (const std::string& lhs, const std::string& rhs) const
      {
        auto tolower = [](string s)
        {
          transform(s.begin(), s.end(), s.begin(), ::tolower);
          return s;
        };
        return tolower(lhs) < tolower(rhs);
      }
    };

    map<string, shared_ptr<raw_pointer>> pointers;
    map<string, string, case_insesitive_cmp> alias;
    map<string, word, case_insesitive_cmp> localpoint;

    map<string, mapped_context> external;
    word last_wild = 80;

    void AddPointer(const string &name, const shared_ptr<raw_pointer> );
  public:
    void AddAlias(const string &, const string &);

    double &Local(const std::string &);
    VAR_TYPE GetType(const std::string &name) const;

    shared_ptr<raw_pointer> GetRawPointer(const std::string &name) const;
    template<typename T>
    shared_ptr<pointer_interface<T>> GetPointer(const std::string &name) const;

    DEPRECATED
    void AddLocal(const std::string &var);
    DEPRECATED
    void AddLocal(const std::string &var, const string &addr);
    DEPRECATED
    void AddLocal(const std::string &var, const string &addr, const string &type);

    template<typename T>
    void AddLocal(const string &name, shared_ptr<pointer<T>>);
    template<typename T>
    void AddLocal(const string &name, const pointer<T> &);
    void AddLocal(const string &name, void *ptr, VAR_TYPE type);

    map<string, map<string, int>> enums;


    void AddExternal(const string &);
    mapped_context External(const string &) const;

    virtual int EnumWorkAround(const string &namelist, const string &name); REFACTOR
    bool EnumWorkAround(const string &namelist, const string &name, int &exception); REFACTOR

    friend class process;
    struct variable_not_found {};
  };
}

#define HWCL_CONTEXT_DECLARED

#include "context.hpp"
#include "../types/pointer.hpp"
#endif

#include "extern_context.h"

#endif