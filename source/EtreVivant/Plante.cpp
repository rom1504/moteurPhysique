#include "Plante.h"
#include <algorithm>

Plante::Plante(double energie, double energieMaximum,double energiePourReproduction, double vitesseCroissance, const double geneCote, const sf::Texture & image, float x, float y, std::vector<Objet*> & objets, std::string proprietaire, sf::Int8 numero) :
Objet(image,x,y,geneCote,geneCote,objets,proprietaire,numero)
,EtreVivant(energie,energiePourReproduction,geneCote,image,x,y,objets,proprietaire,numero),
  m_energieMaximum(energieMaximum),
  m_vitesseCroissance(vitesseCroissance)
{
	m_type=3;
}

void Plante::agirAChaqueFois()
{
    pousser();
    if(m_objets.size()<500 && m_energie>=m_energiePourReproduction) tenterDeSeReproduire();
}

double Plante::etreMange(double quantiteMange)
{
    return changerEnergie(-quantiteMange);
}

void Plante::pousser()
{
    changerEnergie(m_vitesseCroissance/5*m_tempsEcoule);
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
    double geneCote=moyenneAleatoire(m_geneCote,plante->m_geneCote,1.1,0);
    m_objets.push_back(new Plante(2.0, m_energieMaximum,m_energiePourReproduction, m_vitesseCroissance, geneCote, *texture(), x_, y_, m_objets, m_proprietaire));
    m_rechercheReproduction=false;
    plante->m_rechercheReproduction=false;
    m_energie-=m_energiePourReproduction/2;
    plante->m_energie-=plante->m_energiePourReproduction/2;
}
