#pragma once
#include "../stdafx.h"

#include <functional>
#include "tree.h"

namespace calculator
{
  class node
  {
    function<double(string)> GetVariable;
    token t;

    friend class tree;
    struct connect
    {
      node *next, *prev;

      node *Forward() const;
      node *Backward() const;
    };

    connect next, down;

    void Attach(node *const he, connect node::* me);
    node *Deattach(connect node::* me);

    tokenqueue Process(const tokenqueue &);
  public:
    node(const token &);

    void AttachNext(node *const);
    void AttachPrev(node *const);

    node *DeattachNext();
    node *DeattachPrev();

    void AttachDown(node *const);
    void AttachUp(node *const);

    node *DeattachDown();
    node *DeattachUp();


    static node *Build(tokenqueue);
  };

  struct back_token
  {
    tokenqueue q;
  };
}