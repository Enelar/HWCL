#include "send.h"
#include "../../parser/parser.h"

using namespace program::instructions;

send::send(const string &source)
: instruction(source, "send")
{

}

bool send::Signature(const string &source)
{
  return parser::CompareCommand(source, "SEND");
}

void send::Execute(vm::context &)
{

}

send::send(const deque<ub> &orign)
: send(string{ orign.begin(), orign.end() })
{

}

deque<ub> send::Serialize()
{
  return{ Source().begin(), Source().end() };
}