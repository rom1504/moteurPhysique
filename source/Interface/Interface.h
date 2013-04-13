#ifndef DEF_INTERFACE
#define DEF_INTERFACE

#include <SFML/Graphics.hpp>
#include "../Bouton/BoutonImage.h"
#include "../Bouton/BoutonTexte.h"
#include "../Objet/Objet.h"
#include <vector>
#include "../Objet/ObjetMobile.h"

class BoutonObjet : public BoutonImage
{
	public:
	BoutonObjet(const sf::Vector2f position,const sf::Texture & image,Objet * objetLie);
	Objet * objetLie();
	
	private:
	Objet * m_objetLie;
};

class Interface
{
	public:
	Interface(sf::RenderWindow * rendu,std::vector<Objet*> & objets,std::string proprietaire);
	void afficher();
	void actualiserSelection();
	bool recevoirEvenement(sf::Event & evenement);
	Objet * objetSelectionne();
	
	private:
	sf::RenderWindow * m_rendu;
	std::vector<Objet*> & m_objets;
	std::vector<BoutonObjet *> m_bouton;
	std::string m_proprietaire;
	Objet * m_objetSelectionne;
	BoutonImage * m_boutonConstruction;
	bool m_construction;
	bool m_boutonObjetMobile;
	sf::Texture m_imageMaison;
};

#endif
