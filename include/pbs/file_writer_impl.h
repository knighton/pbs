namespace pbs {

template <typename T>
FileWriter<T>::FileWriter(FILE* file) {
    file_ = file;
}

template <typename T>
bool FileWriter<T>::WriteOne(const T& proto) {
    return WriteToFile(proto, file_);
}

}  // namespace pbs
