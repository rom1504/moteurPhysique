#include "MoteurPhysique.h"

MoteurPhysique::MoteurPhysique()
{
	m_app=new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML Graphics");
	m_vue=new sf::View(sf::FloatRect(0,0,800,600));
	m_app->setView(*m_vue);
	m_textureSol.loadFromFile("image/herbe.png");
	m_spriteSol.setTexture(m_textureSol);
	m_spriteSol.setScale(20/m_spriteSol.getLocalBounds().width,20/m_spriteSol.getLocalBounds().height);
	srand((unsigned)time(0));
	int positionBaseX=500+rand()%7001,positionBaseY=500+rand()%5001;
	m_spriteSol.setPosition(0,0);
	sf::Image tempImgChien;
	sf::Image tempImgMaison;
	tempImgChien.loadFromFile("image/chien.png");
	tempImgChien.createMaskFromColor(sf::Color(255,255,255));
	tempImgMaison.loadFromFile("image/maison.png");
	tempImgMaison.createMaskFromColor(sf::Color(255,255,255));
	m_imageChien.loadFromImage(tempImgChien);
	m_imageMaison.loadFromImage(tempImgMaison);
	std::ostringstream out;
	out<<rand()%10000;
	m_proprietaire=out.str();
	m_interface=new Interface(m_app,m_objets,m_proprietaire);
	
	
	ObjetMobile * nouveau;
	m_vue->setCenter(positionBaseX+400,positionBaseY+300);
	for(int xi=positionBaseX+50;xi<=positionBaseX+700;xi+=100)
	{
		for(int yi=positionBaseY+50;yi<=positionBaseY+500;yi+=100)
		{
			nouveau=new ObjetMobile(m_imageChien,m_imageMaison,(float)(xi),(float)(yi),m_objets,m_proprietaire);
			//nouveau->allerA((float)sf::Randomizer::Random(50,750),(float)sf::Randomizer::Random(50,550));
			m_objets.push_back(nouveau);
		}
	}
	m_objets.push_back(new Batiment(m_imageMaison,positionBaseX-150,positionBaseY-150,m_objets,m_proprietaire,m_imageChien));
	m_app->setFramerateLimit(30);
	m_rectangleSelectionAffiche=false;
	m_police.loadFromFile("police/arial.ttf");
	m_boutonTexte=new BoutonTexte(sf::Vector2f(positionBaseX+100,positionBaseY+100),m_police,m_proprietaire);
	/*std::string truc;
	std::cin>>truc;
	if(truc=="serveur")
	{*/
		m_threadServeur=new sf::Thread(&Serveur::Run, &m_serveur);
		m_threadServeur->launch();
	//}
	m_client=new Client(m_objets,m_imageChien,m_imageMaison,m_proprietaire);
	m_threadClient=new sf::Thread(&Client::Run, m_client);
	m_threadClient->launch();
	m_horloge.restart();
}

void MoteurPhysique::gererLesEvenements()
{
	sf::Event evenement;
	sf::Vector2i positionSourisEcran;
	positionSourisEcran=sf::Mouse::getPosition();// à utiliser pour enlever la possibilité de cliquer  da ns;(j yterface : avancement : interface principalement, un peu de travail non encore terminé sur un gestionnaire de ressource... ( voir fichier objets.h entre autre )
	m_coordonneesSouris=m_app->mapPixelToCoords(positionSourisEcran);
	while(m_app->pollEvent(evenement))
	{
		if(m_interface->recevoirEvenement(evenement));
		else
		{
			if(evenement.type==sf::Event::Closed) {m_threadClient->terminate();m_threadServeur->terminate();m_app->close();}
			else if(evenement.type==sf::Event::MouseWheelMoved) m_vue->zoom(1+(float)(evenement.mouseWheel.delta)/10);
			if(positionSourisEcran.y<=550)
			{
				if(evenement.type==sf::Event::MouseButtonPressed && evenement.mouseButton.button==sf::Mouse::Left)
				{
					m_rectangleSelectionAffiche=true;
					m_positionDebutSelection=m_coordonneesSouris;
				}
				else if(evenement.type==sf::Event::MouseButtonReleased && evenement.mouseButton.button==sf::Mouse::Left && m_rectangleSelectionAffiche)
				{
					m_rectangleSelectionAffiche=false;
					//if(m_boutonTexte->clicked(m_coordonneesSouris)) m_app->close();// ?
				}
				else if(evenement.type==sf::Event::MouseButtonPressed && evenement.mouseButton.button==sf::Mouse::Right)
				{
					sf::Vector2f position;
					float x=0,y=0;
					int nombre=0;
					std::vector<Objet*> objetSelectionneDansLordre;
					for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i) if((*i)->selectionne() && (*i)->proprietaire()==m_proprietaire) 
					{
						objetSelectionneDansLordre.push_back(*i);
						nombre++;
					}
					float racineNombre=sqrt(nombre);// voir le sort : semble faire des segmentation fault en plus de ne servir à rien... ( sert quand même mais ne fait pas exactement ce qu'on veut )
					//std::sort(objetSelectionneDansLordre.begin(),objetSelectionneDansLordre.end(),triPlacement());
						// utiliser une structure adapté au tri et peut être un algorithme tout pret puis trier dans l'ordre du plus en haut au plus en bas et du plus à gauche au plus à droite et compter le nb d'élement
						// puis utiliser cette structure en la parcourant dans l'ordre pour choisir le placement des objets
						//but de tout ça : positionnement des objets dans un carré et dans le bon ordre ( que celui qui est déjà vers la gauche se positionne vers la gauche et de même pour les autres positions initiales )
					for(std::vector<Objet*>::iterator i=objetSelectionneDansLordre.begin();i!=objetSelectionneDansLordre.end();++i) 
					{
						position=m_coordonneesSouris;
						position.x+=x;
						position.y+=y;
						(*i)->agirAuClicDroit(position,sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift),0);
						m_client->envoyer((*i)->proprietaire(),(*i)->numero(),position);// à placer dans Objet plutôt ? ( pour ne pas avoir à être appelé à chaque appel de agirAuClicDroit et compagnie )
						x+=(*i)->largeur()*2;
						if(x>=(*i)->largeur()*2*racineNombre) // possibilité de compter le nb d'objet pour faire un carré ( à faire plus tard par ex )
						{
							y+=(*i)->hauteur()*2;
							x=0;
						}
					}
				}
			}
		}
	}
	m_tempsEcoule=m_horlogeFrame.getElapsedTime().asSeconds();
	m_horlogeFrame.restart();
	float deplacementVue=0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) deplacementVue=200*m_tempsEcoule*m_vue->getSize().x/800;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) m_vue->move(-deplacementVue,0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_vue->move(deplacementVue, 0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) m_vue->move(0, -deplacementVue);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) m_vue->move(0,deplacementVue);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) m_vue->zoom(1-m_tempsEcoule/2);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) m_vue->zoom(1+m_tempsEcoule/2);
	if(m_horloge.getElapsedTime().asMilliseconds()>10)
	{
		for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i) m_client->envoyerObjet(*i);
		m_horloge.restart();
	}
}

