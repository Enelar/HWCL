#pragma once
#include "../stdafx.h"

#include <functional>
#include "tree.h"

namespace calculator
{
  class node
  {
  public:
    typedef shared_ptr<node> nextT;
  private:
    function<double(string)> GetVariable;
    token t;

    friend class tree;
    struct connect
    {
      nextT next, prev;

      node *Forward() const;
      node *Backward() const;

      ~connect()
      {
        if (next)
          next.reset();
        if (prev)
          prev.reset();
      }
    };

    connect next, down;

    nextT Attach(node *const he, connect node::* me);
    nextT Deattach(connect node::* me);

    tokenqueue Process(const tokenqueue &);

    friend class executer;
  public:
    node(const token &);
    ~node()
    {
    }

    nextT AttachNext(node *const);
    nextT AttachPrev(node *const);

    nextT DeattachNext();
    nextT DeattachPrev();

    nextT AttachDown(node *const);
    nextT AttachUp(node *const);

    nextT DeattachDown();
    nextT DeattachUp();

    nextT Back() const;
    nextT Forward() const;
    nextT Up() const;
    nextT Down() const;

    static node *Build(tokenqueue);

    bool Alone() const;
    bool Edge() const;

    token Token() const;
    token Token(token);
  };

  struct back_token
  {
    tokenqueue q;
  };
}