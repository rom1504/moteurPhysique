#include "Objet.h"
#include <numeric>
#include <functional>
#include <algorithm>

bool Objet::enCollision(const Objet * objet) const
{
//    return rectangleFDeSprite(m_sprite).intersects(rectangleFDeSprite(objet->m_sprite));
    return fcontour().intersects(objet->fcontour());
}

Objet::Objet(const sf::Texture & image,float x,float y,float w,float h,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero) : m_objets(objets),m_tacheEnCours(false),m_proprietaire(proprietaire),m_tempsEcoule(0),m_selectionne(false)
{
	m_sprite.setTexture(image);
	m_sprite.setPosition(x,y);
	m_sprite.setScale(w/largeur(),h/hauteur());
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

Objet * Objet::plusProcheObjet(std::vector<Objet*> &objets) const
{
    auto it=std::min_element(objets.begin(),objets.end(),std::bind(std::mem_fn(&Objet::plusPres),this,_1,_2));
    if(it!=objets.end()) return *it;
    else return NULL;
}

std::map<std::string,std::string> Objet::toStringMap() const
{
    std::map<std::string,std::string> m;
    m["type"]=std::to_string((int)m_type);
    m["x"]=std::to_string(x());
    m["y"]=std::to_string(y());
    return m;
}


std::string Objet::toString() const
{
    auto m=toStringMap();
    return std::accumulate(m.begin(),m.end(),std::string(""),[](std::string s,std::pair<std::string,std::string> p) {return s+(p.first+": "+p.second+"\n");});
}

Objet * Objet::plusProcheObjet() const
{
    return plusProcheObjet(m_objets);
}

bool Objet::estDeType(int type) const
{
    return m_type==type;
}

std::vector<Objet*> Objet::pasMoi() const
{
    std::vector<Objet*> objets;
    remove_copy(m_objets.begin(),m_objets.end(),std::back_inserter(objets),this);
    return objets;
}

std::vector<Objet*> Objet::objetsDeType(int type) const
{
    auto obs=pasMoi();
    std::vector<Objet*> objets;
    std::copy_if(obs.begin(), obs.end(),std::back_inserter(objets), std::bind(std::mem_fn(&Objet::estDeType),_1,type));
    return objets;
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

sf::Vector2f Objet::position() const
{
    return m_sprite.getPosition();
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

void Objet::draw(sf::RenderWindow* target)
{
	target->draw(m_sprite);
}

const sf::Texture * Objet::texture() const
{
	return m_sprite.getTexture();
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

double Objet::distanceAvec(const Objet * o) const
{
    return sqrt((x()-o->x())*(x()-o->x())+(y()-o->y())*(y()-o->y()));
}


bool Objet::plusPres(const Objet * o1,const Objet * o2) const
{
    return distanceAvec(o1)<distanceAvec(o2);
}

void Objet::agir()
{
    m_tempsEcoule=m_horloge.getElapsedTime().asSeconds();
    m_horloge.restart();
    //sf::Clock c1;
    agirAChaqueFois();
    //std::cout<<c1.getElapsedTime().asMicroseconds()<<std::endl;
    //sf::Clock c;
	if(m_tacheEnCours)
	{
		continuerAAgirVraiment();
	}
	else if(!m_ordres.empty()) // faire une tache après l'autre : utile si la tâche n'est pas instantannée et pas génant sinon
	{
		m_tacheEnCours=true;
		Tache &t=m_ordres.front();
		agirVraiment(t);//tester pop_front
		m_ordres.pop();
	}
    //std::cout<<c.getElapsedTime().asMicroseconds()<<std::endl;
}

void Objet::agirAChaqueFois()
{

}

void Objet::continuerAAgirVraiment()
{
	
}

sf::FloatRect Objet::fcontour() const
{
    return m_sprite.getGlobalBounds();
}

sf::IntRect Objet::icontour() const
{
    return sf::IntRect(fcontour());
}

bool Objet::selectionne() const
{
	return m_selectionne;
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
