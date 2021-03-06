#ifndef DEF_PLANTE
#define DEF_PLANTE
#include "EtreVivant.h"

class Plante : public EtreVivant
{
	
	public:
    Plante(double energie, const double geneCote, const sf::Texture & image, float x, float y, std::vector<Objet*> & objets, std::string proprietaire, sf::Int8 numero=-1);


    double etreMange(double quantiteMange);

	// gènes : constant
	protected:
    void agirAChaqueFois();
    void pousser();
    void seReproduire(Plante * plante);
    void seReproduire(EtreVivant*);
    std::vector<EtreVivant*> etresVivantsPouvantSeReproduire() const;
    std::map<std::string,std::string> toStringMap() const;

    private:
    double m_vitesseCroissance;
		
};


#endif
