#include "tree.h"

using namespace calculator;

void tree::Build(const string &str)
{
  algebra::token_queue::Build(str);
  BuildReversePolish();
}