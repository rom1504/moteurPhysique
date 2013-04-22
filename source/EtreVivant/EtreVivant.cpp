#include "EtreVivant.h"

EtreVivant::EtreVivant(double energie,double energiePourReproduction,const double geneCote,const sf::Texture & image,float x,float y,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero) :
    Objet(image,x,y,geneCote,geneCote,objets,proprietaire,numero),m_energie(energie),m_energiePourReproduction(energiePourReproduction),m_rechercheReproduction(false),m_geneCote(geneCote)
{
	
}

void EtreVivant::agirVraiment(Tache tache)
{
	
}

double EtreVivant::augmenterEnergie(double q)
{
    m_energie+=q;
    return q;
}

double EtreVivant::diminuerEnergie(double q)
{
    double aEnergie=m_energie;
    m_energie=m_energie-q;
    if(m_energie<=0)
    {
        mourrir();
        return aEnergie;
    }
    return q;
}

double EtreVivant::changerEnergie(double q)
{
    if(q>0) return augmenterEnergie(q);
    else return diminuerEnergie(-q);
}


void EtreVivant::tenterDeSeReproduire()
{
    auto etreVivants=etresVivantsPouvantSeReproduire();
    std::vector<Objet*> objets;
    objets.assign(etreVivants.begin(),etreVivants.end());
    auto plusProche=plusProcheObjet(objets);
    m_rechercheReproduction=true;
    if(plusProche!=NULL) seReproduire(dynamic_cast<EtreVivant*>(plusProche));
}

void EtreVivant::mourrir()
{
    auto it=std::find(m_objets.begin(),m_objets.end(),this);
    if(it!=m_objets.end()) m_objets.erase(it);
}

bool EtreVivant::rechercheReproduction() const
{
    return m_rechercheReproduction;
}

double EtreVivant::rand(double min,double max)
{
    return ((double)std::rand()/RAND_MAX)*(abs(max-min))+min;
}

double EtreVivant::myrand(double i,double facteur)
{
    bool sens=(int)rand(0,2)!=0;
    while(true) if((int)rand(0,2)!=0) break; else i=sens ? i*facteur : i/facteur;
    return i;
}

double EtreVivant::moyenneAleatoire(double a,double b,double facteur,double base)
{
    return (a+b)/2+myrand(rand(-base,base)+a-b,facteur);
}

EtreVivant * conv(Objet * o)
{
    return dynamic_cast<EtreVivant*>(o);
}

std::vector<EtreVivant*> EtreVivant::etresVivantsPouvantSeReproduire() const
{
    std::vector<Objet*> etresVivants_=objetsDeType(type());
    std::vector<EtreVivant*> etresVivants;
    std::transform(etresVivants_.begin(),etresVivants_.end(),std::back_inserter(etresVivants),conv);
    std::vector<EtreVivant*> etresVivantsPouvantSeReproduire;
    std::copy_if(etresVivants.begin(), etresVivants.end(),std::back_inserter(etresVivantsPouvantSeReproduire), std::bind(std::mem_fn(&EtreVivant::rechercheReproduction),_1));
    return etresVivantsPouvantSeReproduire;
}
