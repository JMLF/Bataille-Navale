

#include "CGrille.h"
#include <iostream>
#include <windows.h>


CGrille::CGrille()
{

    nbPorteAvion = 1;
    nbCroiseur = 1;
    nbTorpilleur = 0;
    nbSousMarin = 0;
    colonne = 10;
    ligne = 10;
    //grille[9][9] = Case::VIDE;
    for (int i = 0; i < ligne ; i++) {
        for (int f = 0; f < colonne ; f++) {
            grille[i][f] = Case::VIDE;
            //if (grille[i][f] == Case::BATEAU)std::cout << "bateau";
            //if (grille[i][f] == Case::VIDE)std::cout << "eau";
            //std::cout << i << f << std::endl;
        }
    }
    
    
    //grille[][] = Case::VIDE;
   //grille[1][1] = Case::BATEAU;
   //grille[10][4] = Case::VIDE;
}





void CGrille::InitGrille() {

   
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


                     /*-------------------------------
                        // GESTION DES CASES SUR LA GRILLE JOUEUR
                     -------------------------------*/



                        Case etat = getCase(k-1, f);

                        switch (etat) {
                        case Case::BATEAU : // on affiche nos bateaux
                            std::cout << "B ";
                            break;
                           
                        case Case::TOUCHEJ :  // on affiche les cases ou l'ennemi a toucher nos bateaux
                            SetConsoleTextAttribute(hConsole, 13);
                            std::cout << "X ";
                            SetConsoleTextAttribute(hConsole, 9);
                            break;
                        case Case::EAUJ: //on affiche les cases ou il a tirer
                            SetConsoleTextAttribute(hConsole, 9);
                            std::cout << "~ ";
                            //SetConsoleTextAttribute(hConsole, 9);
                            break;


                        case Case::VIDE:
                        default :  std::cout << "  ";
                        
                        }
                       

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
                    SetConsoleTextAttribute(hConsole, 4); // couleur rouge
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
                    else { //si on ne se trouve pas sur la premiere colonne : 
                        

                        /*-------------------------------
                        // GESTION DES CASES SUR LA GRILLE ENNEMIE
                     -------------------------------*/





                        std::cout << "| ";
                        Case etat = getCase(k - 1, f); // on affiche les cases ou le joueur a tirer

                        switch (etat) {
                        case Case::TOUCHEE: //si le joueur a toucher un bateau
                            SetConsoleTextAttribute(hConsole, 13); // violet
                            std::cout << "X ";
                            SetConsoleTextAttribute(hConsole, 4); //rouge
                            break;
                        case Case::EAUE: // si il a tirer a coté
                            SetConsoleTextAttribute(hConsole, 9); //bleu
                            std::cout << "~ ";
                            SetConsoleTextAttribute(hConsole, 4); //rouge
                            break;
                        case Case::VIDE: // si rien n'a été fait sur la case
                        default:  std::cout << "  ";

                        }

                    }
                }


            }
            std::cout << "|" << std::endl; // on termine le tableau par un | pour fermer le tableau
            valeurOuLigne = true; // on repasse sur une ligne de séparation

        }




    }




    
    // et on reboucle jusqu'a la finalisation du tableau.
    system("pause");
    SetConsoleTextAttribute(hConsole, 15);




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

