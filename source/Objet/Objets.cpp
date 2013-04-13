#include "Objets.h"

Objets()
{
	m_imageChien.LoadFromFile("..\\image\\chien.png");
	m_imageChien.CreateMaskFromColor(sf::Color(255,255,255));
	m_imageMaison.LoadFromFile("..\\image\\maison.png");
	m_imageMaison.CreateMaskFromColor(sf::Color(255,255,255));
}

Batiment * ajouterBatiment(float x,float y,std::string proprietaire,sf::Int8 numero=-1)
{
	Batiment * nouveau=new Batiment(m_imageBatiment,x,y,m_objets,proprietaire,m_imageMobile,numero);
	push_back(nouveau);
	return nouveau;
}

ObjetMobile * ajouterObjetMobile(float x,float y,std::string proprietaire,sf::Int8 numero=-1)
{
	ObjetMobile * nouveau=new ObjetMobile(m_imageMobile,x,y,m_objets,proprietaire,numero);
	push_back(nouveau);
	return nouveau;
}
