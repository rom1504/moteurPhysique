#include "BoutonImage.h"

BoutonImage::BoutonImage(const sf::Vector2f position,const sf::Texture & image) : Bouton(position),Sprite(image)
{
	setPosition(position);
}

bool BoutonImage::clicked(const sf::Vector2f positionSouris) const
{
// 	std::cout<<positionSouris.x<<" "<<positionSouris.y<<" "<<getPosition().x<<" "<<getPosition().y<<std::endl; // pb de position
// 	std::cout<<sf::FloatRect(positionSouris.x,positionSouris.y,1,1).intersects(rectangleFDeSprite(*this))<<std::endl;

	return sf::FloatRect(positionSouris.x,positionSouris.y,1,1).intersects(rectangleFDeSprite(*this));
}
