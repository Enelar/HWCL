#include "calculator.h"
#include "tree.h"
#include <memory>

calculator::calculator::calculator(string expression)
: calculation_tree(make_unique<tree>().release())
{
  calculation_tree->Build(expression);
}

double calculator::calculator::Calculate(get_callback Get)
{
  todo(Calculate);
}


calculator::calculator::~calculator()
{
  if (calculation_tree)
    delete calculation_tree;
}