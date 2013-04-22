#ifndef DEF_BOUTONIMAGE
#define DEF_BOUTONIMAGE

#include "Bouton.h"
#include <iostream>

class BoutonImage : public Bouton,public sf::Sprite
{
	public:
	BoutonImage(const sf::Vector2f position,const sf::Vector2f taille,const sf::Texture & image);
	bool clicked(const sf::Vector2f positionSouris) const;
	
};

#endif
