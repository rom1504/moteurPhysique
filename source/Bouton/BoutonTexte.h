#ifndef DEF_BOUTONTEXTE
#define DEF_BOUTONTEXTE

#include "Bouton.h"

class BoutonTexte : public Bouton,public sf::Text
{
	public:
	BoutonTexte(const sf::Vector2f position,const sf::Font & police,const std::string texte="Bouton",const float taille=30,const sf::Color & couleur=sf::Color(255, 255, 255),const unsigned long style=sf::Text::Regular);
	bool clicked(const sf::Vector2f positionSouris) const;
};

#endif
