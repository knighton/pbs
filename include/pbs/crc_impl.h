#include "CRC.h"

namespace pbs {

uint32_t CRC32(const char* data, size_t data_len) {
    return CRC::Calculate(data, data_len, CRC::CRC_32());
}

uint32_t CRC32(const string& data) {
    return CRC::Calculate(data.data(), data.size(), CRC::CRC_32());
}

}  // namespace pbs
