#include "program.h"
#include "../../program/cached_program.h"

using namespace particular;

particular::program::~program()
{
}

particular::program::program(const std::string &f)
: filename(f)
{

}

::program::cached_program particular::program::GetCode() const
{

}