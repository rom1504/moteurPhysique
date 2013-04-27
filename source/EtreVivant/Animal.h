#ifndef DEF_ANIMAL
#define DEF_ANIMAL
#include "EtreVivant.h"
#include "../Objet/ObjetMobile.h"
#include "Plante.h"

class Animal : public EtreVivant,public ObjetMobile
{
	public:
    Animal(double energie,const double geneVitesseManger,const double geneCote,const double geneVitesse,const sf::Texture & image,float x,float y,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero=-1);

    void manger(Plante * p);

    protected:
    void agirAChaqueFois();
    void agirVraiment(Tache tache);
    void seReproduire(EtreVivant* etreVivant);
    void seReproduire(Animal * animal);
    virtual std::map<std::string,std::string> toStringMap() const;

	protected:
	// gènes : constant
	const double m_geneVitesse;
    const double m_geneVitesseManger;
};


#endif
