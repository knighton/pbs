#include <cassert>

namespace pbs {

template <typename T>
Reader<T>::~Reader() {
}

template <typename T>
bool Reader<T>::Read(vector<T>* protos, SequenceReadResult* result) {
    result->Clear();
    T proto;
    while (true) {
        ReadResult rr = Read(&proto);
        switch (rr) {
            case ReadResult::OK:
                protos->emplace_back(proto);
                ++result->num_ok;
                break;
            case ReadResult::END:
                return true;
            case ReadResult::PARTIAL:
                return false;
            case ReadResult::BAD_CHECKSUM:
                ++result->num_bad_checksum;
                break;
            case ReadResult::BAD_PROTO:
                ++result->num_bad_proto;
                break;
            default:
                assert(false);
        }
    }
}

}  // namespace pbs
