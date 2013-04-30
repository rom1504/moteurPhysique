#include "Plante.h"
#include <algorithm>
#include <numeric>


Plante::Plante(double energie, const double geneCote, const sf::Texture & image, float x, float y, std::vector<Objet*> & objets, std::string proprietaire, sf::Int8 numero) :
Objet(image,x,y,geneCote,geneCote,objets,proprietaire,numero)
,EtreVivant(energie,geneCote,image,x,y,objets,proprietaire,numero)
{
    m_type=3;
    m_vitesseCroissance=m_geneCote/10;
}

void Plante::agirAChaqueFois()
{
//    sf::Clock c;
//    sf::Clock c1;
    if(m_horlogeVie.getElapsedTime().asSeconds()>10)
    {
        mourrir();
        return;
    }
    pousser();
//    std::cout<<"c1: "<<c1.getElapsedTime().asMicroseconds()<<std::endl;
    if(m_energie>=m_energiePourReproduction)
    {
//        sf::Clock c2;
        int nbPlantes=std::accumulate(m_objets.begin(),m_objets.end(),0,[](int n,Objet * o){return o->type()==3 ? n+1 : n;});
//        std::cout<<"c2: "<<c2.getElapsedTime().asMicroseconds()<<std::endl;
//        sf::Clock c3;
        if(nbPlantes<600) tenterDeSeReproduire();
//        std::cout<<"c3: "<<c3.getElapsedTime().asMicroseconds()<<std::endl;
    }
//    std::cout<<c.getElapsedTime().asMicroseconds()<<std::endl;
}

double Plante::etreMange(double quantiteMange)
{
    return changerEnergie(-quantiteMange);
}

std::map<std::string,std::string> Plante::toStringMap() const
{
    auto m=EtreVivant::toStringMap();
    m["vitesseCroissance"]=std::to_string(m_vitesseCroissance);
    return m;
}


void Plante::pousser()
{
    changerEnergie(m_vitesseCroissance*m_tempsEcoule);
}

std::vector<EtreVivant*> Plante::etresVivantsPouvantSeReproduire() const
{
    auto etresVivants=EtreVivant::etresVivantsPouvantSeReproduire();
    std::vector<EtreVivant*> etresVivants2;
    std::copy_if(etresVivants.begin(), etresVivants.end(),std::back_inserter(etresVivants2), std::bind(std::less<double>(),std::bind(std::mem_fn(&Objet::distanceAvec),this,_1),100*m_geneCote/10));
    return etresVivants2;
}

void Plante::seReproduire(EtreVivant* etreVivant)
{
    seReproduire(dynamic_cast<Plante*>(etreVivant));
}

void Plante::seReproduire(Plante * plante)
{
    double geneCote=moyenneAleatoire(m_geneCote,plante->m_geneCote,1.01);
    double x_=moyenneAleatoire_old(x(),plante->x(),1.3,10*geneCote/10);
    double y_=moyenneAleatoire_old(y(),plante->y(),1.3,10*geneCote/10);

    if(x_>-500 && y_>-500 && x_+geneCote<500 && y_+geneCote<500)
    {
        Plante * plante_=new Plante((m_energiePourReproduction+plante->m_energiePourReproduction)/2, geneCote, *texture(), x_, y_, m_objets, m_proprietaire);
        if(!std::any_of (m_objets.begin(), m_objets.end(), std::bind(std::mem_fn(&Objet::enCollision),plante_,_1)))//changer pour qu'elles puissent aparaitre sous une vache ?
        {
            m_objets.push_back(plante_);
            m_rechercheReproduction=false;
            plante->m_rechercheReproduction=false;
            diminuerEnergie(m_energiePourReproduction/2/**geneCote/m_geneCote*/);
            plante->diminuerEnergie(plante->m_energiePourReproduction/2/**geneCote/plante->m_geneCote*/);
        }
    }

}
