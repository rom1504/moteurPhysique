#ifndef DEF_OBJETS
#define DEF_OBJETS

#include <vector>
#include "Objet.h"
#include "ObjetMobile.h"
#include "Batiment.h"

class Objets : public std::vector<Objet*> // inutilisé : inutile ?
{
	public:
	Objets();
	Batiment * ajouterBatiment(float x,float y,std::string proprietaire,sf::Int8 numero=-1);
	ObjetMobile * ajouterObjetMobile(float x,float y,std::string proprietaire,sf::Int8 numero=-1);
	
	private:
	sf::Texture m_imageMobile;
	sf::Texture m_imageBatiment;
};

#endif
