#include "context.h"

using namespace vm;

namespace
{
  vector<deque<ub>> ExtractDeques(const deque<ub> &orign )
  {
    vector<deque<ub>> ret;

    word i = 0, e = orign.size();

    auto ExtractDeque = [&orign, &i](const word size) -> deque<ub>
    {
      return{ orign.begin() + i, orign.begin() + i + size };
    };

    while (i < e)
    {
      word size = orign[i++];
      ret.push_back(ExtractDeque(size));
      i += size;
    }

    return ret;
  }
}

context::context(const deque<ub> &orign)
: context(ExtractDeques(orign))
{
}

context::context(const vector<deque<ub>> &orign)
: local(orign[0]), labels(orign[1]), routes(orign[2])
{

}

deque<ub> context::Serialize() const
{
  deque<ub> ret;

  auto Append = [&ret](const deque<ub> &a)
  {
    ret.insert(ret.end(), a.size());
    ret.insert(ret.end(), a.begin(), a.end());
  };

  Append(local.Serialize());
  Append(labels.Serialize());
  Append(routes.Serialize());

  return ret;
}
