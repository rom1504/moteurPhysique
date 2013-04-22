#ifndef DEF_UNITE
#define DEF_UNITE

#include "ObjetMobile.h"
#include "Batiment.h"
#include <iostream>

class Unite : public ObjetMobile
{
	public:
	Unite(const sf::Texture & image,const sf::Texture & imageBatiment,float x,float y,float w,float h,float vitesse,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero=-1);
	
	private://methodes privées diverses
	virtual void aFinitDeSeDeplacer();
	
	protected:
	virtual void agirVraiment(Tache tache);
	
	private://attributs divers
	const sf::Texture & m_imageBatiment;
	bool m_construire;
};

#endif
