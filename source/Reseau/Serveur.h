#ifndef DEF_SERVEUR
#define DEF_SERVEUR

#include <vector>
#include <SFML/Network.hpp>
#include <iostream>

class Serveur
{
	public://methodes publiques
	Serveur();
	void Run();
	
	private:
	sf::SocketSelector m_selector;
	sf::TcpListener m_listener;
	std::vector<sf::TcpSocket *> m_client;
};

#endif
