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

namespace vm
{
  struct context;
  typedef shared_ptr<context> mapped_context;
}

#include "local_vars.h"
#include "labels.h"
#include "routes.h"

namespace vm
{
  struct raw_pointer;
  struct context : object
  {
    context_utils::local_vars local;
    context_utils::labels labels;

    typedef shared_ptr<context> mapped_context;
  protected:
    word last_wild = 80;
  public:
    context_utils::routes routes;


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

    virtual int EnumWorkAround(const string &namelist, const string &name); REFACTOR
    bool EnumWorkAround(const string &namelist, const string &name, int &exception); REFACTOR

    friend class process;
    struct variable_not_found {};

    context() = default;
    context(const deque<ub> &);
    virtual deque<ub> Serialize() const;
  private:
    context(const vector<deque<ub>> &);
  };
}

#define HWCL_CONTEXT_DECLARED

#include "context.hpp"
#include "../types/pointer.hpp"
#endif

#include "extern_context.h"

#endif