#include "Batiment.h"

Batiment::Batiment(const sf::Texture & image,float x,float y,std::vector<Objet*> & objets,std::string proprietaire,const sf::Texture & imageObjetMobileCree,sf::Int8 numero) : Objet(image,x,y,objets,proprietaire,numero),m_imageObjetMobileCree(imageObjetMobileCree)
{
	m_type=1;
}

void Batiment::agirVraiment(Tache tache)
{
	creerObjetMobile(tache.position);
	m_tacheEnCours=false;
}

void Batiment::creerObjetMobile(sf::Vector2f position)
{
	ObjetMobile * nouveau=new ObjetMobile(m_imageObjetMobileCree,*(m_sprite.getTexture()),x()+largeur()+5,y()+(largeur())/2,m_objets,m_proprietaire);
	for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i) if((*i)!=nouveau && sontEnCollision(nouveau->sprite(),(*i)->sprite())) return;
	nouveau->agirAuClicDroit(position,0,0);
	m_objets.push_back(nouveau);
}
