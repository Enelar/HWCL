#ifndef HWCL_POINTER_DEFINED
#include "..\types\pointer.h"
#else
#include "../../stdafx.h"
#include <algorithm>

namespace vm
{
  namespace context_utils
  {
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

    struct routes
    {
      map<string, VAR_TYPE> dynamic_typing;

      map<string, shared_ptr<raw_pointer>> pointers;
      map<string, string, case_insesitive_cmp> alias;
      map<string, word, case_insesitive_cmp> localpoint;

      map<string, mapped_context> external;

      void AddPointer(const string &name, const shared_ptr<raw_pointer>, context *c);
      void AddAlias(const string &, const string &);

      void AddExternal(const string &);
      mapped_context External(const string &) const;

    };


  }
}

#endif