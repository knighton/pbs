#pragma once

#include <string>
#include <vector>

#include "func_common.h"

using std::string;
using std::vector;

namespace pbs {

// Proto -> string.
//
// Appends to the string.
//
// Returns whether successful.
template <typename T>
bool WriteOneToString(const T& proto, string* data);

// Protos -> string.
//
// Appends to the string.
//
// Returns the number of protos written.
template <typename T>
size_t WriteToString(const vector<T>& protos, string* data);

// String -> proto.
//
// Advances the index.
template <typename T>
ReadResult ReadOneFromString(const string& data, size_t* index, T* proto);

// String -> protos.
//
// Advances the index.  Appends to the protos.
//
// Returns whether there is no data left.
template <typename T>
bool ReadFromString(const string& data, size_t* index, vector<T>* protos,
                    SequenceReadResult* status);

}  // namespace pbs

#include "string_func_impl.h"
