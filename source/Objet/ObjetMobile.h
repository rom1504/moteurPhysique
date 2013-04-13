#ifndef DEF_OBJETMOBILE
#define DEF_OBJETMOBILE

#include "Objet.h"
#include "Batiment.h"
#include <iostream>

class ObjetMobile : public Objet
{
	public:
	ObjetMobile(const sf::Texture & image,const sf::Texture & imageBatiment,float x,float y,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero=-1);
	
	const sf::Vector2f destination() const;
	
	protected:
	virtual void agirVraiment(Tache tache);
	virtual void continuerAAgirVraiment();
	void allerA(float x,float y);// pour le passage des images en paramètre du constructeur : assez absurde : il faudrait voir pour gérer ça avec le gestionnaire de ressource ou un truc de ce genre
	void allerA(sf::Vector2f destination);
	
	private://methodes privées diverses
	void deplacer();
	void aFinitDeSeDeplacer();
	
	private://attributs divers
	sf::Vector2f m_destination;
	bool m_seDeplace;
	float m_vitesse;//en pixel par seconde
	sf::Clock m_horloge;
	const sf::Texture & m_imageBatiment;
	bool m_construire;
};

#endif
