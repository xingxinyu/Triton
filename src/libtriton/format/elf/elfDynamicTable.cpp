//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <cstdio>

#include <elfDynamicTable.hpp>
#include <exceptions.hpp>



namespace triton {
  namespace format {
    namespace elf {

      ElfDynamicTable::ElfDynamicTable() {
        this->tag   = 0;
        this->value = 0;
      }


      ElfDynamicTable::ElfDynamicTable(const ElfDynamicTable& copy) {
        this->tag   = copy.tag;
        this->value = copy.value;
      }


      ElfDynamicTable::~ElfDynamicTable() {
      }


      void ElfDynamicTable::operator=(const ElfDynamicTable& copy) {
        this->tag   = copy.tag;
        this->value = copy.value;
      }


      triton::uint32 ElfDynamicTable::parse(const triton::uint8* raw, triton::uint8 EIClass) {
        triton::format::elf::Elf32_Dyn_t dyn32;
        triton::format::elf::Elf64_Dyn_t dyn64;

        switch (EIClass) {
          case triton::format::elf::ELFCLASS32:
            memcpy(&dyn32, raw, sizeof(triton::format::elf::Elf32_Dyn_t));
            this->tag   = dyn32.d_tag;
            this->value = dyn32.d_val;
            return sizeof(triton::format::elf::Elf32_Dyn_t);

          case triton::format::elf::ELFCLASS64:
            memcpy(&dyn64, raw, sizeof(triton::format::elf::Elf64_Dyn_t));
            this->tag   = dyn64.d_tag;
            this->value = dyn64.d_val;
            return sizeof(triton::format::elf::Elf64_Dyn_t);

          default:
            throw triton::exceptions::Elf("ElfDynamicTable::parse(): Invalid EI_CLASS.");
        }
        return 0;
      }


      triton::sint64 ElfDynamicTable::getTag(void) const {
        return this->tag;
      }


      triton::uint64 ElfDynamicTable::getValue(void) const {
        return this->value;
      }

    }; /* elf namespace */
  }; /* format namespace */
}; /* triton namespace */

