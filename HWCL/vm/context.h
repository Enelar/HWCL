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
  private:
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

    map<string, raw_pointer> pointers;
    map<string, string, case_insesitive_cmp> alias;
    map<string, word, case_insesitive_cmp> localpoint;

    map<string, mapped_context> external;
    word last_wild = 80;
  public:
    void AddAlias(const string &, const string &);

    double &Local(const std::string &);

    DEPRECATED
    void AddLocal(const std::string &var);
    DEPRECATED
    void AddLocal(const std::string &var, const string &addr);
    DEPRECATED
    void AddLocal(const std::string &var, const string &addr, const string &type);

    template<typename T>
    void AddLocal(const string &name, const pointer<T> &)
    {
      IMPLEMENTATION_REQUIRED    }

    void AddExternal(const string &);
    mapped_context External(const string &);

    friend class process;
  };
}

#define HWCL_CONTEXT_DECLARED

#include "context.hpp"
#include "types/pointer.hpp"
#endif

#endif