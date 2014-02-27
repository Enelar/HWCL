#ifndef HWCL_CONTEXT_DECLARED

#ifndef HWCL_POINTER_DEFINED
#include "types\pointer.h"
#else

#include "../stdafx.h"

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>

namespace vm
{
  struct raw_pointer;
  struct context : object
  {
    struct
    {
      double NN[80];
      bool FL[127];
      double DAY;
      // time TIME[4];
      std::string STR = std::string(64, 0); // fill 64 byte with zeros
    } local;

    vector<double> local_NN;

    map<string, VAR_TYPE> dynamic_typing;
    std::map<std::string, word> labels;

    void Label(const std::string &, word);
    word Label(const std::string &);

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


    void AddExternal(const string &);
    mapped_context External(const string &) const;

    friend class process;
  };

  struct extern_context : public context
  {
  public:
    void AddLocal(const string &name, void *ptr, VAR_TYPE t)
    {
      if (t == NUMBER)
      {
        typedef extern_pointer<vm::floating_point> pointer_t;
        auto p = make_shared<pointer_t>(ptr, t);
        dynamic_typing.insert({ name, t });
        pointers.insert({ name, p });
        return;
      }
      if (t == BOOLEAN)
      {
        typedef extern_pointer<bool> pointer_t;
        auto p = make_shared<pointer_t>(ptr, t);
        dynamic_typing.insert({ name, t });
        pointers.insert({ name, p });
        return;
      }
      if (t == STRING)
      {
        typedef extern_pointer<string> pointer_t;
        auto p = make_shared<pointer_t>(ptr, t);
        dynamic_typing.insert({ name, t });
        pointers.insert({ name, p });
        return;
      }
      if (t == ENUM)
      {
        return;
      }
      dead_space();
    }
  };
}

#define HWCL_CONTEXT_DECLARED

#include "context.hpp"
#include "types/pointer.hpp"
#endif

#endif