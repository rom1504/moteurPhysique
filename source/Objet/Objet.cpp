#include "Objet.h"

bool sontEnCollision(const sf::Sprite & sprite1,const sf::Sprite & sprite2)
{
	return rectangleFDeSprite(sprite1).intersects(rectangleFDeSprite(sprite2));
}

Objet::Objet(const sf::Texture & image,float x,float y,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero) : m_selectionne(false),m_objets(objets),m_proprietaire(proprietaire),m_tacheEnCours(false)
{
	m_sprite.setTexture(image);
	m_sprite.setPosition(x,y);
	m_numero=numero!=-1 ? numero : (m_objets.empty() ? 1 : (m_objets.back())->numero()+1);
}

float Objet::largeur() const
{
	return m_sprite.getGlobalBounds().width;
}

float Objet::hauteur() const
{
	return m_sprite.getGlobalBounds().height;
}

bool comparabley(const Objet * a,const Objet * b)
{
	float hmoy=(a->hauteur()+b->hauteur())/2;
	return abs(a->y()-b->y())<(10*hmoy/100);
}

bool triPlacement::operator()(const Objet * objet1,const Objet * objet2) const
{
	if(objet1->y()<objet2->y()) return true;
	else if(comparabley(objet2,objet1)) return objet1->x()<objet2->x();
	else return false;
}

float Objet::x() const 
{
	return m_sprite.getPosition().x;
}

float Objet::y() const
{
	return m_sprite.getPosition().y;
}

Objet::~Objet()
{
	
}

void Objet::setSelectionne(bool selectionne)
{
	m_selectionne=selectionne;
}

void Objet::agirAuClicDroit(sf::Vector2f position,bool ajouterALaQueue,int typeTache)
{
	if(!ajouterALaQueue)
	{
		while(!m_ordres.empty()) m_ordres.pop();
		m_tacheEnCours=false;
	}
	Tache tache;
	tache.type=typeTache;// peut on faire mieux ?
	tache.position=position;
	m_ordres.push(tache);
}

void Objet::agir()
{
	if(m_tacheEnCours) continuerAAgirVraiment();
	else if(!m_ordres.empty()) // faire une tache après l'autre : utile si la tâche n'est pas instantannée et pas génant sinon
	{
		m_tacheEnCours=true;
		agirVraiment(m_ordres.front());//tester pop_front
		m_ordres.pop();
	}
}

void Objet::continuerAAgirVraiment()
{
	
}

bool Objet::selectionne() const
{
	return m_selectionne;
}

const sf::Sprite & Objet::sprite() const
{
	return m_sprite;
}

const std::string Objet::proprietaire() const
{
	return m_proprietaire;
}

const sf::Int8 Objet::numero() const
{
	return m_numero;
}

const sf::Int8 Objet::type() const
{
	return m_type;
}
