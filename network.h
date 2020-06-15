#ifndef NETWORK_H
#define NETWORK_H


#include <SFML/Network.hpp>


class Network
{
public:
    Network();
    void set_ip();
    void Send();
    void Send_pos(sf::Vector3f &eye,float &rot);
    void Receive();
    sf::Vector3f Receive_pos(sf::Vector3f &fr_eye,float &rot);
    int Receive_distance(sf::Vector3f &pos_e);
    void Send_distance(const int &distance,sf::Vector3f &pos_e);
    void seting_host();
private:
    sf::Packet pack;
    sf::UdpSocket sock;
    sf::UdpSocket sock1;
    sf::IpAddress ip="192.168.0.102";
    unsigned short port=56000;
    unsigned short sender_port=54000;
    unsigned short port_distance=52000;
    unsigned short sender_port_distance=50000;
};

#endif // NETWORK_H
