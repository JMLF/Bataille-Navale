

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
    
    char colonnel = 'A'; //On établit un charactere qui sera incrémenter a chaque colonne pour l'affichage des lettres du haut du tableau
    int k = 0; //de meme pour les lignes, cette variable sera incrémentée a chaque ligne pour l'affichage des nombres du coté du tableau
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //sert a modifier la couleur de la console
    SetConsoleTextAttribute(hConsole, 9); // couleur bleue

    bool valeurOuLigne = true; // ce booléen nous servira a verifier dans chaque ligne si il faut y mettre un charactère ou faire une ligne
    /****************************************************

    //################# GRILLE JOUEUR ################
    
    *****************************************************/

    /* on fait ligne par ligne, sachant qu'une ligne se compose d'une ligne séparatrice, et d'une ligne ou se trouvent les valeurs. 
    Ligne séparatrice : +--+--+--+--+--+--+(...)
    Ligne des valeurs : |  |  |  |  |  |  |(...)

    D'ou la multiplication par 2.
    On remarque que la création des lignes du tableau fini par une ligne de valeur, pour que cela soit plus propre , on y ajoute une ligne
    séparatrice d'ou le +1 apres la multiplication.

    La ligne des caractere ne doit pas etre prise en compte dans le jeu , donc on y ajoute une ligne (ligne+1) pour avoir 11 lignes.
    */
    for (int i = 0; i < (ligne+1) * 2 + 1 ; i++) {  
        if (valeurOuLigne == true) { //Si on est sur une ligne séparatrice ...
            for (int f = 0; f < colonne+1; f++) {
                std::cout << "+---";
            }
            std::cout << "+" << std::endl; // on fini le tableau par un caratère '+' et un retour a la ligne
            valeurOuLigne = false; // on passe le bool a faux pour que la boucle revienne sur une ligne de valeurs
        }
        else { //Si on est sur une ligne de valeur...
            k++; // on incrémente les nombres du coté du tableau a chaque ligne de valeurs.
            for (int f = 0; f < colonne+1; f++) { // on s'occupe maintenant du tableau dans sa largeur, en fonction du nombre de colonnes. +1 pour decaler les valeurs en raison de la case 0,0
          
                if (i < 2 && f > 0) { // si on est sur la premiere ligne et que on se trouve pas sur la case 0,0 on affiche lettre par lettre dans chaque case

                    std::cout << "| ";
                    SetConsoleTextAttribute(hConsole, 15); // couleur blanc (F)
                    std::cout << char(colonnel + f-1) << " "; // on affiche la lettre correspondante.
                    SetConsoleTextAttribute(hConsole, 9); // couleur bleue
                }
                else // si on est pas sur la premiere ligne ou que on est sur la case 0.0 ...
                {
                    if (f == 0) { // si on est sur la premiere colonne :
                       

                        if (k < 11) { // on verifie que le format du nombre a afficher dans le tableau pour eviter un décalage quand on a deux chiffres 
                            if (k == 1) { // si c'est la zone 0.0 :
                                std::cout << "| ";
                                SetConsoleTextAttribute(hConsole, 15);
                                std::cout << "  ";
                                SetConsoleTextAttribute(hConsole, 9);
                            }
                            else { // si c'est les autres ( ex : 1.0 2.0 3.0 (...)
                                std::cout << "| ";
                                SetConsoleTextAttribute(hConsole, 15);
                                std::cout << k-1 << " "; // on affiche le nombre de la ligne en gerant le décallage de la zone 0.0
                                SetConsoleTextAttribute(hConsole, 9);
                            }
                        }
                        else { //si le format du nombre est a deuyx chiffre , on prend soin d'enlever un espace dans la nottation pour eviter un décallage sur le tableau
                            std::cout << "|";
                            SetConsoleTextAttribute(hConsole, 15);
                            std::cout << k-1 << " ";
                            SetConsoleTextAttribute(hConsole, 9);
                        }
                    }
                    else { //si on ne se trouve pas sur la premiere colonne , on fait une case vide : 
                        std::cout << "| ";
                        std::cout << "  ";
                        
                    }
                }

                
            }
            std::cout << "|" << std::endl; // on termine le tableau par un | pour fermer le tableau
            valeurOuLigne = true; // on repasse sur une ligne de séparation

        } 




    }



    /****************************************************

   //################# GRILLE ENNEMIE ################

   *****************************************************/
    valeurOuLigne = true;
    k = 0;
    SetConsoleTextAttribute(hConsole, 4);
    for (int i = 0; i < (ligne + 1) * 2 + 1; i++) {
        if (valeurOuLigne == true) { //Si on est sur une ligne séparatrice ...
            for (int f = 0; f < colonne + 1; f++) {
                std::cout << "+---";
            }
            std::cout << "+" << std::endl; // on fini le tableau par un caratère '+' et un retour a la ligne
            valeurOuLigne = false; // on passe le bool a faux pour que la boucle revienne sur une ligne de valeurs
        }
        else { //Si on est sur une ligne de valeur...
            k++; // on incrémente les nombres du coté du tableau a chaque ligne de valeurs.
            for (int f = 0; f < colonne + 1; f++) { // on s'occupe maintenant du tableau dans sa largeur, en fonction du nombre de colonnes. +1 pour decaler les valeurs en raison de la case 0,0

                if (i < 2 && f > 0) { // si on est sur la premiere ligne et que on se trouve pas sur la case 0,0 on affiche lettre par lettre dans chaque case

                    std::cout << "| ";
                    SetConsoleTextAttribute(hConsole, 15); // couleur blanc (F)
                    std::cout << char(colonnel + f - 1) << " "; // on affiche la lettre correspondante.
                    SetConsoleTextAttribute(hConsole, 4); // couleur bleue
                }
                else // si on est pas sur la premiere ligne ou que on est sur la case 0.0 ...
                {
                    if (f == 0) { // si on est sur la premiere colonne :


                        if (k < 11) { // on verifie que le format du nombre a afficher dans le tableau pour eviter un décalage quand on a deux chiffres 
                            if (k == 1) { // si c'est la zone 0.0 :
                                std::cout << "| ";
                                SetConsoleTextAttribute(hConsole, 15);
                                std::cout << "  ";
                                SetConsoleTextAttribute(hConsole, 4);
                            }
                            else { // si c'est les autres ( ex : 1.0 2.0 3.0 (...)
                                std::cout << "| ";
                                SetConsoleTextAttribute(hConsole, 15);
                                std::cout << k - 1 << " "; // on affiche le nombre de la ligne en gerant le décallage de la zone 0.0
                                SetConsoleTextAttribute(hConsole, 4);
                            }
                        }
                        else { //si le format du nombre est a deuyx chiffre , on prend soin d'enlever un espace dans la nottation pour eviter un décallage sur le tableau
                            std::cout << "|";
                            SetConsoleTextAttribute(hConsole, 15);
                            std::cout << k - 1 << " ";
                            SetConsoleTextAttribute(hConsole, 4);
                        }
                    }
                    else { //si on ne se trouve pas sur la premiere colonne , on fait une case vide : 
                        std::cout << "| ";
                        std::cout << "  ";

                    }
                }


            }
            std::cout << "|" << std::endl; // on termine le tableau par un | pour fermer le tableau
            valeurOuLigne = true; // on repasse sur une ligne de séparation

        }




    }




    
    // et on reboucle jusqu'a la finalisation du tableau.
    system("pause");














}

std::vector<std::string> CGrille::saisieJoueur(std::string abs, int ord, bool maGrille)
{





    std::vector<std::string> Coordonee;
    return Coordonee;
   
}

bool CGrille::partiePerdue()
{
    return false;
}
