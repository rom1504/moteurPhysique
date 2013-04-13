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

bool sontEnCollision(const sf::Sprite & sprite1,const sf::Sprite & sprite2);

struct Tache
{
	int type;//permet d'associer à un nombre diverses taches en fonctions de la classes dérivées, est ce que ce serait mieux de faire un enum et de dériver la structure Tache ? semble pas évident comme ça, à voir ensuite...
	sf::Vector2f position;
};

class Objet
{
	public:// essayer de diminuer le nombre de truc en public
	Objet(const sf::Texture & image,float x,float y,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero=-1);
	virtual ~Objet();
	const sf::Sprite & sprite() const;
	void setSelectionne(bool selectionne);
	bool selectionne() const;
	void agirAuClicDroit(sf::Vector2f position,bool ajouterALaQueue,int typeTache);
	void agir();
	const std::string proprietaire() const;
	const sf::Int8 numero() const;
	const sf::Int8 type() const;
	void Draw(sf::RenderWindow& Target);
	float largeur() const;
	float hauteur() const;
	float x() const;
	float y() const;
	
	protected:
	virtual void agirVraiment(Tache tache)=0;//changer de nom ?...
	virtual void continuerAAgirVraiment(); // pas forcé de redéfinir ( ne fait rien si non rédéfinit )
	
	protected://attributs divers
	sf::Sprite m_sprite;
	bool m_selectionne;
	std::vector<Objet*> & m_objets;
	std::queue<Tache> m_ordres;// pas fini
	std::string m_proprietaire;
	sf::Int8 m_numero;
	sf::Int8 m_type;
	bool m_tacheEnCours;
};

bool comparabley(Objet * a,Objet * b);

struct triPlacement
{
	bool operator()(const Objet * objet1,const Objet * objet2) const;
};

#endif
