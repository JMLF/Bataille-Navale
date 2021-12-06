
///\mainpage 
///\file ClientBatailleNavale.cpp
///\brief Fichier main du client, utilise les classes CGrille et CConnectionServeur




#include "CConnectionServeur.h"
#include "CGrille.h"
#include <iostream>

///\fn main
///\brief fonction main, prend des argument en ligne de commande 
int main(int argc, char* argv[])
{
    system("mode con LINES=70 COLS=100");
    //Verif des arguments -----------------------------------------------------------------------------------------

    if (argc != 3) //different de 3 car exe vaut pour 1
    {
        std::cout << " manque 1 argument ( IP / Port ) " << std::endl;
        return 0;
    }

    std::string IP_SERVEUR = argv[1];
    std::string port = argv[2];
    //--------------------------------------------------------------------------------------------------------------

    CConnectionServeur connection(IP_SERVEUR, port);
    connection.initConnec();
    connection.connection(); //on se connecte içi 
    std::cout << "Connection en cour " << std::endl;
    CGrille grille;
    std::string message;

    message = connection.reception(); //reception de l'accusé de conenction
    std::cout << message << std::endl;
    message = connection.reception(); //reception du message qui dit qu'on doit placer les bateaux
    std::cout << message << std::endl;
    Sleep(10);
    grille.placerBateau();
    message = connection.reception(); //reception du message qui dit qu'on peux parler ou que l'autre joueur place ses bateau
    std::cout << message << std::endl;

   
   

    if (message == "Serveur: votre tour de jouer") //on previent le joueur 2 que l'on a fini de placer les bateaux 
    {

        connection.envoi("joueur: J'ai ini de placer mes bateaux");
        std::string etats;
        int etat(0);
        int xTemp = 0;
        int yTemp = 0;
        do
        {
              
            std::string discussion;
            std::string messageEnnemi;
              
            messageEnnemi = connection.reception();
            std::cout << messageEnnemi << std::endl;
             
            // declaration --------------------------------------------------------------
            int x;
            int y;
            CGrille::resultat lettre;
            CGrille::resultat lettreAenvouyer = CGrille::resultat::F;
            CGrille::Case Case;
            // ---------------------------------------------------------------------------


            //analyse de la trame recu ---------------------------------------------------  
            //mettre a jour la map de l'ennemi avec les coordonné CoordonneTemp + lettre
            grille.serialisation(x, y, messageEnnemi, lettre);
     
            if (lettre == CGrille::resultat::F)
            {
               
                Case = grille.getCase(x, y);
                
                if (Case == CGrille::Case::BATEAU)
                {
                    grille.XGrilleJoueur(x, y);
                    lettreAenvouyer = CGrille::resultat::T;

                }
                if (Case == CGrille::Case::VIDE)
                {
                    grille.TildGrilleJoueur(x, y);
                    lettreAenvouyer = CGrille::resultat::L;

                }
            }
              
            if (lettre == CGrille::resultat::T)
            {
                grille.XGrilleEnnemie(xTemp, yTemp);
                std::cout << "valeur xtzmp et y temp " << xTemp << " " << yTemp << std::endl;
                system("pause");


                Case = grille.getCase(x, y);
                if (Case == CGrille::Case::BATEAU)
                {
                    grille.XGrilleJoueur(x, y);
                    lettreAenvouyer = CGrille::resultat::T;
                }
                if (Case == CGrille::Case::VIDE)
                {
                    grille.TildGrilleJoueur(x, y);
                    lettreAenvouyer = CGrille::resultat::L;
                }

            }
              
            if (lettre == CGrille::resultat::L)
            {
                grille.TildGrilleEnnemie(xTemp, yTemp);
                std::cout << "valeur xtzmp et y temp " << xTemp << yTemp << std::endl;
                system("pause");


                Case = grille.getCase(x, y);
                if (Case == CGrille::Case::BATEAU)
                {
                    grille.XGrilleJoueur(x, y);
                    lettreAenvouyer = CGrille::resultat::T;
                }
                if (Case == CGrille::Case::VIDE)
                {
                    grille.TildGrilleJoueur(x, y);
                    lettreAenvouyer = CGrille::resultat::L;
                }
            }
              
            if (lettre == CGrille::resultat::P)
            {
                //partie remporté 
                std::cout << " Victoire";
                return 0;
            }
              
            //fin analyse trame -------------------------------------------------------
            
            discussion = connection.reception();
            std::cout << discussion << std::endl;
              
            std::cout << "Ou voulez-vous envoyer un missile ?" << std::endl;
            std::cin >> discussion;

            int taille = discussion.size(); //si la trame est sup a 2, x fait 2 chiffres
           
            if (taille > 2) //donc le chiffre est 10
            {
                xTemp = std::stoi(discussion.substr(0, 2)); 

                if (discussion.at(2) == 'A')
                {
                    yTemp = 1;
                }
                if (discussion.at(2) == 'B')
                {
                    yTemp = 2;
                }
                if (discussion.at(2) == 'C')
                {
                    yTemp = 3;
                }
                if (discussion.at(2) == 'D')
                {
                    yTemp = 4;
                }
                if (discussion.at(2) == 'E')
                {
                    yTemp = 5;
                }
                if (discussion.at(2) == 'F')
                {
                    yTemp = 6;
                }
                if (discussion.at(2) == 'G')
                {
                    yTemp = 7;
                }
                if (discussion.at(2) == 'H')
                {
                    yTemp = 8;
                }
                if (discussion.at(2) == 'I')
                {
                    yTemp = 9;
                }
                if (discussion.at(2) == 'J')
                {
                    yTemp = 10;
                }
            }
            else
            {
                xTemp = std::stoi(discussion.substr(0, 1)); //le chiffre n'est pas 10

                if (discussion.at(1) == 'A')
                {
                    yTemp = 1;
                }
                if (discussion.at(1) == 'B')
                {
                    yTemp = 2;
                }
                if (discussion.at(1) == 'C')
                {
                    yTemp = 3;
                }
                if (discussion.at(1) == 'D')
                {
                    yTemp = 4;
                }
                if (discussion.at(1) == 'E')
                {
                    yTemp = 5;
                }
                if (discussion.at(1) == 'F')
                {
                    yTemp = 6;
                }
                if (discussion.at(1) == 'G')
                {
                    yTemp = 7;
                }
                if (discussion.at(1) == 'H')
                {
                    yTemp = 8;
                }
                if (discussion.at(1) == 'I')
                {
                    yTemp = 9;
                }
                if (discussion.at(1) == 'J')
                {
                    yTemp = 10;
                }
            }
          
              
           
            std::cout << std::endl;
            std::cout << discussion << std::endl;
            
            
            switch (lettreAenvouyer)
            {
            case CGrille::resultat::F:
                discussion = "F:" + discussion;
                break;
            case CGrille::resultat::T:
                discussion = "T:" + discussion;
                break;
            case CGrille::resultat::L:
                discussion = "L:" + discussion;
                break;
            case CGrille::resultat::G:
                discussion = "G:" + discussion;
                break;
            case CGrille::resultat::P:
                discussion = "F:" + discussion;
                break;

            }
              
            std::cout << discussion << std::endl;
            connection.envoi(discussion);
             
            grille.afficherGrille();
              
        } while (true);
    }

    if (message == "joueur: J'ai ini de placer mes bateaux") //si on reçoit le message que le joueur 2 a fini on peux envoyer une trame puisque c'est notre tour coté serveur
    {
        std::string etats;
        int etat(0);
        int xTemp = 0;
        int yTemp = 0;
        CGrille::resultat lettreAenvouyer;
        lettreAenvouyer = CGrille::resultat::F;
        do
        {
              
            std::string discussion;
            discussion = connection.reception();
             
            std::cout << discussion << std::endl;

            std::cout << "Ou voulez-vous envoyer un missile ?" << std::endl;
            std::cin >> discussion;
            std::cout << std::endl;
            
            int taille = discussion.size(); //si la trame est sup a 2, x fait 2 chiffres

            if (taille > 2) //donc le chiffre est 10
            {
                xTemp = std::stoi(discussion.substr(0, 2));

                if (discussion.at(2) == 'A')
                {
                    yTemp = 1;
                }
                if (discussion.at(2) == 'B')
                {
                    yTemp = 2;
                }
                if (discussion.at(2) == 'C')
                {
                    yTemp = 3;
                }
                if (discussion.at(2) == 'D')
                {
                    yTemp = 4;
                }
                if (discussion.at(2) == 'E')
                {
                    yTemp = 5;
                }
                if (discussion.at(2) == 'F')
                {
                    yTemp = 6;
                }
                if (discussion.at(2) == 'G')
                {
                    yTemp = 7;
                }
                if (discussion.at(2) == 'H')
                {
                    yTemp = 8;
                }
                if (discussion.at(2) == 'I')
                {
                    yTemp = 9;
                }
                if (discussion.at(2) == 'J')
                {
                    yTemp = 10;
                }
            }
            else
            {
                xTemp = std::stoi(discussion.substr(0, 1)); //le chiffre n'est pas 10

                if (discussion.at(1) == 'A')
                {
                    yTemp = 1;
                }
                if (discussion.at(1) == 'B')
                {
                    yTemp = 2;
                }
                if (discussion.at(1) == 'C')
                {
                    yTemp = 3;
                }
                if (discussion.at(1) == 'D')
                {
                    yTemp = 4;
                }
                if (discussion.at(1) == 'E')
                {
                    yTemp = 5;
                }
                if (discussion.at(1) == 'F')
                {
                    yTemp = 6;
                }
                if (discussion.at(1) == 'G')
                {
                    yTemp = 7;
                }
                if (discussion.at(1) == 'H')
                {
                    yTemp = 8;
                }
                if (discussion.at(1) == 'I')
                {
                    yTemp = 9;
                }
                if (discussion.at(1) == 'J')
                {
                    yTemp = 10;
                }
            }
          
            std::cout << std::endl;
            std::cout << discussion << std::endl;
          
            switch (lettreAenvouyer)
            {
            case CGrille::resultat::F:
                discussion = "F:" + discussion;
                break;
            case CGrille::resultat::T:
                discussion = "T:" + discussion;
                break;
            case CGrille::resultat::L:
                discussion = "L:" + discussion;
                break;
            case CGrille::resultat::G:
                discussion = "G:" + discussion;
                break;
            case CGrille::resultat::P:
                discussion = "F:" + discussion;
                break;

            }
            connection.envoi(discussion);
             //5
            std::string messageEnnemi = connection.reception();
            std::cout << messageEnnemi << std::endl;
             //6
            //ajouter une fonction de mise a jour de la map (fonction de serialisation)
       //analyse de la trame recu ---------------------------------------------------          
            int x;
            int y;
            CGrille::resultat lettre;
            //CGrille::resultat lettreAenvouyer; inschallah
            CGrille::Case Case;
            grille.serialisation(x, y, messageEnnemi, lettre);
             
            //mettre a jour la map de l'ennemi avec les coordonné CoordonneTemp + lettre 

         
           
            
                if (lettre == CGrille::resultat::F)
                {
                    Case = grille.getCase(x, y); 
                    
               
                    if (Case == CGrille::Case::BATEAU)
                    {
                        grille.XGrilleJoueur(x, y);
                        lettreAenvouyer = CGrille::resultat::T;
                    }
                    if (Case == CGrille::Case::VIDE)
                    {
                        grille.TildGrilleJoueur(x, y);
                        lettreAenvouyer = CGrille::resultat::L;
                    }
                }
                if (lettre == CGrille::resultat::T)
                {
                    grille.XGrilleEnnemie(xTemp, yTemp);
                    std::cout << "valeur xtzmp et y temp " << xTemp << yTemp << std::endl;
                    system("pause");

                    Case = grille.getCase(x, y);
                    if (Case == CGrille::Case::BATEAU)
                    {
                        grille.XGrilleJoueur(x, y);
                        lettreAenvouyer = CGrille::resultat::T;
                    }
                    if (Case == CGrille::Case::VIDE)
                    {
                        grille.TildGrilleJoueur(x, y);
                        lettreAenvouyer = CGrille::resultat::L;
                    }

                }
                if (lettre == CGrille::resultat::L)
                {
                    grille.TildGrilleEnnemie(xTemp, yTemp);
                    std::cout << "valeur xtzmp et y temp " << xTemp << yTemp << std::endl;
                    system("pause");

                    Case = grille.getCase(x, y);
                    if (Case == CGrille::Case::BATEAU)
                    {
                        grille.XGrilleJoueur(x, y);
                        lettreAenvouyer = CGrille::resultat::T;
                    }
                    if (Case == CGrille::Case::VIDE)
                    {
                        grille.TildGrilleJoueur(x, y);
                        lettreAenvouyer = CGrille::resultat::L;
                    }
                }
                if (lettre == CGrille::resultat::P)
                {
                    //partie remporté 
                    std::cout << " Victoire";
                    return 0;
                }

                //fin analyse trame -------------------------------------------------------

                 //8
                grille.afficherGrille();



            } while (true);

        }




        return(0); //a verif
}//main 





