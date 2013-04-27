#include "ObjetMobile.h"

ObjetMobile::ObjetMobile(const sf::Texture & image,float x,float y,float w,float h,float vitesse,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero) : Objet(image,x,y,w,h,objets,proprietaire,numero),m_seDeplace(false),m_destination(x,y),m_vitesse(vitesse)
{
	// destination initiale foireux mais fonctionnel : objectif: régler le problème du aller à en réseau ( décalage de la position de base ) : doit être régler par la suite par une transmission de la variable se_deplace ( trouver un type bool compatible avec le type packet de la sfml )

}


void ObjetMobile::aFinitDeSeDeplacer()
{
	m_seDeplace=false;
	m_tacheEnCours=false;
//    std::cout<<"Je suis arrivé :) :)"<<std::endl;;
}

sf::FloatRect agrandir(sf::FloatRect r,double a)
{
    return sf::FloatRect(r.left-a,r.top-a,r.width+2*a,r.height+2*a);
}

void ObjetMobile::deplacer()
{
    float AC=m_vitesse*m_tempsEcoule;
	float xA=x(),yA=y();
	float xB=m_destination.x,yB=m_destination.y;
	float AB=std::sqrt(std::pow(xB-xA,2)+std::pow(yB-yA,2));
    if(AB!=0 && AB>=AC)
	{
		float xAC=AB<AC ? xB-xA : (xB>xA ? 1 : -1)*(AC*std::abs(xB-xA))/AB;
		float yAC=AB<AC ? yB-yA : (yB>yA ? 1 : -1)*(AC*std::abs(yB-yA))/AB;
        //sf::Sprite nouveauSprite=m_sprite;
        //nouveauSprite.move(xAC,yAC);
		//for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i) if(*i!=&(*this) && sontEnCollision(nouveauSprite,(*i)->sprite())) return;
		m_sprite.move(xAC,yAC);
	}
    if(AB<=AC)
    {
        m_sprite.setPosition(xB,yB);
        aFinitDeSeDeplacer();// ici pourrait se faire l'utilisation d'un signal personnalisé ( boost ou quoi ... )
    }
}

std::map<std::string,std::string> ObjetMobile::toStringMap() const
{
	auto m=Objet::toStringMap();
	m["vitesse"]=std::to_string(m_vitesse);
    m["se deplace"]=m_seDeplace ? "oui" : "non";
	return m;
}

const sf::Vector2f ObjetMobile::destination() const
{
	return m_destination;
}

void ObjetMobile::agirVraiment(Tache tache)
{
	m_tacheEnCours=false;
}

void ObjetMobile::continuerAAgirVraiment()
{
	deplacer();
}

void ObjetMobile::allerA(sf::Vector2f destination)
{
	allerA(destination.x,destination.y);
}

void ObjetMobile::allerA(float x,float y)
{
	m_destination.x=x;
	m_destination.y=y;
	m_seDeplace=true;
    m_tacheEnCours=true;
}
