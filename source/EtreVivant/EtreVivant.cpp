#include "EtreVivant.h"

EtreVivant::EtreVivant(double energie,const double geneCote,const sf::Texture & image,float x,float y,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero) :
    Objet(image,x,y,geneCote,geneCote,objets,proprietaire,numero),m_energie(energie),m_rechercheReproduction(false),m_geneCote(geneCote)
{
    m_energieMaximum=10/2*m_geneCote/10;
    m_energiePourReproduction=5/2*m_geneCote/10;
    m_horlogeVie.restart();
}

void EtreVivant::agirVraiment(Tache tache)
{
	
}

std::map<std::string,std::string> EtreVivant::toStringMap() const
{
    auto m=Objet::toStringMap();
    m["energie"]=std::to_string(m_energie);
    m["energie pour reproduction"]=std::to_string(m_energiePourReproduction);
    m["peut se reproduire"]=m_energie>=m_energiePourReproduction ? "oui" : "non";
    m["recherche la reproduction"]=m_rechercheReproduction ? "oui" : "non";
    m["geneCote"]=std::to_string(m_geneCote);
    m["energieMaximum"]=std::to_string(m_energieMaximum);
    m["temps de vie"]=std::to_string(m_horlogeVie.getElapsedTime().asSeconds());
    return m;
}

double EtreVivant::augmenterEnergie(double q)
{
    double nEnergie=m_energie+q;
    if(nEnergie<=m_energieMaximum)
    {
        m_energie=nEnergie;
        return q;
    }
    m_energie=m_energieMaximum;
    return m_energie-(nEnergie-q);
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

double abs(double d)
{
    return d>0 ? d : -d;
}



double EtreVivant::moyenneAleatoire_old(double a,double b,double facteur,double base)
{
    double m=(a+b)/2;
    double c=m+(((int)rand(0,2))==0 ? -1 : 1)*myrand(rand(-base,base)+abs(a-b),facteur);
    return c;
}
double EtreVivant::moyenneAleatoire(double a,double b,double facteur)
{
    double m=(a+b)/2;
    double d=abs(a-b);
    d=d==0 ? 1 : d;
    double c=m*myrand(1,1+(m/d)/100);
    return c>0 ? c : m;
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
