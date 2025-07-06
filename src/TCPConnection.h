#pragma once

#include <functional>
#include <vector>
#include <cstdint>

#include "TCPHeader.h"

class TCPConnection
{
public:
    using SenderFunction = std::function<void(const uint8_t*, size_t)>;

    TCPConnection(uint16_t source_port,
                  uint16_t destination_port,
                  SenderFunction sender)
                  : source_port(source_port)
                  , destination_port(destination_port)
                  , sequence_number(0)
                  , sender(sender)
    {}

    void send_sync()
    {
        // Add TCP header
        // set the ports
        // set the flags

        uint8_t buffer[200];
        // header.serialize(buffer);

        sender(buffer, 200);
    }

private:
    uint16_t source_port, destination_port;
    uint32_t sequence_number;

    SenderFunction sender;
};