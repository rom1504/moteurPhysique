#include "Interface.h"


BoutonObjet::BoutonObjet(const sf::Vector2f position,const sf::Vector2f taille,const sf::Texture & image,Objet * objetLie) : BoutonImage(position,taille,image),m_objetLie(objetLie)
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
	m_boutonConstruction=new BoutonImage(sf::Vector2f(605,555),sf::Vector2f(20,20),m_imageMaison);
	m_boutonObjetMobile=false;
	m_construction=0;
    m_police.loadFromFile("police/arial.ttf");
    m_objetSelectionne=NULL;
}

void Interface::actualiserSelection()
{
	m_construction=false;
	m_bouton.clear();
	BoutonObjet * boutonTemp;
	sf::Vector2f position;
	position.x=20;
	position.y=550;
	bool premier=true;
    for(Objet * o : m_objets) if(o->selectionne() && o->proprietaire()==m_proprietaire)
	{
        boutonTemp=new BoutonObjet(position,sf::Vector2f(20,20),*(o->texture()),o);
		m_bouton.push_back(boutonTemp);
		if(position.x>=380)
		{
			position.x=20;
			position.y+=20;
		}
		else position.x+=20;
        if(premier)
        {
            premier=false;
            m_objetSelectionne=boutonTemp->objetLie();
        }
	}
    m_boutonObjetMobile=!premier && m_objetSelectionne->type()==0;
    if(premier) m_objetSelectionne=NULL;
}

bool Interface::recevoirEvenement(sf::Event & evenement)
{
	sf::Vector2i positionSourisEcrani=sf::Mouse::getPosition(*m_rendu);
	sf::Vector2f positionSourisEcran=sf::Vector2f(positionSourisEcrani);
	if(evenement.type==sf::Event::MouseButtonReleased && evenement.mouseButton.button==sf::Mouse::Left)
	{
        for(BoutonObjet * b : m_bouton) if(b->clicked(positionSourisEcran))
		{
            m_objetSelectionne=b->objetLie(); // faire une apparance dans le menu pour la selection
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
    for(BoutonObjet * b : m_bouton)
	{	
        if(b->objetLie()==m_objetSelectionne)
		{
			sf::RectangleShape r1;
            r1.setPosition(b->getPosition().x-1,b->getPosition().y-1);
            r1.setSize(sf::Vector2f(b->getGlobalBounds().width+1,b->getGlobalBounds().height+1));
			r1.setFillColor(sf::Color(255,255,255,0));
			r1.setOutlineColor(sf::Color(0,0,255));
			m_rendu->draw(r1);
		}
        m_rendu->draw(*b);
	}
    if(m_objetSelectionne!=NULL)
    {
       BoutonTexte * bt=new BoutonTexte(sf::Vector2f(550,200),m_police,m_objetSelectionne->toString(),15);
       m_rendu->draw(*bt);
    }
}
