#ifndef DEF_CLIENT
#define DEF_CLIENT

#include <vector>
#include <string>
#include <SFML/System.hpp> 
#include <SFML/Network.hpp>
#include "../Objet/Objet.h"
#include "../Objet/ObjetMobile.h"
#include "../Objet/Batiment.h"
#include <iostream>

class Client
{
	public://methodes publiques
	Client(std::vector<Objet*> & objets,sf::Texture & imageMobile,sf::Texture & imageBatiment,std::string proprietaire);
	void Run();
	void envoyer(std::string proprietaire,sf::Int8 numero,sf::Vector2f position);
	void envoyerObjet(Objet * objet);
	
	private:
	sf::IpAddress m_serverAddress;
	sf::TcpSocket m_socket;
	bool m_connecte;
	std::vector<Objet*> & m_objets;
	sf::Texture m_imageMobile;
	sf::Texture m_imageBatiment;
	std::string m_proprietaire;
};

#endif
