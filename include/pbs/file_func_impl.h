#include <string>

#include "crc.h"
#include "file_reader.h"
#include "file_writer.h"

using std::string;

namespace pbs {

template <typename T>
bool WriteToFile(const T& proto, FILE* file) {
    string data;
    proto.SerializeToString(&data);
    EntryHeader header;
    header.crc32 = CRC32(data);
    header.size = data.size();
    if (fwrite(&header, sizeof(header), 1, file) != 1) {
        return false;
    }
    return fwrite(data.data(), 1, data.size(), file) == data.size();
}

template <typename T>
size_t WriteToFile(const vector<T>& protos, FILE* file) {
    FileWriter<T> writer(file);
    return writer.Write(protos);
}

template <typename T>
ReadResult ReadFromFile(FILE* file, T* proto) {
    EntryHeader header;
    if (feof(file)) {
        return ReadResult::END;
    } else if (!fread(&header, sizeof(header), 1, file)) {
        return ReadResult::PARTIAL;
    }
    string data(header.size, '\0');
    if (fread(&data[0], 1, header.size, file) != header.size) {
        return ReadResult::PARTIAL;
    }
    uint32_t redo_crc32 = CRC32(data);
    if (header.crc32 != redo_crc32) {
        return ReadResult::BAD_CHECKSUM;
    }
    if (!proto->ParseFromString(data)) {
        return ReadResult::BAD_PROTO;
    }
    return ReadResult::OK;
}

template <typename T>
bool ReadFromFile(FILE* file, vector<T>* protos, SequenceReadResult* status) {
    FileReader<T> reader(file);
    return reader.Read(protos, status);
}

}  // namespace pbs
