#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>

class Network
{
public:
    Network();
private:
    sf::UdpSocket sock;
    sf::IpAddress ip;

};

#endif // NETWORK_H
