#pragma once
#include <deque>
#include <vector>

struct Salle {
    int capacite = 0;
    std::deque<int> fourmis;
};

class Fourmiliere {
public:
    std::vector<Salle> salles;
    std::vector<std::vector<int>> graphe;
    int F = 0;
    int index_sd = -1;

    void appliquerConfiguration(void (*config)(Fourmiliere&));
    void initialiser();
    void afficher();
    void tour();
    bool termine();
};

class Structur {
public:
    void afficherSchema();
};