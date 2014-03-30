#include "process.h"
#include "../../vm/process_handler.h"

using namespace particular;

PROC_STATUSES process::Status()
{
  return UNDEFINED;
}

particular::process::process()
: i(nullptr)
{

}

particular::process::process(const process &p)
{
  if (p.i)
    i = new process_impl(*p.i);
  else
    i = nullptr;
}

particular::process::process(vm::process_handler ph)
: i(new process_impl(std::make_shared<vm::process_handler>(ph) ))
{

}

particular::process::~process()
{
  if (i)
    delete i;
}