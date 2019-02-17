#pragma once

#include <vector>

#include "func_common.h"

using std::vector;

namespace pbs {

// Proto -> buffer.
//
// Advances the data pointer.
//
// Returns whether the proto could be fit into the buffer.
template <typename T>
bool WriteToBuffer(const T& proto, char** data, const char* data_end);

// Protos -> buffer.
//
// Returns the number of protos that could be fit into the buffer.
template <typename T>
size_t WriteToBuffer(const vector<T>& protos, char** data,
                     const char* data_end);

// Buffer -> proto.
//
// Advances the data pointer.
template <typename T>
ReadResult ReadFromBuffer(const char** data, const char* data_end, T* proto);

// Buffer -> protos.
//
// Advances the data pointer.  Appends to the protos.
//
// Returns whether there is no data left.
template <typename T>
bool ReadFromBuffer(const char** data, const char* data_end, vector<T>* protos,
                    SequenceReadResult* status);

}  // namespace pbs

#include "buffer_func_impl.h"
