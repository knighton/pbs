#pragma once

#include "string_func.h"

namespace pbs {

template <typename T>
StringReader<T>::StringReader(const string* data, size_t* index) {
    data_ = data;
    index_ = index;
}

template <typename T>
ReadResult StringReader<T>::Read(T* proto) {
    return ReadFromString(*data_, index_, proto);
}

}  // namespace pbs
