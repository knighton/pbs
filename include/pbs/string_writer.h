#pragma once

#include <string>

#include "writer.h"

using std::string;

namespace pbs {

template <typename T>
class StringWriter : public Writer<T> {
  public:
    StringWriter(string* data);

    bool WriteOne(const T& proto) override;

  private:
    string* data_{nullptr};
};

}  // namespace pbs

#include "string_writer_impl.h"
