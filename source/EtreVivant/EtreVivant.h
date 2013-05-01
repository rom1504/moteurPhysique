#ifndef DEF_ETREVIVANT
#define DEF_ETREVIVANT
#include "../Objet/Objet.h"
#include <vector>

// plein de choses à modifier : serait pas mal de faire un plan complet de ce que je vais faire, notamment faire pater le réseau ou bien l'intégrer, etc... : au moins dire ce que je veux que le résultat final soit...

// se débrouiller pour hériter d'une partie de ObjetMobile


class EtreVivant: virtual public Objet
{
	public:
    EtreVivant(double energie, const double geneCote, const sf::Texture & image, float x, float y, std::vector<Objet*> & objets, std::string proprietaire, sf::Int8 numero=-1);

    static double rand(double min,double max);
    static double myrand(double i,double facteur=1.1);
    static double moyenneAleatoire(double a,double b,double facteur=1.1);
    static double moyenneAleatoire_old(double a,double b,double facteur,double base);
    double geneCote() const;


	protected:
    virtual void seReproduire(EtreVivant*)=0;
    void tenterDeSeReproduire();
    virtual double diminuerEnergie(double q);
    virtual double augmenterEnergie(double q);
    double changerEnergie(double q);
    void agirVraiment(Tache tache);
    virtual void mourrir();
    bool rechercheReproduction() const;
    virtual std::vector<EtreVivant*> etresVivantsPouvantSeReproduire() const;
	//std::vector <const double*const> genes; // non : seulement dans la reproduction
    virtual std::map<std::string,std::string> toStringMap() const;

    double m_energie;
    double m_energiePourReproduction;
    bool m_rechercheReproduction;
    double m_energieMaximum;

    sf::Clock m_horlogeVie;
	
	// gènes : constant
	const double m_geneCote;
		
};


#endif
