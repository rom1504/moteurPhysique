#include "Animal.h"
#include <algorithm>
#include <functional>

Animal::Animal(double energie, const double geneCote, const double geneVitesse, const sf::Texture & image, float x, float y, std::vector<Objet*> & objets, std::string proprietaire, sf::Int8 numero) :
Objet(image,x,y,geneCote,geneCote,objets,proprietaire,numero)
,EtreVivant(energie,geneCote,image,x,y,objets,proprietaire,numero)
,ObjetMobile(image,x,y,geneCote,geneCote,geneVitesse,objets,proprietaire,numero)
,m_geneVitesse(geneVitesse)
{
    m_type=2;
    m_vitesseManger=m_geneCote;
}

void Animal::manger(Plante * p)
{
    changerEnergie(p->etreMange(m_vitesseManger*m_tempsEcoule));
}

std::map<std::string,std::string> Animal::toStringMap() const
{
    auto m=EtreVivant::toStringMap();
    auto m1=ObjetMobile::toStringMap();
    m.insert(m1.begin(),m1.end());
    return m;
}


void Animal::agirAChaqueFois()
{
    if(m_horlogeVie.getElapsedTime().asSeconds()>10)
    {
        mourrir();
        return;
    }
    changerEnergie(-m_tempsEcoule/120*m_geneCote/25);//dépense d'énergie pour rester en vie
    // les conditions sont bien ici ?
    if(/*!(m_rechercheReproduction && m_seDeplace)*/ /*&& m_objets.size()<500*/ /*&&*/ m_energie>=m_energiePourReproduction &&  std::accumulate(m_objets.begin(),m_objets.end(),0,[](int n,Objet * o){return o->type()==2 ? n+1 : n;})<30)
    {
        m_seDeplace=false;
        m_tacheEnCours=false;
        tenterDeSeReproduire();
//        std::cout<<"lolo"<<std::endl;
    }
    if(m_seDeplace) {/*std::cout<<"Je me déplace :) :)"<<std::endl;*/changerEnergie(-m_geneVitesse/120*m_tempsEcoule*m_geneCote/25);}
    using namespace std::placeholders;
    auto it = std::find_if (m_objets.begin(), m_objets.end(), std::bind(std::logical_and<bool>(),std::bind(std::mem_fn(&Objet::enCollision),this,_1),std::bind(std::mem_fn(&Objet::estDeType),_1,3)));
    if(it!=m_objets.end()) {/*std::cout<<"Je mange :) :)"<<std::endl;*/manger(dynamic_cast<Plante*>(*it));}
    else if(!m_seDeplace  && !(m_rechercheReproduction && m_seDeplace))
    {
       // std::cout<<"J'essaye de me déplacer :) :)"<<std::endl;
        std::vector<Objet*> plantes=objetsDeType(3);
        Objet * o=plusProcheObjet(plantes);
        if(o!=NULL)allerA(o->position());
       // else std::cout<<"Je trouve rien à manger :( :("<<std::endl;
    }
}

void Animal::agirVraiment(Tache tache)
{

}

void Animal::seReproduire(EtreVivant* etreVivant)
{
    seReproduire(dynamic_cast<Animal*>(etreVivant));
}

void Animal::seReproduire(Animal * animal)
{
    if(enCollision(animal))
    {
//        mourrir();
//        std::cout<<(int)animal->type()<<std::endl;
        double x_=moyenneAleatoire(x(),animal->x(),1.3,20);
        double y_=moyenneAleatoire(y(),animal->y(),1.3,20);
        double geneCote=moyenneAleatoire(m_geneCote,animal->m_geneCote,1.3,0);
        double geneVitesse=moyenneAleatoire(m_geneVitesse,animal->m_geneVitesse,1.3,0);
        m_objets.push_back(new Animal((m_energiePourReproduction+animal->m_energiePourReproduction)/2, geneCote,geneVitesse, *texture(), x_, y_, m_objets, m_proprietaire));
        m_rechercheReproduction=false;
        animal->m_rechercheReproduction=false;
        diminuerEnergie(m_energiePourReproduction/2/**geneCote/m_geneCote*/);
        animal->diminuerEnergie(animal->m_energiePourReproduction/2/**geneCote/animal->m_geneCote*/);
    }
    else
    {
        allerA(animal->position());// plutôt allerA(animal) ?
    }
}
