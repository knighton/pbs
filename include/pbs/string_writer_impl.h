#include "string_func.h"

namespace pbs {

template <typename T>
StringWriter<T>::StringWriter(string* data) {
    data_ = data;
}

template <typename T>
bool StringWriter<T>::WriteOne(const T& proto) {
    return WriteToString(proto, data_);
}

}  // namespace pbs
