#include "Benchmark.h"

Benchmark::Benchmark(const sf::Vector2f position,const sf::Font & police,const std::string nomMesure,int nbMesureAFaire,const float taille,const sf::Color & couleur) : Text(nomMesure,police,taille),m_nbMesureAFaire(nbMesureAFaire),m_nbMesure(0),m_sommeMesure(0),m_nomMesure(nomMesure)
{
    setPosition(position);
    setColor(couleur);
}

void Benchmark::debut()
{
    m_horloge.restart();
}

void Benchmark::fin()
{
    m_sommeMesure+=m_horloge.getElapsedTime().asMilliseconds();
    m_nbMesure++;
    if(m_nbMesure==m_nbMesureAFaire)
    {
        setString(m_nomMesure+" : "+std::to_string(m_sommeMesure/m_nbMesure));
        m_nbMesure=0;
        m_sommeMesure=0;
    }
}
