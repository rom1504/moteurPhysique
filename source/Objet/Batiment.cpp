#include "Batiment.h"

Batiment::Batiment(const sf::Texture & image,float x,float y,float w,float h,std::vector<Objet*> & objets,std::string proprietaire,const sf::Texture & imageUniteCree,sf::Int8 numero) : Objet(image,x,y,w,h,objets,proprietaire,numero),m_imageUniteCree(imageUniteCree)
{
	m_type=1;
}

void Batiment::agirVraiment(Tache tache)
{
	creerUnite(tache.position);
	m_tacheEnCours=false;
}

void Batiment::creerUnite(sf::Vector2f position)
{
	Unite * nouveau=new Unite(m_imageUniteCree,*(m_sprite.getTexture()),x()+largeur()+5,y()+(largeur())/2,28,28,350,m_objets,m_proprietaire);
    for(Objet * o : m_objets) if(o!=nouveau && nouveau->enCollision(o)) return;
	nouveau->agirAuClicDroit(position,0,0);
	m_objets.push_back(nouveau);
}
