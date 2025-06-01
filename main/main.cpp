#include <iostream>
#include "ants.hpp"

extern void algo1(Fourmiliere&);
extern void algo2(Fourmiliere&);
extern void algo3(Fourmiliere&);
extern void algo4(Fourmiliere&);
extern void algo5(Fourmiliere&);

int main() {
    Structur s;
    s.afficherSchema();

    Fourmiliere colonie;

    colonie.appliquerConfiguration(algo1);
    colonie.initialiser();

    int tour = 0;
    const int MAX_TOURS = 1000;

    while (!colonie.termine() && tour < MAX_TOURS) {
        std::cout << "Tour " << ++tour << "\n";
        colonie.afficher();
        std::cout << "Fourmis au dortoir : " << colonie.salles[colonie.index_sd].fourmis.size() << "\n\n";
        colonie.tour();
    }

    if(tour >= MAX_TOURS)
        std::cerr << "\nERREUR : Temps maximal dépassé" << std::endl;
    else
        std::cout << "\nTous les fourmis ont atteint le dortoir en " << tour << " tours" << std::endl;

    return 0;
}
