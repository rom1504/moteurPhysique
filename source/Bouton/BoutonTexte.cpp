#include "BoutonTexte.h"

BoutonTexte::BoutonTexte(const sf::Vector2f position,const sf::Font & police,const std::string texte,const float taille,const sf::Color & couleur,const unsigned long style) : Bouton(position),Text(texte,police,taille)
{
	setPosition(position);
	setColor(couleur);
	//SetStyle(style);
}

bool BoutonTexte::clicked(const sf::Vector2f positionSouris) const
{
	return sf::FloatRect(positionSouris.x,positionSouris.y,1,1).intersects(getGlobalBounds());
}
