#pragma once

#include "writer.h"

namespace pbs {

template <typename T>
class BufferWriter : public Writer<T> {
  public:
    BufferWriter(char** data, const char* data_end);

    bool Write(const T& proto);

  private:
    char** data_{nullptr};
    const char* data_end_{nullptr};
};

}  // namespace pbs

#include "buffer_writer_impl.h"
