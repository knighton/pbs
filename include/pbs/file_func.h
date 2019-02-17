#pragma once

#include <cstdio>
#include <vector>

#include "func_common.h"

using std::vector;

namespace pbs {

// Proto -> file.
//
// Returns whether the entry was entirely written to file.
template <typename T>
bool WriteOneToFile(const T& proto, FILE* file);

// Protos -> file.
//
// Returns the number of protos written.
template <typename T>
size_t WriteToFile(const vector<T>& protos, FILE* file);

// File -> proto.
template <typename T>
ReadResult ReadOneFromFile(FILE* file, T* proto);

// File -> protos.
//
// Appends to the protos.
//
// Returns whether there is no data left.
template <typename T>
bool ReadFromFile(FILE* file, vector<T>* protos, SequenceReadResult* status);

}  // namespace pbs

#include "file_func_impl.h"
