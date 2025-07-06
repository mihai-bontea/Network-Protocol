#pragma once

#include <cstdint>

class TCPHeader
{
public:
    // TODO: add all the header values
    uint16_t source_port, destination_port;
    uint32_t sequence_number;

    uint8_t flags;

    void serialize(uint8_t* buffer) const
    {

    }
private:
    static void write16(uint8_t* buffer, uint16_t value)
    {

    }

    static void write32(uint8_t* buffer, uint32_t value)
    {

    }
};