void MoteurPhysique::traiter()
{
	//for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i) (*i)->agir();// : à voir semble déclencher une segmentation fault mais aucune idée pourquoi
	for(std::vector<Objet*>::iterator i=m_objets.begin(),e=m_objets.end();i!=e;++i) (*i)->agir();
	if(m_rectangleSelectionAffiche)
	{
		float x1,x2,y1,y2;
		x1=std::min(m_positionDebutSelection.x,m_coordonneesSouris.x);
		y1=std::min(m_positionDebutSelection.y,m_coordonneesSouris.y);
		x2=std::max(m_positionDebutSelection.x,m_coordonneesSouris.x);
		y2=std::max(m_positionDebutSelection.y,m_coordonneesSouris.y);
		m_rectangleSelection=new sf::FloatRect(x1,y1,std::abs(x2-x1),std::abs(y2-y1));
		for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i) if(!((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) && (*i)->selectionne())) (*i)->setSelectionne(m_rectangleSelection->intersects(rectangleFDeSprite((*i)->sprite())));
		m_interface->actualiserSelection();
	}
}

void MoteurPhysique::afficher()
{
	m_app->clear();
	m_app->setView(m_app->getDefaultView());
	for(int xi=0;xi<40;xi++)
	{
		for(int yi=0;yi<30;yi++)
		{
			m_spriteSol.setPosition(xi*20,yi*20);
			m_app->draw(m_spriteSol);
		}
	}
	m_app->setView(*m_vue);
	for(std::vector<Objet*>::iterator i=m_objets.begin();i!=m_objets.end();++i)
	{
		m_app->draw((*i)->sprite());
		sf::RectangleShape r;
		r.setPosition((*i)->sprite().getPosition().x-1,(*i)->sprite().getPosition().y-1);
		r.setSize(sf::Vector2f((*i)->sprite().getGlobalBounds().width+1,(*i)->sprite().getGlobalBounds().height+1));
		r.setFillColor(m_interface->objetSelectionne()==(*i) ? sf::Color(0,0,255,100) : sf::Color(255,255,0,100));
		if((*i)->selectionne()) m_app->draw(r);
	}
	if(m_rectangleSelectionAffiche)
	{
		sf::RectangleShape r;
		r.setPosition(m_rectangleSelection->left,m_rectangleSelection->top);
		r.setSize(sf::Vector2f(m_rectangleSelection->width,m_rectangleSelection->height));
		r.setFillColor(sf::Color(255,255,255,0));
		r.setOutlineColor(sf::Color(255,255,255));
        r.setOutlineThickness(m_vue->getSize().x/800);
        m_app->draw(r);
	}
	m_app->draw(*m_boutonTexte);
	m_app->setView(m_app->getDefaultView());
	m_interface->afficher();
	m_app->setView(*m_vue);
	m_app->display();
}

void MoteurPhysique::lancer()
{
	while (m_app->isOpen())
	{
		gererLesEvenements();
		traiter();
		afficher();
	}
}