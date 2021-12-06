#include "CGrille.h"
using namespace std;
int main() {
    CGrille grille;
    grille.bateauToucherAllier(1, 1);
    grille.tirLoupeEnnemi(1, 2);
    grille.bateauToucherEnnemi(1, 3);
    grille.tirLoupeJoueur(1, 4);
    grille.setCase(2, 1, CGrille::Case::BATEAU);
    grille.afficherGrille();
    system("pause");
}