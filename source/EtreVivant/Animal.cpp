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

double Animal::geneVitesse() const
{
    return m_geneVitesse;
}

double max(double a, double b)
{
    return a>b ? a : b;
}

void Animal::manger(Plante * p)
{
    double possibleDeManger=m_vitesseManger*m_tempsEcoule;
    double essayerManger=max(possibleDeManger,m_energieMaximum-m_energie);
    changerEnergie(p->etreMange(essayerManger));
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
//    sf::Clock c;
//    sf::Clock c1;
    if(m_horlogeVie.getElapsedTime().asSeconds()>10)
    {
        mourrir();
        return;
    }
    changerEnergie(-m_tempsEcoule/120*m_geneCote/25);//dépense d'énergie pour rester en vie
    // les conditions sont bien ici ?
    if(/*!(m_rechercheReproduction && m_seDeplace)*/ /*&& m_objets.size()<500*/ /*&&*/ m_energie>=m_energiePourReproduction &&  std::accumulate(m_objets.begin(),m_objets.end(),0,[](int n,Objet * o){return o->type()==2 ? n+1 : n;})<40)
    {
        m_seDeplace=false;
        m_tacheEnCours=false;
        tenterDeSeReproduire();
//        std::cout<<"lolo"<<std::endl;
    }
    if(m_seDeplace) {/*std::cout<<"Je me déplace :) :)"<<std::endl;*/changerEnergie(-(m_geneVitesse/120+m_geneCote/40)*m_tempsEcoule/10);}
    using namespace std::placeholders;
//    std::cout<<"c1:"<<c1.getElapsedTime().asMicroseconds()<<std::endl;
//    sf::Clock c2;
// une seule en meme temps ?
    auto it = std::find_if (m_objets.begin(), m_objets.end(),[this](Objet * o) {return o->estDeType(3) && enCollision(o);});


//    std::cout<<"c2:"<<c2.getElapsedTime().asMicroseconds()<<std::endl;
//    sf::Clock c3;
    if(it!=m_objets.end()) {/*std::cout<<"Je mange :) :)"<<std::endl;*/manger(dynamic_cast<Plante*>(*it));}
    else if(!m_seDeplace  && !(m_rechercheReproduction && m_seDeplace))
    {

//        sf::Clock c4;
       // std::cout<<"J'essaye de me déplacer :) :)"<<std::endl;
        std::vector<Objet*> plantes=objetsDeType(3);

//        std::cout<<"c4:"<<c4.getElapsedTime().asMicroseconds()<<std::endl;
//        sf::Clock c5;
        Objet * o=plusProcheObjet(plantes);
//        std::cout<<"c5:"<<c5.getElapsedTime().asMicroseconds()<<std::endl;

//        sf::Clock c6;
        if(o!=NULL)allerA(o->position());
//        std::cout<<"c6:"<<c6.getElapsedTime().asMicroseconds()<<std::endl;

        // voir via moyenne si mieux ?
//        Objet * min=NULL;
//        double dmin=1000000;
//        double d;
//        for(Objet * o : m_objets)
//        {
//            if(o->type()==3 && (d=distanceAvec(o))<dmin)
//            {
//                min=o;
//                dmin=d;
//            }
//        }
//        if(min!=NULL)allerA(min->position());

       // else std::cout<<"Je trouve rien à manger :( :("<<std::endl;
    }
//    std::cout<<"c3:"<<c3.getElapsedTime().asMicroseconds()<<std::endl;
//    std::cout<<c.getElapsedTime().asMicroseconds()<<std::endl;
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
        double x_=moyenneAleatoire_old(x(),animal->x(),1.3,20);
        double y_=moyenneAleatoire_old(y(),animal->y(),1.3,20);
        double geneCote=moyenneAleatoire(m_geneCote,animal->m_geneCote,1.3);
        double geneVitesse=moyenneAleatoire(m_geneVitesse,animal->m_geneVitesse,1.3);
        if(x_>-500 && y_>-500 && x_+geneCote<500 && y_+geneCote<500)
        {
            m_objets.push_back(new Animal((m_energiePourReproduction+animal->m_energiePourReproduction)/2, geneCote,geneVitesse, *texture(), x_, y_, m_objets, m_proprietaire));
            m_rechercheReproduction=false;
            animal->m_rechercheReproduction=false;
            diminuerEnergie(m_energiePourReproduction/2/**geneCote/m_geneCote*/);
            animal->diminuerEnergie(animal->m_energiePourReproduction/2/**geneCote/animal->m_geneCote*/);
        }
    }
    else
    {
        allerA(animal->position());// plutôt allerA(animal) ?
    }
}
