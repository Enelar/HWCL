#include "end.h"
#include "../../parser/parser.h"

using namespace program::instructions;

end::end(const string &source)
: instruction(source, "end")
{

}

bool end::Signature(const string &source)
{
  return parser::CompareCommand(source, "END");
}

void end::Execute(vm::context &)
{

}

end::end(const deque<ub> &)
: instruction("")
{

}

deque<ub> end::Serialize()
{
  todo("Serialize");
}