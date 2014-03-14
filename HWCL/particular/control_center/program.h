#pragma once

#include "../export_header.h"

namespace program
{
  class cached_program;
}

#include <string>

namespace particular
{
  struct program
  {
    ~program();
  private:
    std::string filename;
    std::string obj_filename;

    friend class control_center;
    ::program::cached_program GetCode() const;

    program(const std::string &filename );
  };
}