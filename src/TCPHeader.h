#pragma once

#include <cstdint>

class TCPHeader
{
public:
    uint16_t source_port, destination_port;
    uint32_t sequence_number, acknowledgment_number;

    uint8_t data_offset;
    uint8_t reserved;
    uint16_t flags;

    uint16_t window_size, checksum, urgent_pointer;

    void serialize(uint8_t* buffer) const
    {
        write16(buffer, source_port);
        write16(buffer + 2, destination_port);
        write32(buffer + 4, sequence_number);
        write32(buffer + 8, acknowledgment_number);

        uint8_t offset_reserved = (data_offset << 4) | (reserved & 0x07);
        buffer[12] = offset_reserved;
        buffer[13] = flags & 0xFF;

        write16(buffer + 14, window_size);
        write16(buffer + 16, checksum);
        write16(buffer + 18, urgent_pointer);
    }

    void deserialize(const uint8_t* buffer)
    {
        source_port = (buffer[0] << 8) | buffer[1];
        destination_port = (buffer[2] << 8) | buffer[3];
        sequence_number = (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | buffer[7];
        acknowledgment_number = (buffer[8] << 24) | (buffer[9] << 16) | (buffer[10] << 8) | buffer[11];

        uint8_t offset_reserved = buffer[12];
        data_offset = offset_reserved >> 4;
        reserved = (offset_reserved >> 1) & 0x07;

        flags = buffer[13];
        window_size = (buffer[14] << 8) | buffer[15];
        checksum = (buffer[16] << 8) | buffer[17];
        urgent_pointer = (buffer[18] << 8) | buffer[19];
    }
private:
    static void write16(uint8_t* buffer, uint16_t value)
    {
        buffer[0] = value >> 8;
        buffer[1] = value & 0xFF;
    }

    static void write32(uint8_t* buffer, uint32_t value)
    {
        buffer[0] = value >> 24;
        buffer[1] = (value >> 16) & 0xFF;
        buffer[2] = (value >> 8) & 0xFF;
        buffer[3] = value & 0xFF;
    }
};