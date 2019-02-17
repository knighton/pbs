#pragma once

#include <cstdio>

#include "writer.h"

namespace pbs {

template <typename T>
class FileWriter : public Writer<T> {
  public:
    FileWriter(FILE* file);

    bool WriteOne(const T& proto) override;

  private:
    FILE* file_{nullptr};
};

}  // namespace pbs

#include "file_writer_impl.h"
