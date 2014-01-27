#pragma once
#include "../stdafx.h"

#include <functional>
#include "tree.h"

#include <deque>

namespace calculator
{
  class executer
  {
    typedef std::shared_ptr<token> memsafe_token;
    typedef std::list<memsafe_token> token_levels;
    typedef std::deque<token_levels> token_map;

    word zero_level_offset = 0;
    token_map turing_tape;
  public:
    executer(const node *root);

  private:
    enum COMMANDS
    {
      NEXT, UP, DOWN
    };
    list<COMMANDS> commands;
    const node *Next(const node *);
    token_map::const_iterator GetLevel(int);
  };
}