#pragma once
#include "../stdafx.h"

#include <vector>
#include <string>
#include <map>
#include <memory>

namespace vm
{
  struct context : object
  {
    struct
    {
      double NN[80];
      bool FL[127];
      // time TIME[4];
      std::string STR = std::string(64, 0); // fill 64 byte with zeros
    } local;

    vector<double> local_NN;

    std::map<std::string, word> labels;

    void Label(const std::string &, word);
    word Label(const std::string &);

    typedef shared_ptr<context> mapped_context;
  private:
    map<string, string> alias;
    map<string, word> localpoint;

    map<string, mapped_context> external;
    word last_wild = 80;
  public:
    void AddAlias(const string &, const string &);

    double &Local(const std::string &);
    void AddLocal(const std::string &);
    void AddLocal(const std::string &, const string &);

    void AddExternal(const string &);
    mapped_context External(const string &);

    friend class process;
  };
}