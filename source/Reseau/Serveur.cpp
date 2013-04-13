#include "Serveur.h"

Serveur::Serveur()
{

}

void Serveur::Run()
{
	if (m_listener.listen(13429)!=sf::Socket::Done) return;
	m_selector.add(m_listener);
	while(true)
	{
		if(m_selector.wait())
		{
			if (m_selector.isReady(m_listener))
			{
				sf::TcpSocket * client=new sf::TcpSocket;
				if(m_listener.accept(*client) == sf::Socket::Done)
				{
					m_selector.add(*client);
					m_client.push_back(client);
					//m_client.first().Send(packet);
					//std::cout<<"Connection";
				}
			}
			else
			{
				 for (std::vector<sf::TcpSocket*>::iterator it = m_client.begin(); it != m_client.end(); ++it)
				 {
					if(m_selector.isReady(*(*it)))
					{
						sf::Packet packet;
						if ((*it)->receive(packet)==sf::Socket::Done)
						{
							for(std::vector<sf::TcpSocket*>::iterator i=m_client.begin();i!=m_client.end();++i) if((*i)!=(*it)) (*i)->send(packet);
						}
						//else // ???? ( si c'est bien dans ce cas remettre )
						//{
						//	m_selector.Remove(socket);
						//	for(std::vector<sf::TcpSocket>::iterator i=m_client.begin();i!=m_client.end();++i) if((*i)==socket) {m_client.erase(i);break;}
						//}
					}
				}
			}
		}
	}
}
