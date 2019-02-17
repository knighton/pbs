#pragma once

#include <vector>

using std::vector;

namespace pbs {

// PBS file writer abstract base class.
template <typename T>
class Writer {
  public:
    // Initialize with the state we are reading from (string, file, etc).

    // Write one entry to a PBS file, advancing the state.
    //
    // Returns whether entry was successfully written.
    virtual bool Write(const T& proto) = 0;

    // Write a sequence of entries to a PBS file, advancing the state.
    //
    // Returns the number of entries successfully written.
    size_t Write(const vector<T>& protos);
};

}  // namespace pbs

#include "writer_impl.h"
