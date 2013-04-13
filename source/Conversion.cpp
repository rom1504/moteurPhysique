#include "Conversion.h"

sf::FloatRect rectangleFDeSprite(const sf::Sprite & sprite)
{
	return sprite.getGlobalBounds();
}

sf::IntRect rectangleIDeSprite(const sf::Sprite & sprite)
{
	return sf::IntRect(rectangleFDeSprite(sprite));
}
