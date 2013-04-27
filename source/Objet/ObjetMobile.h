#ifndef DEF_OBJETMOBILE
#define DEF_OBJETMOBILE

#include "Objet.h"
#include <iostream>

class ObjetMobile : virtual public Objet
{
	public:
	ObjetMobile(const sf::Texture & image,float x,float y,float w,float h,float vitesse,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero=-1);
	
    const sf::Vector2f destination() const;
	
	protected:
	void allerA(float x,float y);// pour le passage des images en paramètre du constructeur : assez absurde : il faudrait voir pour gérer ça avec le gestionnaire de ressource ou un truc de ce genre
	void allerA(sf::Vector2f destination);
	virtual void agirVraiment(Tache tache);
	virtual void continuerAAgirVraiment();
	void deplacer();
	virtual void aFinitDeSeDeplacer();
    bool m_seDeplace;
	virtual std::map<std::string,std::string> toStringMap() const;
	
	private://attributs divers
    sf::Vector2f m_destination;
    float m_vitesse;//en pixel par seconde
};

#endif
