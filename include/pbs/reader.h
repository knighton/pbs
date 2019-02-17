#pragma once

#include <vector>

#include "func_common.h"

using std::vector;

namespace pbs {

// PBS file reader abstract base class.
template <typename T>
class Reader {
  public:
    // Initialize with the state we are reading from (string, file, etc).
    virtual ~Reader();

    // Read one PBS entry, advancing the state.
    //
    // Sets "proto" on success.
    //
    // Returns a status enum, which is nonzero on failure.
    virtual ReadResult Read(T* proto) = 0;

    // Read all PBS entries to the end.
    //
    // Appends parsed protobufs to "protos".  Tracks statistics on the results
    // of each PBS entry read in "result".
    //
    // Returns whether there is no partial data left when done.
    bool Read(vector<T>* protos, SequenceReadResult* result);
};

}  // namespace pbs

#include "reader_impl.h"
