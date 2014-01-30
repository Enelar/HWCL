#pragma once
#include "../stdafx.h"

#include <functional>
#include "tree.h"

#include <deque>

namespace calculator
{
  class executer
  {
    //typedef node::nextT memsafe_node;
    typedef std::deque<node::nextT> token_levels;
    typedef std::deque<token_levels> token_map;
    calculator::get_callback GetVariable;

    word zero_level_offset = 0;
    token_map turing_tape;

    node::nextT root;
  public:
    executer(node::nextT root);
    token Recognize(token);
    node::nextT Execute();
    pair<double, node::nextT> VacuumBraces(node::nextT);
    // returns ptr to previous sequence copy
    node::nextT Erase(node::nextT, node::nextT);
    node::nextT Replace(node::nextT, node::nextT, node::nextT value);
  private:
    enum COMMANDS
    {
      NEXT, UP, DOWN
    };
    list<COMMANDS> commands;
    node::nextT Next(node::nextT);
    token_map::const_reference GetLevel(int);
  };

  struct cant_vacuum
  {

  };
}