#pragma once

namespace pbs {

template <typename T>
size_t Writer<T>::Write(const vector<T>& protos) {
    size_t i;
    for (i = 0; i < protos.size(); ++i) {
        if (!Write(protos[i])) {
            break;
        }
    }
    return i;
}

}  // namespace pbs
