#pragma once

#include <vector>

#include "TCPHeader.h"

// Unit of data transferred through a network
// Consists of header and data(payload)
class TCPSegment
{
public:
    TCPHeader header;

    std::vector<uint8_t> payload;
};

