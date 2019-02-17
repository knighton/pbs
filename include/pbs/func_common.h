#pragma once

#include <cstdint>

namespace pbs {

// Result of parsing one PBS entry.
enum class ReadResult {
    OK = 0,            // Read the PBS entry successfully.
    END = 1,           // Reached the end.  No data left to parse.
    PARTIAL = 2,       // Reached the end.  Incomplete/truncated data present.
    BAD_CHECKSUM = 3,  // Read entry, but checksum failure.
    BAD_PROTO = 4      // Read entry and checksum pass, but proto parse fail.
};

// Result of parsing all PBS entries.
struct SequenceReadResult {
    // The counts (see ReadResult).
    uint32_t num_ok{0};            // Number of successfully parsed entries.
    uint32_t num_bad_checksum{0};  // Number of entries with checksum failure.
    uint32_t num_bad_proto{0};     // Number of entries with invalid proto.

    // Reset counts to zeros.
    void Clear();
};

// The header of a PBS entry.
//
// A PBS (protocol buffer sequence) file is a concatenation of PBS entries.
//
// The other part of a PBS entry, coming after the header, is the serialized
// protocol buffer data.
struct __attribute__((packed)) EntryHeader {
    uint32_t crc32;  // CRC32 of the protobuf data.
    uint32_t size;   // Length of the protobuf data.
};

}  // namespace pbs

#include "func_common_impl.h"
