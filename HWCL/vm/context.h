#pragma once
#include "../stdafx.h"

#include <string>
#include <map>

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

    std::map<std::string, word> labels;

    void Label(const std::string &, word);
    word Label(const std::string &);

  private:
    std::map<std::string, word> alias;
    word last_wild = 80;
  public:
    double &Local(const std::string &);
    void AddLocal(const std::string &);
    void AddLocal(const std::string &, word index);
  };
}