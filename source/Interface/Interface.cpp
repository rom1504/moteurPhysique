#include "Interface.h"


BoutonObjet::BoutonObjet(const sf::Vector2f position,const sf::Texture & image,Objet * objetLie) : BoutonImage(position,image),m_objetLie(objetLie)
{
	
}

Objet * BoutonObjet::objetLie()
{
	return m_objetLie;
}

Interface::Interface(sf::RenderWindow * rendu,std::vector<Objet*> & objets,std::string proprietaire) : m_objets(objets)
{
	m_rendu=rendu;
	m_proprietaire=proprietaire;
	sf::Image tempImgMaison;
	tempImgMaison.loadFromFile("image/maison.png");
	tempImgMaison.createMaskFromColor(sf::Color(255,255,255));
	m_imageMaison.loadFromImage(tempImgMaison);
	m_boutonConstruction=new BoutonImage(sf::Vector2f(605,555),m_imageMaison);
	m_boutonConstruction->setScale(20/m_boutonConstruction->getLocalBounds().width,20/m_boutonConstruction->getLocalBounds().height);
	m_boutonObjetMobile=false;
	m_construction=0;
}

void Interface::actualiserSelection()
{
	m_construction=false;
	m_bouton.clear();
	BoutonObjet * boutonTemp;
	sf::Vector2f position;
	position.x=20;
	position.y=550;
	sf::Vector2f echelle;
	echelle.x=0.5;
	echelle.y=0.5;
	bool premier=true;
	for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i) if((*i)->selectionne() && (*i)->proprietaire()==m_proprietaire) 
	{
		boutonTemp=new BoutonObjet(position,*((*i)->sprite().getTexture()),*i);
		boutonTemp->scale(echelle);
		m_bouton.push_back(boutonTemp);
		if(position.x>=380)
		{
			position.x=20;
			position.y+=20;
		}
		else position.x+=20;
		if(premier && boutonTemp->objetLie()->type()==0)
		{
			premier=false;
			m_objetSelectionne=boutonTemp->objetLie();
		}
	}
	m_boutonObjetMobile=!premier;
}

bool Interface::recevoirEvenement(sf::Event & evenement)
{
	sf::Vector2i positionSourisEcrani=sf::Mouse::getPosition();
	sf::Vector2f positionSourisEcran=sf::Vector2f(positionSourisEcrani);
	if(evenement.type==sf::Event::MouseButtonReleased && evenement.mouseButton.button==sf::Mouse::Left)
	{
		for(std::vector<BoutonObjet*>::iterator i=m_bouton.begin();i!=m_bouton.end();++i) if((*i)->clicked(positionSourisEcran)) 
		{
			m_objetSelectionne=(*i)->objetLie(); // faire une apparance dans le menu pour la selection
			if(m_objetSelectionne->type()!=0) m_boutonObjetMobile=false;
		}
		if(m_boutonConstruction->clicked(positionSourisEcran)) // voir si bien
		{	
			m_construction=true; // bien avancé: écrire ça dans le done list
		}
	}
	
	if(evenement.type==sf::Event::MouseButtonReleased && evenement.mouseButton.button==sf::Mouse::Right && m_construction && positionSourisEcran.y<=550)
	{
		m_objetSelectionne->agirAuClicDroit(m_rendu->mapPixelToCoords(positionSourisEcrani),sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift),1);// vérifier que ça peut pas arriver pour un batiment
		if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))) m_construction=false;
		return true;
	}
	return false;
}

Objet * Interface::objetSelectionne()
{
	return m_objetSelectionne;
}

void Interface::afficher()
{
	sf::RectangleShape l1;
	l1.setPosition(0,550);
	l1.setSize(sf::Vector2f(800,550));
	l1.setFillColor(sf::Color::White);
	m_rendu->draw(l1);
	sf::RectangleShape r;
	r.setPosition(0,550);
	r.setSize(sf::Vector2f(800,50));
	r.setFillColor(sf::Color(200,200,200));
	m_rendu->draw(r);
	sf::RectangleShape l2;
	l2.setPosition(600,550);
	l2.setSize(sf::Vector2f(600,600));
	l2.setFillColor(sf::Color::White);
	m_rendu->draw(l2);
	if(m_boutonObjetMobile) m_rendu->draw(*m_boutonConstruction);
	for(std::vector<BoutonObjet*>::iterator i=m_bouton.begin();i!=m_bouton.end();++i)
	{	
		if((*i)->objetLie()==m_objetSelectionne)
		{
			sf::RectangleShape r1;
			r1.setPosition((*i)->getPosition().x-1,(*i)->getPosition().y-1);
			r1.setSize(sf::Vector2f((*i)->getGlobalBounds().width+1,(*i)->getGlobalBounds().height+1));
			r1.setFillColor(sf::Color(255,255,255,0));
			r1.setOutlineColor(sf::Color(0,0,255));
			m_rendu->draw(r1);
		}
		m_rendu->draw(**i);
	}
}
