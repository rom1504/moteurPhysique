#include "BoutonImage.h"

BoutonImage::BoutonImage(const sf::Vector2f position,const sf::Vector2f taille,const sf::Texture & image) : Bouton(position),Sprite(image)
{
	setPosition(position);
	setScale(taille.x/getGlobalBounds().width,taille.y/getGlobalBounds().height);
}

bool BoutonImage::clicked(const sf::Vector2f positionSouris) const
{
    return sf::FloatRect(positionSouris.x,positionSouris.y,1,1).intersects(getGlobalBounds());
}
