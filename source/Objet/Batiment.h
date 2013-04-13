#ifndef DEF_BATIMENT
#define DEF_BATIMENT

#include "Objet.h"
#include "ObjetMobile.h"

class Batiment : public Objet
{
	public:
	Batiment(const sf::Texture & image,float x,float y,std::vector<Objet*> & objets,std::string proprietaire,const sf::Texture & imageObjetMobileCree,sf::Int8 numero=-1);// là dedans : variable absurde : image,objets,proprietaire,image2,(numero ? ok : autoremplit dans objet : utile quand même dans client peut être ? ? ?... ) et puis mettre x,y en un vector2f
	
	
	protected:
	virtual void agirVraiment(Tache tache);
	void creerObjetMobile(sf::Vector2f position);
	
	private:
	const sf::Texture & m_imageObjetMobileCree;
};

#endif
