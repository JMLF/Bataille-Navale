
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

  //  enum class trame{AVOUS=0,FIRE,TOUCH,MISS,WIN=4}; //plus utilisé

    if (message == "Serveur: votre tour de jouer") //on previent le joueur 2 que l'on a fini de placer les bateaux 
    {

        connection.envoi("joueur: J'ai ini de placer mes bateaux"); 
        std::string etats;
        int etat(0);
        int xTemp;
        int yTemp;
        do
        {
            
            std::string discussion;
            std::string messageEnnemi;
            messageEnnemi = connection.reception();
            std::cout <<  messageEnnemi << std::endl;
            
            //analyse de la trame recu ---------------------------------------------------          
            int x;
            int y;
            CGrille::resultat lettre;
            CGrille::resultat lettreAenvouyer;
            CGrille::Case Case;
            grille.serialisation(x,y,discussion,lettre);
            //mettre a jour la map de l'ennemi avec les coordonné CoordonneTemp + lettre 
           
            if (lettre == CGrille::resultat::F)
            {
                Case = grille.getCase(x, y);
                if (Case == CGrille::Case::BATEAU)
                {
                    grille.bateauToucherAllier(x, y);
                    lettreAenvouyer = CGrille::resultat::T;
                }
                if (Case == CGrille::Case::VIDE)
                {
                    grille.tirLoupeEnnemi(x, y);
                    lettreAenvouyer = CGrille::resultat::L;
                }
            }

            if (lettre == CGrille::resultat::T)
            {
                grille.bateauToucherEnnemi(xTemp, yTemp);

                Case = grille.getCase(x, y);
                if (Case == CGrille::Case::BATEAU)
                {
                    grille.bateauToucherAllier(x, y);
                    lettreAenvouyer = CGrille::resultat::T;
                }
                if (Case == CGrille::Case::VIDE)
                {
                    grille.tirLoupeEnnemi(x, y);
                    lettreAenvouyer = CGrille::resultat::L;
                }

            }
            if (lettre == CGrille::resultat::L)
            {
                grille.tirLoupeJoueur(xTemp, yTemp);

                Case = grille.getCase(x, y);
                if (Case == CGrille::Case::BATEAU)
                {
                    grille.bateauToucherAllier(x, y);
                    lettreAenvouyer = CGrille::resultat::T;
                }
                if (Case == CGrille::Case::VIDE)
                {
                    grille.tirLoupeEnnemi(x, y);
                    lettreAenvouyer = CGrille::resultat::L;
                }
            }
            if (lettre == CGrille::resultat::P)
            {
                //partie remporté 
                std::cout<< " Victoire";
                return 0;
            }
            
           

            //fin analyse trame -------------------------------------------------------
            discussion = connection.reception();
            std::cout << discussion << std::endl;
            std::cout << "Ou voulez-vous envoyer un missile ?" << std::endl;
            std::cin >> discussion;
            xTemp = std::stoi(std::to_string(discussion.at(0)));
           
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
            std::cout << std::endl;
           
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
            grille.afficherGrille();
            

          

        } while (true);
    }
    if (message == "joueur: J'ai ini de placer mes bateaux") //si on reçoit le message que le joueur 2 a fini on peux envoyer une trame puisque c'est notre tour coté serveur
    {
        std::string etats;
        int etat(0);
        int xTemp;
        int yTemp;
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
            xTemp = std::stoi(std::to_string(discussion.at(0)));

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
            std::cout << std::endl;

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

            std::string messageEnnemi = connection.reception();
            std::cout << messageEnnemi << std::endl;
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
                    grille.bateauToucherAllier(x, y);
                    lettreAenvouyer = CGrille::resultat::T;
                }
                if (Case == CGrille::Case::VIDE)
                {
                    grille.tirLoupeEnnemi(x, y);
                    lettreAenvouyer = CGrille::resultat::L;
                }
            }

            if (lettre == CGrille::resultat::T)
            {
                grille.bateauToucherEnnemi(xTemp, yTemp);

                Case = grille.getCase(x, y);
                if (Case == CGrille::Case::BATEAU)
                {
                    grille.bateauToucherAllier(x, y);
                    lettreAenvouyer = CGrille::resultat::T;
                }
                if (Case == CGrille::Case::VIDE)
                {
                    grille.tirLoupeEnnemi(x, y);
                    lettreAenvouyer = CGrille::resultat::L;
                }

            }
            if (lettre == CGrille::resultat::L)
            {
                grille.tirLoupeJoueur(xTemp, yTemp);

                Case = grille.getCase(x, y);
                if (Case == CGrille::Case::BATEAU)
                {
                    grille.bateauToucherAllier(x, y);
                    lettreAenvouyer = CGrille::resultat::T;
                }
                if (Case == CGrille::Case::VIDE)
                {
                    grille.tirLoupeEnnemi(x, y);
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

           
            grille.afficherGrille();

           

        } while (true);

    }

    
  

    return(0);
}


