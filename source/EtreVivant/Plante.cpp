#include "Plante.h"
#include <algorithm>
#include <numeric>

double Plante::m_nbPlantes=0;

Plante::Plante(double energie, const double geneCote, const sf::Texture & image, float x, float y, std::vector<Objet*> & objets, std::string proprietaire, sf::Int8 numero) :
Objet(image,x,y,geneCote,geneCote,objets,proprietaire,numero)
,EtreVivant(energie,geneCote,image,x,y,objets,proprietaire,numero)
{
	m_type=3;
    m_energieMaximum=2*m_energie*m_geneCote/10;
    m_energiePourReproduction=5/2*m_geneCote/10;
    m_vitesseCroissance=m_geneCote/10;
    m_nbPlantes++;
}


void Plante::mourrir()
{
    EtreVivant::mourrir();
    m_nbPlantes--;
}

void Plante::agirAChaqueFois()
{//static bien.... ?
    //int nbPlante=std::accumulate(m_objets.begin(),m_objets.end(),0,[](int n,Objet * o){return o->type()==3 ? n+1 : n;});
    pousser();
    if(m_nbPlantes<500 && m_energie>=m_energiePourReproduction) tenterDeSeReproduire();
}

double Plante::etreMange(double quantiteMange)
{
    return changerEnergie(-quantiteMange);
}

std::map<std::string,std::string> Plante::toStringMap() const
{
    auto m=EtreVivant::toStringMap();
    m["vitesseCroissance"]=std::to_string(m_vitesseCroissance);
    m["energieMaximum"]=std::to_string(m_energieMaximum);
    return m;
}


void Plante::pousser()
{
    changerEnergie(m_vitesseCroissance*m_tempsEcoule);
}

double Plante::augmenterEnergie(double q)
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

std::vector<EtreVivant*> Plante::etresVivantsPouvantSeReproduire() const
{
    auto etresVivants=EtreVivant::etresVivantsPouvantSeReproduire();
    std::vector<EtreVivant*> etresVivants2;
    std::copy_if(etresVivants.begin(), etresVivants.end(),std::back_inserter(etresVivants2), std::bind(std::less<double>(),std::bind(std::mem_fn(&Objet::distanceAvec),this,_1),100));
    return etresVivants2;
}

void Plante::seReproduire(EtreVivant* etreVivant)
{
    seReproduire(dynamic_cast<Plante*>(etreVivant));
}

void Plante::seReproduire(Plante * plante)
{
    double x_=moyenneAleatoire(x(),plante->x(),1.3,20);
    double y_=moyenneAleatoire(y(),plante->y(),1.3,20);
    double geneCote=moyenneAleatoire(m_geneCote,plante->m_geneCote,1.01,0);
    m_objets.push_back(new Plante((m_energiePourReproduction+plante->m_energiePourReproduction)/2, geneCote, *texture(), x_, y_, m_objets, m_proprietaire));
    m_rechercheReproduction=false;
    plante->m_rechercheReproduction=false;
    m_energie-=m_energiePourReproduction/2;
    plante->m_energie-=plante->m_energiePourReproduction/2;
}
