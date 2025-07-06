#pragma once

#include <cstdint>

// TCP uses 16-bit checksum over header, data, and pseudo-header
class ChecksumCalculator
{
    static uint16_t compute(const uint8_t* data, size_t length)
    {
        uint16_t result = 0;
        return result;
    }
};