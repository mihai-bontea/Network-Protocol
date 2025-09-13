#include <iostream>

#include "TCPConnection.h"

class MockNetwork
{
public:
    TCPConnection& client;
    TCPConnection& server;

    MockNetwork(TCPConnection& c, TCPConnection& s)
            : client(c), server(s) {}

    void send_from_client(const TCPSegment& seg)
    {
        auto resp = server.receive(seg);
        if (resp.size() > 0)
        {
            auto back = client.receive(resp);
            if (back.size() > 0) server.receive(back);
        }
    }

    void send_from_server(const TCPSegment& seg)
    {
        auto resp = client.receive(seg);
        if (resp.size() > 0)
        {
            auto back = server.receive(resp);
            if (back.size() > 0) client.receive(back);
        }
    }
};

int main()
{
    TCPConnection client(1000, 2000);
    TCPConnection server(2000, 1000);
    MockNetwork net(client, server);

    auto syn = client.initiate_connection();
    net.send_from_client(syn);

    std::cout << "Client state: "
              << (client.get_state() == TCPConnection::State::ESTABLISHED ? "ESTABLISHED" : "NOT ESTABLISHED") << "\n";
    std::cout << "Server state: "
              << (server.get_state() == TCPConnection::State::ESTABLISHED ? "ESTABLISHED" : "NOT ESTABLISHED") << "\n";

    auto msg = client.send_data("TCP is working!");
    net.send_from_client(msg);

    std::cout << "Server received: " << server.read_data() << "\n";
    return 0;
}