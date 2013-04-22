#include "Unite.h"

Unite::Unite(const sf::Texture & image,const sf::Texture & imageBatiment,float x,float y,float w,float h,float vitesse,std::vector<Objet*> & objets,std::string proprietaire,sf::Int8 numero) :
Objet(image,x,y,w,h,objets,proprietaire,numero)
,ObjetMobile(image,x,y,w,h,vitesse,objets,proprietaire,numero),m_imageBatiment(imageBatiment),m_construire(false)
{
	m_type=0;
}


void Unite::aFinitDeSeDeplacer()
{
	if(m_construire) m_objets.push_back(new Batiment(m_imageBatiment,x()+(largeur())*1.1,y()+hauteur(),50,50,m_objets,m_proprietaire,*(m_sprite.getTexture())));
	m_tacheEnCours=false;
}

void Unite::agirVraiment(Tache tache)
{
	m_construire=tache.type;
	allerA(tache.position);
}