#include "export_header.h"
#include "../vm/vm.h"
#include "import_center\import_center.h"

namespace particular
{
  struct particular_vm : vm::virtual_machine
  {
    std::map<string, vm::context::mapped_context> already_mapped;

    import_center_with_storage &ic =
      static_cast<import_center_with_storage &>(import_center::GetImportCenter());

    vm::context::mapped_context GetExternalContext(const string &name) override;

    int GetEnumValue(const string &struct_name, const string &name) override;

  };
}