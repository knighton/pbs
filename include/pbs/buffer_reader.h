#pragma once

#include "reader.h"

namespace pbs {

template <typename T>
class BufferReader : public Reader<T> {
  public:
    BufferReader(const char** data, const char* data_end);

    ReadResult Read(T* proto);

  private:
    const char** data_{nullptr};
    const char* data_end_{nullptr};
};

}  // namespace pbs

#include "buffer_reader_impl.h"
