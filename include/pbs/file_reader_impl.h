#include "file_func.h"

namespace pbs {

template <typename T>
FileReader<T>::FileReader(FILE* file) {
    file_ = file;
}

template <typename T>
ReadResult FileReader<T>::ReadOne(T* proto) {
    return ReadOneFromFile(file_, proto);
}

}  // namespace pbs
