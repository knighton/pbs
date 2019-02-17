#include "buffer_func.h"

namespace pbs {

template <typename T>
BufferReader<T>::BufferReader(const char** data, const char* data_end) {
    data_ = data;
    data_end_ = data_end;
}

template <typename T>
ReadResult BufferReader<T>::ReadOne(T* proto) {
    return ReadOneFromBuffer(data_, data_end_, proto);
}

}  // namespace pbs
