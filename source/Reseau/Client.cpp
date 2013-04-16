#include "Client.h"

Client::Client(std::vector<Objet*> & objets,sf::Texture & imageMobile,sf::Texture & imageBatiment,std::string proprietaire) :m_connecte(false),m_objets(objets),m_imageMobile(imageMobile),m_imageBatiment(imageBatiment),m_proprietaire(proprietaire)
{
	
}

void Client::Run()
{
// 	m_serverAddress=sf::IpAddress("127.0.0.1");
// 	m_connecte=false;
// 	if (m_socket.connect(m_serverAddress,13429)!=sf::Socket::Done) return;
// 	sf::Packet packetRecu;
// 	std::string proprietaire;
// 	sf::Int8 numero;
// 	sf::Vector2f position,destination;
// 	sf::Int8 type,type2;
// 	m_connecte=true;
// 	Objet * nouveau;
// 	bool existe=false;
// 	while(m_connecte)
// 	{
// 		if((m_connecte=(m_socket.receive(packetRecu)==sf::Socket::Done)))
// 		{
// 			if(packetRecu>>type>>proprietaire>>numero && proprietaire!=m_proprietaire)
// 			{
// 				if(type==0) {if(packetRecu>>position.x>>position.y) for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i) {if((*i)->proprietaire()==proprietaire && (*i)->numero()==numero) {(*i)->agirAuClicDroit(position,0,0); break;}}}
// 				else if(type==1) if(packetRecu>>type2>>position.x>>position.y)
// 				{
// 					for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i) {if((*i)->proprietaire()==proprietaire && (*i)->numero()==numero) {existe=true; break;}} // empêche de créer un objet existant déjà, il faudra ensuite faire que ça modifie l'existant pour pouvoir synchroniser
// 					if(!existe)
// 					{
// 						if(type2==0)
// 						{
// 							packetRecu>>destination.x>>destination.y;
// 							nouveau=new ObjetMobile(m_imageMobile,m_imageBatiment,position.x,position.y,m_objets,proprietaire,numero);
// 							nouveau->agirAuClicDroit(destination,0,0);
// 						}
// 						else if(type2==1) nouveau=new Batiment(m_imageBatiment,position.x,position.y,m_objets,proprietaire,m_imageMobile,numero);
// 						m_objets.push_back(nouveau);
// 					}
// 				}
// 			}
// 			proprietaire="";
// 		}
// 		existe=false;
// 	}
}

void Client::envoyer(std::string proprietaire,sf::Int8 numero,sf::Vector2f position)
{
// 	if(m_connecte)
// 	{
// 		sf::Packet packet;
// 		sf::Int8 type=0;
// 		packet<<type<<proprietaire<<numero<<position.x<<position.y;
// 		m_connecte=(m_socket.send(packet)==sf::Socket::Done);
// 	}
}

void Client::envoyerObjet(Objet * objet)
{
// 	if(m_connecte)
// 	{
// 		sf::Packet packet;
// 		sf::Int8 type=1;
// 		packet<<type<<objet->proprietaire()<<objet->numero()<<objet->type()<<objet->sprite().getPosition().x<<objet->sprite().getPosition().y;
// 		if(objet->type()==0) packet<<(dynamic_cast<ObjetMobile*>(objet))->destination().x<<(dynamic_cast<ObjetMobile*>(objet))->destination().y;
// 		m_connecte=(m_socket.send(packet)==sf::Socket::Done);
// 	}
}
