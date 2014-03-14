#pragma once

#include "../export_header.h"

namespace program
{
  class cached_program;
}

#include <string>

namespace particular
{
  struct _HWCL_METHOD_ program
  {
    ~program();
  private:
    std::string *filename;

    friend class control_center;
    ::program::cached_program GetCode() const;

    friend class control_center;
    program(const std::string &filename );
  };
}