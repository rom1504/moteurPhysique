#include "Animal.h"
#include <algorithm>
#include <functional>

Animal::Animal(double energie, const double geneVitesseManger, const double geneCote, const double geneVitesse, const sf::Texture & image, float x, float y, std::vector<Objet*> & objets, std::string proprietaire, sf::Int8 numero) :
Objet(image,x,y,geneCote,geneCote,objets,proprietaire,numero)
,EtreVivant(energie,geneCote,image,x,y,objets,proprietaire,numero)
,ObjetMobile(image,x,y,geneCote,geneCote,geneVitesse,objets,proprietaire,numero)
,m_geneVitesse(geneVitesse),m_geneVitesseManger(geneVitesseManger)
{
	m_type=2;
    m_energiePourReproduction=m_energie*1.5;
}

void Animal::manger(Plante * p)
{
    double quantiteMange=m_geneVitesseManger/10*m_tempsEcoule;
    double a=changerEnergie(p->etreMange(quantiteMange));
    if(a>0) changerEnergie(-quantiteMange/5);
}

std::map<std::string,std::string> Animal::toStringMap() const
{
    auto m=EtreVivant::toStringMap();
    auto m1=ObjetMobile::toStringMap();
    m.insert(m1.begin(),m1.end());
    m["geneVitesseManger"]=std::to_string(m_geneVitesseManger);
    return m;
}


void Animal::agirAChaqueFois()
{
    changerEnergie(-m_tempsEcoule);//vieillesse
    // les conditions sont bien ici ?
    if(/*!(m_rechercheReproduction && m_seDeplace)*/ /*&& m_objets.size()<500*/ /*&&*/ m_energie>=m_energiePourReproduction)
    {
        m_seDeplace=false;
        m_tacheEnCours=false;
        tenterDeSeReproduire();
//        std::cout<<"lolo"<<std::endl;
    }
    if(m_seDeplace) {/*std::cout<<"Je me déplace :) :)"<<std::endl;*/changerEnergie(-m_geneVitesse/25*m_tempsEcoule);}
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
        double geneVitesseManger=moyenneAleatoire(m_geneVitesseManger,animal->m_geneVitesseManger,1.3,0);
        double geneVitesse=moyenneAleatoire(m_geneVitesse,animal->m_geneVitesse,1.3,0);
        m_objets.push_back(new Animal((m_energiePourReproduction+animal->m_energiePourReproduction)/2, geneVitesseManger, geneCote,geneVitesse, *texture(), x_, y_, m_objets, m_proprietaire));
        m_rechercheReproduction=false;
        animal->m_rechercheReproduction=false;
        m_energie-=m_energiePourReproduction/2;
        animal->m_energie-=animal->m_energiePourReproduction/2;
    }
    else
    {
        allerA(animal->position());// plutôt allerA(animal) ?
    }
}
