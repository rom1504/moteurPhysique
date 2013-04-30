#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <SFML/Graphics.hpp>

class Benchmark : public sf::Text
{
public:
    Benchmark(const sf::Vector2f position,const sf::Font & police,const std::string nomMesure="Mesure",int nbMesureAFaire=10,const float taille=15,const sf::Color & couleur=sf::Color(255, 255, 255));
    void debut();
    void fin();

private:
    int m_nbMesureAFaire;
    int m_nbMesure;
    int m_sommeMesure;
    sf::Clock m_horloge;
    std::string m_nomMesure;
};

#endif // BENCHMARK_H
