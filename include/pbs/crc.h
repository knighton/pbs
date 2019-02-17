#pragma once

#include <string>

using std::string;

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wshadow-field-in-constructor"
#pragma clang diagnostic ignored "-Wsign-conversion"
#endif

namespace pbs {

uint32_t CRC32(const char* data, size_t data_len);
uint32_t CRC32(const string& data);

}  // namespace pbs

#include "crc_impl.h"

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
