#ifndef DEF_OBJET
#define DEF_OBJET

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> 
#include <SFML/Network.hpp> 
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include "../Conversion.h"
#include <iostream>

struct Tache
{
	int type;//permet d'associer à un nombre diverses taches en fonctions de la classes dérivées, est ce que ce serait mieux de faire un enum et de dériver la structure Tache ? semble pas évident comme ça, à voir ensuite...
	sf::Vector2f position;
};
using namespace std::placeholders;

class Objet
{
	public:// essayer de diminuer le nombre de truc en public
	Objet(const sf::Texture & image,float x,float y,float w,float h,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero=-1);
	virtual ~Objet();
	void setSelectionne(bool selectionne);
	bool selectionne() const;
	void agirAuClicDroit(sf::Vector2f position,bool ajouterALaQueue,int typeTache);
    virtual void agir();
	const std::string proprietaire() const;
	const sf::Int8 numero() const;
	const sf::Int8 type() const;
	void draw(sf::RenderWindow* Target);
	float largeur() const;
	float hauteur() const;
	float x() const;
	float y() const;
    sf::Vector2f position() const;
    virtual bool enCollision(const Objet * objet) const;
	sf::FloatRect fcontour() const;
	sf::IntRect icontour() const;
	const sf::Texture * texture() const;
    double distanceAvec(const Objet * o) const;
    bool plusPres(const Objet * o1,const Objet * o2) const;
    bool estDeType(int type) const;
    Objet * plusProcheObjet(std::vector<Objet*> & objets) const;
    Objet * plusProcheObjet() const;
    std::vector<Objet*> objetsDeType(int type) const;
    std::vector<Objet*> pasMoi() const;
	
    //vaudrait mieux mettre un max de truc en privé pour pouvoir changer Objet sans tout péter dans les classes qui héritent
	protected:
	virtual void agirVraiment(Tache tache)=0;//changer de nom ?...
	virtual void continuerAAgirVraiment(); // pas forcé de redéfinir ( ne fait rien si non rédéfinit )
    virtual void agirAChaqueFois();
	
	protected://attributs divers
	std::vector<Objet*> & m_objets;
	std::queue<Tache> m_ordres;// pas fini
	bool m_tacheEnCours;
	sf::Sprite m_sprite;
    sf::Int8 m_type;
    std::string m_proprietaire;
    double m_tempsEcoule;

    private:
    bool m_selectionne;
    sf::Int8 m_numero;
    sf::Clock m_horloge;

};

bool comparabley(Objet * a,Objet * b);

struct triPlacement
{
	bool operator()(const Objet * objet1,const Objet * objet2) const;
};

#endif
