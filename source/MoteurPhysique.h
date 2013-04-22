#ifndef DEF_MOTEURPHYSIQUE
#define DEF_MOTEURPHYSIQUE

#include <SFML/Graphics.hpp>
#include "Objet/Unite.h"
#include "Objet/Batiment.h"
#include "Bouton/BoutonTexte.h"
#include "Bouton/BoutonImage.h"
#include "Interface/Interface.h"
#include "EtreVivant/Animal.h"
#include "EtreVivant/Plante.h"
#include <vector>
#include <algorithm>
#include "Reseau/Serveur.h"
#include "Reseau/Client.h"
#include <sstream>
#include <iostream>
#include <cstdlib> 
#include <ctime> 

class MoteurPhysique
{
	public://methodes publiques
	MoteurPhysique();
	void lancer();
	
	private://methodes privées
	void gererLesEvenements();
	void afficher();
	void traiter();
	
	private:
	//attributs principaux
	sf::RenderWindow * m_app;
	
	//attributs graphiques
	sf::View * m_vue;
	sf::Texture m_textureSol;
	sf::Sprite m_spriteSol;
	sf::Texture m_imageChien;
	sf::Texture m_imageMaison;
	sf::Texture m_imageVache;
	sf::Texture m_imageChat;
	sf::Texture m_imageHerbe;
	
	//atributs divers
	Interface * m_interface;
	std::vector<Objet*> m_objets;
	bool m_rectangleSelectionAffiche;
	sf::Vector2f m_positionDebutSelection;
	float m_tempsEcoule;
	sf::Vector2f m_coordonneesSouris;
	BoutonTexte * m_boutonTexte;
	sf::Font m_police;
	Serveur m_serveur;
	Client * m_client;
	std::string m_proprietaire;
	sf::Clock m_horloge;
	sf::Clock m_horlogeFrame;
	sf::Thread * m_threadServeur;
	sf::Thread * m_threadClient;
	sf::FloatRect * m_rectangleSelection;
};

#endif