std::string CGrille::placerBateau()
{
    Case grille2[11][11]; //on déclare une grille de sauvegarde
    system("CLS");
    bool selection = false;
    int k = 0;
    enum TypeBateau { PORTEAVION, CROISEUR, TORPILLEUR, SOUSMARIN };


    while ((nbCroiseur + nbPorteAvion + nbSousMarin + nbTorpilleur) > 0) { // tant que tout les bateaux n'ont pas été placer :
        while (selection == false) { //on crée un menu pour selectionner
            
            system("CLS");
            if (k == 4) k = 0; 
            if (GetKeyState('Z') & 0x8000) // Si la touche Z est préssée on navigue dans le menu
            {
                if (k == 4) k = 0;
                else { k++; }
            }
            switch (k)
            { //en fonction de k on affiche l'objet sele
            case PORTEAVION: std::cout << " >Porte-Avion [][][][][] " << nbPorteAvion << std::endl << "Croiseur [][][][]" << std::endl << "Torpilleur [][][]" << std::endl << "Sous-Marin [][]" << std::endl;
                break;
            case CROISEUR: std::cout << "Porte-Avion [][][][][]" << std::endl << " >Croiseur [][][][] " << nbCroiseur << std::endl << "Torpilleur [][][]" << std::endl << "Sous-Marin [][]" << std::endl;
                break;
            case TORPILLEUR: std::cout << "Porte-Avion [][][][][]" << std::endl << "Croiseur [][][][]" << std::endl << " >Torpilleur [][][] " << nbTorpilleur << std::endl << "Sous-Marin [][]" << std::endl;
                break;
            case SOUSMARIN: std::cout << "Porte-Avion [][][][][]" << std::endl << "Croiseur [][][][]" << std::endl << "Torpilleur [][][]" << std::endl << " >Sous-Marin [][] " << nbSousMarin << std::endl;
                break;
            }
            //std::cout << k;
            Sleep(30);
            if (GetKeyState('E') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
            {
                switch (k)
                {
                case PORTEAVION:
                    k = 4;
                    if (nbPorteAvion != 0) {
                        selection = true;
                        break;
                    }
                    else {
                        std::cout << " Plus de bateaux de ce type a placer" << std::endl;
                        system("pause");
                        break;
                    }
                case CROISEUR:
                    k = 3;
                    if (nbCroiseur != 0) {
                        selection = true;
                        break;
                    }
                    else {
                        std::cout << " Plus de bateaux de ce type a placer" << std::endl;
                        system("pause");
                        break;
                    }
                case TORPILLEUR:
                    k = 2;
                    if (nbTorpilleur != 0) {
                        selection = true;
                        break;
                    }
                    else {
                        std::cout << " Plus de bateaux de ce type a placer" << std::endl;
                        system("pause");
                        break;
                    }
                case SOUSMARIN:
                    k = 1;
                    if (nbSousMarin != 0) {
                        selection = true;
                        break;
                    }
                    else {
                        std::cout << " Plus de bateaux de ce type a placer" << std::endl;
                        system("pause");
                        break;
                    }


                    
                    


                }
            }
        }
        int coordoY = ligne / 2, coordoX = colonne / 2;
        
    
        for (int i = 0; i < ligne; i++) {
            for (int f = 0; f < colonne; f++) {
                grille2[i][f] = grille[i][f];
                //if (grille[i][f] == Case::BATEAU)std::cout << "bateau";
                //if (grille[i][f] == Case::VIDE)std::cout << "eau";
                //std::cout << i << f << std::endl;
            }
        }

       






        //PLACEMENT DU BATEAU
        bool selection2 = false;
        bool direction = false;
        while (selection2 == false) {

            if (direction == false) {
                for (int i = 0; i < k + 1; i++) {
                    grille[coordoY][coordoX + i] = Case::BATEAU;
                }
            }
            else {
                for (int i = 0; i < k + 1; i++) {
                    grille[coordoY + i][coordoX] = Case::BATEAU;
                }
            }
            afficherGrille();
            if (GetKeyState('Z') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
            {
                if (direction == false) {
                    for (int i = 0; i < k + 1; i++) {
                        grille[coordoY][coordoX + i] = Case::VIDE;
                    }
                }
                else {
                    for (int i = 0; i < k + 1; i++) {
                        grille[coordoY + i][coordoX] = Case::VIDE;
                    }
                }
                coordoY--;
                system("CLS");
            }
            if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
            {
                if (direction == false) {
                    for (int i = 0; i < k + 1; i++) {
                        grille[coordoY][coordoX + i] = Case::VIDE;
                    }
                }
                else {
                    for (int i = 0; i < k + 1; i++) {
                        grille[coordoY + i][coordoX] = Case::VIDE;
                    }
                }
                coordoX--;
                system("CLS");
            }
            if (GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
            {
                if (direction == false) {
                    for (int i = 0; i < k + 1; i++) {
                        grille[coordoY][coordoX + i] = Case::VIDE;
                    }
                }
                else {
                    for (int i = 0; i < k + 1; i++) {
                        grille[coordoY + i][coordoX] = Case::VIDE;
                    }
                }
                coordoY++;
                system("CLS");
            }
            if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
            {
                if (direction == false) {
                    for (int i = 0; i < k + 1; i++) {
                        grille[coordoY][coordoX + i] = Case::VIDE;
                    }
                }
                else {
                    for (int i = 0; i < k + 1; i++) {
                        grille[coordoY + i][coordoX] = Case::VIDE;
                    }
                }
                coordoX++;
                system("CLS");
            }
            Sleep(50);

            if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
            {
                if (direction == false) {
                    for (int i = 0; i < k + 1; i++) {
                        grille[coordoY][coordoX + i] = Case::VIDE;
                    }
                    direction = true;
                }
                else {
                    for (int i = 0; i < k + 1; i++) {
                        grille[coordoY + i][coordoX] = Case::VIDE;
                    }
                    direction = false;
                }
                system("CLS");
            }





            if (GetKeyState('E') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
            {

                if (grille[coordoY][coordoX] == grille2[coordoY][coordoX]) {

                    std::cout << "Placement impossible" << std::endl;
                    system("pause");
                    throw("Superposition de bateaux");
                }



                //Gestion de la superposition des bateaux 
                for (int i = 0; i < ligne; i++) {
                    for (int f = 0; f < colonne; f++) {

                        if (grille[i][f] == Case::BATEAU) {
                            /*if (grille2[i][f] == grille[i][f]) {
                                std::cout << "Placement impossible" << std::endl;
                                //
                                throw("Superposition de bateaux");
                            }*/
                            //else { grille2[i][f] = grille[i][f]; }

                            grille2[i][f] = grille[i][f];
                        }
                    }
                }
                ////////////////////////////////////////////////






                for (int i = 0; i < ligne; i++) {
                    for (int f = 0; f < colonne; f++) {
                        grille[i][f] = grille2[i][f];
                    }
                }










                selection2 = true;
                selection = false;
                switch (k)
                {
                case 4: nbPorteAvion--; std::cout << nbPorteAvion; system("pause"); break;
                case 3: nbCroiseur--; break;
                case 2: nbTorpilleur--; break;
                case 1: nbSousMarin--; break;
                }
            }
        }

    }




    system("pause");
    return "reusite";



    
}
