#pragma once

#include <vector>
#include <cstring>

#include "TCPHeader.h"

// Unit of data transferred through a network
// Consists of header and data(payload)
class TCPSegment
{
public:
    TCPHeader header;

    std::vector<uint8_t> payload;

    std::vector<uint8_t> serialize() const
    {
        size_t header_length = header.data_offset * 4;
        std::vector<uint8_t> buffer(header_length + payload.size());

        // Serialize header
        header.serialize(buffer.data());

        // Serialize payload at the end
        if (!payload.empty())
        {
            std::memcpy(buffer.data() + header_length, payload.data(), payload.size());
        }
        return buffer;
    }

    void deserialize(const uint8_t* buffer, size_t length)
    {
        if (length < 20)
        {
            throw std::runtime_error("TCP Header must be at least 20 bytes");
        }

        // TODO
        // header.deserialize(buffer)

        size_t header_length = header.data_offset * 4;
        if (length < header_length)
        {
            throw std::runtime_error("Invalid data_offset");
        }

        size_t payload_size = length - header_length;
        payload.resize(payload_size);

        std::memcpy(payload.data(), buffer + header_length, payload_size);
    }

    size_t size() const
    {
        return (header.data_offset * 4) + payload.size();
    }
};

