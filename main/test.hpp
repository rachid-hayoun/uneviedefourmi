#include "ants.hpp"
#include <iostream>

using namespace std;

const int F = 10;      
const int SALLES = 6; 

////////////////////////    Schéma ASCII    //////////////////////////////////////

void Structur::afficherSchema() {
    cout << " ________________________________________________________" << endl;
    cout << "|           |  V | S1 | S2 | S3 | S4 | S5 | S6 | Dortoir |" << endl;
    cout << "| Capacite  |--------------------------------------------|" << endl;
    cout << "|           | 10 | 2  | 2  | 2  | 2  | 2  | 2  |    10   |" << endl;
    cout << " ________________________________________________________" << endl;
}

Fourmiliere::Fourmiliere() : salles(SALLES + 2), graphe(SALLES + 2) {
    for (int i = 0; i <= SALLES + 1; i++) {
        salles[i].capacite = (i == 1 || i == SALLES + 1) ? F : 2;
    }
    for (int i = 0; i <= SALLES; i++) {
        graphe[i].push_back(i + 1);
    }
}

/////////////////////         Vestibule Salle 0      //////////////////////////////

void Fourmiliere::initialiser() {
    salles[0].fourmis.clear();
    for (int i = 1; i <= F; i++) {
        salles[0].fourmis.push_back(i);
    }
    for (int i = 1; i <= SALLES + 1; i++)
        salles[i].fourmis.clear();
}


////////////////////        Checkpoint des salles   //////////////////////////////

void Fourmiliere::afficher() {
    for (int i = 0; i <= SALLES + 1; i++) {
        if (i == 0)
            cout << "Vestibule";
        else if (i == SALLES + 1)
            cout << "Dortoir ";
        else
            cout << "Salle " << i << " ";
        cout << " (" << salles[i].fourmis.size() << " fourmis): ";
        for (int f : salles[i].fourmis) cout << f << " ";
        cout << endl;
    }
    cout << "___________________________________________________" << endl;
}

/////////////////////////       Déplacement        /////////////////////////////////

void Fourmiliere::tour() {
    for (int i = SALLES; i >= 0; i--) {
        if (!graphe[i].empty()) {
            int next_salle = graphe[i].front();
            int deplacements = 0;
            while (!salles[i].fourmis.empty() &&
                   salles[next_salle].fourmis.size() < salles[next_salle].capacite &&
                   deplacements < 2) {
                int fourmi = salles[i].fourmis.front();
                salles[i].fourmis.pop_front();
                salles[next_salle].fourmis.push_back(fourmi);
                deplacements++;
            }
        }
    }
}


//////////////    Vérifie si toutes les fourmis sont arrivées au dortoir  ////////////

bool Fourmiliere::termine() {
    return salles[SALLES + 1].fourmis.size() == F;
}
