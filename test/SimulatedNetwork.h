#pragma once

#include <vector>
#include <queue>
#include <cstdint>

class SimulatedNetwork
{
public:
    struct Packet
    {
        std::vector<uint8_t> data;
    };

    void send_packet(const uint8_t* data, size_t length)
    {
        Packet packet;
        packet.data.assign(data, data + length);
        sent_packets.push(packet);
    }

    bool has_packet() const
    {
        return !sent_packets.empty();
    }

    Packet pop_packet()
    {
        const auto packet = sent_packets.front();
        sent_packets.pop();
        return packet;
    }

private:
    std::queue<Packet> sent_packets;
};