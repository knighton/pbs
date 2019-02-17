#pragma once

#include <cstring>

#include "crc.h"
#include "string_reader.h"
#include "string_writer.h"

using std::memcpy;

namespace pbs {

template <typename T>
bool WriteToString(const T& proto, string* data) {
    string s;
    proto.SerializeToString(&s);
    size_t index = data->size();
    EntryHeader header;
    header.crc32 = CRC32(s);
    header.size = static_cast<uint32_t>(s.size());
    data->resize(index + sizeof(header) + header.size);
    memcpy(&(*data)[index], &header, sizeof(header));
    index += sizeof(header);
    memcpy(&(*data)[index], s.data(), header.size);
    return true;
}

template <typename T>
size_t WriteToString(const vector<T>& protos, string* data) {
    StringWriter<T> writer(data);
    return writer.Write(protos);
}

template <typename T>
ReadResult ReadFromString(const string& data, size_t* index, T* proto) {
    EntryHeader header;
    if (data.size() < *index) {
        assert(false);
    } else if (data.size() == *index) {
        return ReadResult::END;
    } else if (data.size() < *index + sizeof(header)) {
        return ReadResult::PARTIAL;
    }
    memcpy(&header, &data[*index], sizeof(header));
    *index += sizeof(header);
    if (data.size() < *index + header.size) {
        return ReadResult::PARTIAL;
    }
    string s(header.size, '\0');
    memcpy(&s[0], &data[*index], header.size);
    *index += header.size;
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
bool ReadFromString(const string& data, size_t* index, vector<T>* protos,
                    SequenceReadResult* status) {
    StringReader<T> reader(&data, index);
    return reader.Read(protos, status);
}

}  // namespace pbs
