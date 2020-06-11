#include "network.h"

#include <iostream>



Network::Network()
{
    sf::IpAddress ip_;
    std::cout<<"Your ip :"<<sf::IpAddress::getLocalAddress()<<std::endl;
    std::cout<<"Entrer your friend's IP address:"<<std::endl;
    std::cin>>ip_;
    ip=ip_;
    std::cout<<ip<<std::endl;

    sock.setBlocking(false);
    if (sock.bind(port)!= sf::Socket::Done )
    {
        std::cerr<<"error"<<std::endl;
    }

    sock1.setBlocking(false);
    if (sock1.bind(port_distance)!= sf::Socket::Done )
    {
        std::cerr<<"error"<<std::endl;
    }
}

void Network::seting_host()
{
//    unsigned short temporary=port;
//    port=sender_port;
//    sender_port=temporary;

//    temporary=port_distance;
//    port_distance=sender_port_distance;
//    sender_port_distance=temporary;

//    std::cout<<port<<std::endl;
    std::swap(port,sender_port);
    std::swap(port_distance,sender_port_distance);

    sock.unbind();
    sock1.unbind();
    if (sock.bind(port)!= sf::Socket::Done )
    {
        std::cerr<<"error"<<std::endl;
    }
    if (sock1.bind(port_distance)!= sf::Socket::Done )
    {
        std::cerr<<"error"<<std::endl;
    }
}

void Network::Send()
{
    char buffer[]="HI, I'm Kuba. Let's go?";
    std::cout<<sizeof (buffer)<<std::endl;
    if(sock.send(buffer,sizeof (buffer),ip,sender_port)!= sf::Socket::Done)
    {
        std::cerr<<"error"<<std::endl;
    }

}

void Network::Send_pos(sf::Vector3f &eye,float &rot)
{

    pack<<eye.x<<eye.y<<eye.z<<rot;
    if(sock.send(pack,ip,sender_port)==sf::Socket::Done)
    {
        pack.clear();
    }

}

void Network::Send_distance(const int &distance,sf::Vector3f &pos_e)
{
    pack<<distance<<pos_e.x<<pos_e.y<<pos_e.z;
    if(sock1.send(pack,ip,sender_port_distance)==sf::Socket::Done)
    {
        pack.clear();
    }
}

void Network::Receive()
{

    sock.setBlocking(true);
    char data[100];

    std::size_t received;

    if (sock.receive(data, 100, received, ip, port) != sf::Socket::Done)
    {
        std::cerr<<"Error - data reception"<<std::endl;
    }
    std::cout<<data<<std::endl;
    sock.setBlocking(false);

}

sf::Vector3f Network::Receive_pos(sf::Vector3f &fr_eye,float &rot)
{


    if(sock.receive(pack,ip,port)!=sf::Socket::NotReady)
        if(pack>>fr_eye.x>>fr_eye.y>>fr_eye.z>>rot)
        {
            pack.clear();
        }

    return fr_eye;
}

int Network::Receive_distance(sf::Vector3f &pos_e)
{
    int temp_distance=0;
    if(sock1.receive(pack,ip,port_distance)!=sf::Socket::NotReady)
        if(pack>>temp_distance>>pos_e.x>>pos_e.y>>pos_e.z)
        {
            pack.clear();
        }

    return temp_distance;
}
