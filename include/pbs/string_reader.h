#pragma once

#include <string>

#include "reader.h"

using std::string;

namespace pbs {

template <typename T>
class StringReader : public Reader<T> {
  public:
    StringReader(const string* data, size_t* index);

    ReadResult Read(T* proto);

  private:
    const string* data_{nullptr};
    size_t* index_{nullptr};
};

}  // namespace pbs

#include "string_reader_impl.h"
