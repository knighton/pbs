#pragma once

namespace pbs {

template <typename T>
Writer<T>::~Writer() {
}

template <typename T>
size_t Writer<T>::Write(const vector<T>& protos) {
    size_t i;
    for (i = 0; i < protos.size(); ++i) {
        if (!WriteOne(protos[i])) {
            break;
        }
    }
    return i;
}

}  // namespace pbs
