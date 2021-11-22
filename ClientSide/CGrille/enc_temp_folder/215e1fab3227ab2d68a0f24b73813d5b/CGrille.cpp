

#include "CGrille.h"
#include <iostream>
#include <windows.h>

CGrille::CGrille()
{
    grille[1][1] = Case::BATEAU;
}

CGrille::Case CGrille::getCase(int ligne, int colonne)
{
    //grille[1][1] = Case::BATEAU;
    //Case CaseTeste = ;
    //if (CaseTeste == Case::BATEAU)std::cout << "bateau";
    //if (CaseTeste == Case::EAU)std::cout << "eau";
    //system("pause");
    return grille[ligne][colonne];
}

void CGrille::setCase(int ligne, int colonne, Case type)
{
    grille[ligne][colonne] = type;
}

void CGrille::afficherGrille()
{
    char colonnel = 'A';
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 9);
    bool valeurOuLigne = true;
    for (int i = 0; i < (ligne+1) * 2 + 1 ; i++) {
        if (valeurOuLigne == true) {
            //if (i == 0) {
              //  std::cout << "+---";
            //}
            for (int f = 0; f < colonne+1; f++) {
                std::cout << "+---";
            }
            std::cout << "+" << std::endl;
            valeurOuLigne = false;
        }
        else {
            for (int f = 0; f < colonne+1; f++) {
          
                if (i < 2 & f > 0) {

                    std::cout << "| ";
                    SetConsoleTextAttribute(hConsole, 15);
                    std::cout << char(colonnel + f-1) << " ";
                    SetConsoleTextAttribute(hConsole, 9);
                }
                else
                {
                    //if (ligne == 2) {

                        std::cout << "| ";
                        //SetConsoleTextAttribute(hConsole, 15);
                        std::cout << "  ";
                        //SetConsoleTextAttribute(hConsole, 9);
                    //}
                }
                
            }
            std::cout << "|" << std::endl;
            valeurOuLigne = true;

        }

    }
    system("pause");
}

std::vector<std::string> CGrille::saisieJoueur()
{
    return std::vector<std::string>();
}

bool CGrille::partiePerdue()
{
    return false;
}
