#ifndef DEF_BOUTON
#define DEF_BOUTON

#include <SFML/Graphics.hpp>

class Bouton
{
	public:
	Bouton(const sf::Vector2f position);
	virtual bool clicked(const sf::Vector2f positionSouris)const =0;
};

#endif
