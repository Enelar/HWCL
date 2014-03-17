#pragma once

#include <cstring>

namespace particular
{
  template<typename T>
  struct crt_compatible_string
  {
  private:
    char *name;
    int length;
  public:
    crt_compatible_string(const char *_name)
    {
      length = strlen(_name);
      name = new char[length + 1];
      memcpy(name, _name, length + 1);
    }

    crt_compatible_string(const std::string &str)
    {
      length = str.length();
      name = new char[length + 1];
      memcpy(name, str.c_str(), length + 1);
    }

    crt_compatible_string(const crt_compatible_string &str)
    {
      delete[] name;
      length = str.length;
      name = new char[length + 1];
      memcpy(name, str.name, length + 1);
    }

    operator std::string() const
    {
      return std::string(name);
    }

    ~crt_compatible_string()
    {
      if (name)
        delete[] name;
    }
  };

  typedef crt_compatible_string<char> string_param;
}