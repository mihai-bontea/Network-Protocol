#include <deque>

#include "TCPSegment.h"

class TCPConnection
{
public:
    enum class State { CLOSED, SYN_SENT, SYN_RECEIVED, ESTABLISHED, FIN_WAIT };

private:
    State state = State::CLOSED;
    uint16_t source_port;
    uint16_t destination_port;
    std::deque<uint8_t> recv_buffer;

public:
    TCPConnection(uint16_t source_port, uint16_t destination_port)
            : source_port(source_port), destination_port(destination_port) {}

    State get_state() const { return state; }

    TCPSegment initiate_connection()
    {
        state = State::SYN_SENT;
        TCPSegment seg;
        seg.header.source_port = source_port;
        seg.header.destination_port = destination_port;
        seg.header.flags = TCPHeader::SYN;
        return seg;
    }

    TCPSegment receive(const TCPSegment& seg)
    {
        TCPSegment response;
        response.header.source_port = source_port;
        response.header.destination_port = destination_port;

        if (seg.header.flags & TCPHeader::SYN && state == State::CLOSED)
        {
            state = State::SYN_RECEIVED;
            response.header.flags = TCPHeader::SYN | TCPHeader::ACK;
            return response;
        }
        if (seg.header.flags & TCPHeader::SYN && state == State::SYN_SENT)
        {
            state = State::ESTABLISHED;
            response.header.flags = TCPHeader::ACK;
            return response;
        }
        if (seg.header.flags & TCPHeader::ACK && state == State::SYN_RECEIVED)
        {
            state = State::ESTABLISHED;
            return {};
        }
        if (state == State::ESTABLISHED && !seg.payload.empty())
        {
            recv_buffer.insert(recv_buffer.end(),
                               seg.payload.begin(), seg.payload.end());
            response.header.flags = TCPHeader::ACK;
            return response;
        }
        return {};
    }

    TCPSegment send_data(const std::string& msg)
    {
        TCPSegment seg;
        seg.header.source_port = source_port;
        seg.header.destination_port = destination_port;
        seg.header.flags = 0;
        seg.payload.assign(msg.begin(), msg.end());
        return seg;
    }

    std::string read_data()
    {
        std::string data(recv_buffer.begin(), recv_buffer.end());
        recv_buffer.clear();
        return data;
    }
};