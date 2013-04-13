#include "ObjetMobile.h"

ObjetMobile::ObjetMobile(const sf::Texture & image,const sf::Texture & imageBatiment,float x,float y,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero) : Objet(image,x,y,objets,proprietaire,numero),m_seDeplace(false),m_vitesse(350),m_imageBatiment(imageBatiment)
{
	m_type=0;
	m_destination.x=x;// foireux mais fonctionnel : objectif: régler le problème du aller à en réseau ( décalage de la position de base ) : doit être régler par la suite par une transmission de la variable se_deplace ( trouver un type bool compatible avec le type packet de la sfml )
	m_destination.y=y;
}


void ObjetMobile::aFinitDeSeDeplacer()
{
	if(m_construire)
	{
		m_objets.push_back(new Batiment(m_imageBatiment,x()+(largeur())*1.1,hauteur(),m_objets,m_proprietaire,*(m_sprite.getTexture())));
	}
}

void ObjetMobile::deplacer()
{
	float AC=m_vitesse*m_horloge.getElapsedTime().asSeconds();
	m_horloge.restart();
	float xA=x(),yA=y();
	float xB=m_destination.x,yB=m_destination.y;
	float AB=std::sqrt(std::pow(xB-xA,2)+std::pow(yB-yA,2));
	if(AB!=0)
	{
		float xAC=AB<AC ? xB-xA : (xB>xA ? 1 : -1)*(AC*std::abs(xB-xA))/AB;
		float yAC=AB<AC ? yB-yA : (yB>yA ? 1 : -1)*(AC*std::abs(yB-yA))/AB;
		sf::Sprite nouveauSprite=m_sprite;
		nouveauSprite.move(xAC,yAC);
		//for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i) if(*i!=&(*this) && sontEnCollision(nouveauSprite,(*i)->sprite())) return;
		m_sprite.move(xAC,yAC);
	}
	if(AB<AC)
	{
		m_tacheEnCours=false;
		aFinitDeSeDeplacer();// ici pourrait se faire l'utilisation d'un signal personnalisé ( boost ou quoi ... )
	}
}

const sf::Vector2f ObjetMobile::destination() const
{
	return m_destination;
}

void ObjetMobile::agirVraiment(Tache tache)
{
	m_construire=tache.type;
	allerA(tache.position);
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
	m_horloge.restart();
}
