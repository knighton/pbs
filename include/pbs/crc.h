#pragma once

#include <string>

using std::string;

namespace pbs {

uint32_t CRC32(const char* data, size_t data_len);
uint32_t CRC32(const string& data);

}  // namespace pbs

#include "crc_impl.h"
