#include "ants.hpp"
#include <iostream>
#include <climits>  // Pour INT_MAX
using namespace std;

void Structur::afficherSchema() {
    cout << " ___________" << endl;
    cout << "|           |" << endl;
    cout << "| Programme |" << endl;
    cout << "|___________|" << endl;
}

void Fourmiliere::appliquerConfiguration(void (*config)(Fourmiliere&)) {
    salles.clear();
    graphe.clear();
    config(*this);
}

void Fourmiliere::initialiser() {
    salles[0].fourmis.clear();
    for (int i = 1; i <= F; i++) {
        salles[0].fourmis.push_back(i);
    }
    for (size_t i = 1; i < salles.size(); ++i)
        salles[i].fourmis.clear();
}

void Fourmiliere::afficher() {
    for (size_t i = 0; i < salles.size(); ++i) {
        cout << "S" << i << " (" << salles[i].fourmis.size() << "/" << salles[i].capacite << "): ";
        for (int f : salles[i].fourmis) cout << f << " ";
        cout << endl;
    }
    cout << "-----------------------------------------------------" << endl;
}

void Fourmiliere::tour() {
    vector<deque<int>> nouvelles_salles(salles.size());

    for (int i = salles.size() - 1; i >= 0; --i) {
        for (int next : graphe[i]) {
            while (!salles[i].fourmis.empty() &&
                   (nouvelles_salles[next].size() + salles[next].fourmis.size() < salles[next].capacite || salles[next].capacite == 0)) {
                int f = salles[i].fourmis.front();
                salles[i].fourmis.pop_front();
                nouvelles_salles[next].push_back(f);
            }
        }
    }

    for (size_t i = 0; i < salles.size(); ++i) {
        while (!nouvelles_salles[i].empty()) {
            salles[i].fourmis.push_back(nouvelles_salles[i].front());   
            nouvelles_salles[i].pop_front();
        }
    }
}

bool Fourmiliere::termine() {
    if (index_sd < 0 || index_sd >= (int)salles.size())
        return false;
    return salles[index_sd].fourmis.size() == F;
}

// ----------- Algorithmes -----------

void algo1(Fourmiliere& f) {
    f.F = 5;
    f.index_sd = 3;
    f.salles.resize(4);
    f.graphe.resize(4);

    f.salles[3].capacite = f.F;

    f.graphe[0] = {1};
    f.graphe[1] = {2};
    f.graphe[2] = {3};
}

void algo2(Fourmiliere& f) {
    f.F = 5;
    f.index_sd = 3;
    f.salles.resize(4);
    f.graphe.resize(4);

    f.salles[3].capacite = f.F;

    f.graphe[0] = {1};
    f.graphe[1] = {2};
    f.graphe[2] = {3};
    f.graphe[3] = {0}; // boucle Sd - Sv
}

void algo3(Fourmiliere& f) {
    f.F = 5;
    f.index_sd = 4;
    f.salles.resize(5);
    f.graphe.resize(5);

    f.salles[4].capacite = f.F;

    f.graphe[0] = {1};   // Sv - S1
    f.graphe[1] = {2, 3}; // S1 - S2 et S1 - S4
    f.graphe[2] = {3};   // S2 - S3
    f.graphe[3] = {4};   // S4 - Sd
    // Note : pas de sortie de S3, fourmis bloquées mais pas dérangeant pour test
}

void algo4(Fourmiliere& f) {
    f.F = 10;
    f.index_sd = 7;
    f.salles.resize(8);
    f.graphe.resize(8);

    f.salles[1].capacite = 2;
    f.salles[4].capacite = 2;
    f.salles[7].capacite = f.F;

    f.graphe[0] = {1};     // Sv - S1
    f.graphe[1] = {2, 3};  // S1 - S2, S1 - S3
    f.graphe[2] = {4};     // S2 - S4
    f.graphe[3] = {4};     // S3 - S4
    f.graphe[4] = {5, 6};  // S4 - S5, S4 - S6
    f.graphe[5] = {7};     // S5 - Sd
    f.graphe[6] = {7};     // S6 - Sd

}

void algo5(Fourmiliere& f) {
    f.F = 50;
    f.index_sd = 9;
    f.salles.resize(15);
    f.graphe.resize(15);

    f.salles[0].capacite = INT_MAX; // Sv illimité
    f.salles[1].capacite = 8;
    f.salles[2].capacite = 4;
    f.salles[3].capacite = 2;
    f.salles[4].capacite = 4;
    f.salles[5].capacite = 2;
    f.salles[6].capacite = 4;
    f.salles[7].capacite = 2;
    f.salles[8].capacite = 5;
    f.salles[9].capacite = f.F;      // Sd
    f.salles[13].capacite = 4;
    f.salles[14].capacite = 2;

    f.graphe[0] = {1};
    f.graphe[1] = {2, 6};
    f.graphe[2] = {3, 5};
    f.graphe[3] = {4};
    f.graphe[4] = {9};
    f.graphe[5] = {4};
    f.graphe[6] = {7, 8};
    f.graphe[7] = {9, 10};
    f.graphe[8] = {11, 12};
    f.graphe[9] = {};       // Dortoir pas de sorties
    f.graphe[10] = {14};
    f.graphe[11] = {13};
    f.graphe[12] = {13};
    f.graphe[13] = {9};
    f.graphe[14] = {9};
}
