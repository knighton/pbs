namespace pbs {

template <typename T>
BufferWriter<T>::BufferWriter(char** data, const char* data_end) {
    data_ = data;
    data_end_ = data_end;
}

template <typename T>
bool BufferWriter<T>::WriteOne(const T& proto) {
    return WriteOneToBuffer(proto, data_, data_end_);
}

}  // namespace pbs
