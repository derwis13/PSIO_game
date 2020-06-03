#include "network.h"

#include <iostream>

Network::Network()
{


    // Create a socket and bind it to the port 55001
    sf::UdpSocket socket;
    socket.bind(55001);
    // Send a message to 192.168.0.100 on port 55002
    std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
    socket.send(message.c_str(), message.size() + 1, "192.168.0.104", 55002);
    // Receive an answer (most likely from 192.168.0.104, but could be anyone else)
    char buffer[1024];
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    socket.receive(buffer, sizeof(buffer), received, sender, port);
    std::cout << sender.toString() << " said: " << buffer << std::endl;
    // ----- The server -----
    // Create a socket and bind it to the port 55002
    sf::UdpSocket socket1;
    socket1.bind(55002);
    // Receive a message from anyone

    socket1.receive(buffer, sizeof(buffer), received, sender, port);
    std::cout << sender.toString() << " said: " << buffer << std::endl;
    // Send an answer
    std::string message1 = "Welcome " + sender.toString();
    socket1.send(message.c_str(), message1.size() + 1, sender, port);
}
