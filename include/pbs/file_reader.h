#pragma once

#include <cstdio>

#include "reader.h"

namespace pbs {

template <typename T>
class FileReader : public Reader<T> {
  public:
    FileReader(FILE* file);

    ReadResult Read(T* proto);

  private:
    FILE* file_{nullptr};
};

}  // namespace pbs

#include "file_reader_impl.h"
