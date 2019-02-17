#include <cstring>
#include <string>

#include "crc.h"
#include "buffer_reader.h"
#include "buffer_writer.h"

using std::memcpy;
using std::string;

namespace pbs {

template <typename T>
bool WriteToBuffer(const T& proto, char** data, const char* data_end) {
    string s;
    proto.SerializeToString(&s);
    EntryHeader header;
    header.crc32 = CRC32(s);
    header.size = s.size();
    if (data_end < *data + sizeof(header) + s.size()) {
        return false;
    }
    memcpy(*data, &header, sizeof(header));
    *data += sizeof(header);
    memcpy(*data, s.data(), s.size());
    *data += s.size();
    return true;
}

template <typename T>
size_t WriteToBuffer(const vector<T>& protos, char** data,
                     const char* data_end) {
    BufferWriter<T> writer(data, data_end);
    return writer.Write(protos);
}

template <typename T>
ReadResult ReadFromBuffer(const char** data, const char* data_end, T* proto) {
    EntryHeader header;
    if (data_end < *data) {
        assert(false);
    } else if (data_end == *data) {
        return ReadResult::END;
    } else if (data_end < *data + sizeof(header)) {
        return ReadResult::PARTIAL;
    }
    memcpy(&header, *data, sizeof(header));
    *data += sizeof(header);
    if (data_end < *data + header.size) {
        return ReadResult::PARTIAL;
    }
    string s(header.size, '\0');
    memcpy(&s[0], *data, header.size);
    uint32_t redo_crc32 = CRC32(s);
    if (header.crc32 != redo_crc32) {
        return ReadResult::BAD_CHECKSUM;
    }
    if (!proto->ParseFromString(s)) {
        return ReadResult::BAD_PROTO;
    }
    return ReadResult::OK;
}

template <typename T>
bool ReadFromBuffer(const char** data, const char* data_end, vector<T>* protos,
                    SequenceReadResult* status) {
    BufferReader<T> reader(data, data_end);
    return reader.Read(protos, status);
}

}  // namespace pbs
