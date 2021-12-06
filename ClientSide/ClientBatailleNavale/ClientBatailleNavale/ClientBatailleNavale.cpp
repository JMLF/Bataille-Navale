
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

    //  enum class trame{AVOUS=0,FIRE,TOUCH,MISS,WIN=4}; //plus utilisé
    int erreurs(0);

    if (message == "Serveur: votre tour de jouer") //on previent le joueur 2 que l'on a fini de placer les bateaux 
    {

        connection.envoi("joueur: J'ai ini de placer mes bateaux");
        std::string etats;
        int etat(0);
        int xTemp = 0;
        int yTemp = 0;
        do
        {
            std::cout << erreurs << std::endl; erreurs++; //0
            std::string discussion;
            std::string messageEnnemi;
            std::cout << erreurs << std::endl; erreurs++; //1
            messageEnnemi = connection.reception();
            std::cout << messageEnnemi << std::endl;
            std::cout << erreurs << std::endl; erreurs++;
            //analyse de la trame recu ---------------------------------------------------          
            int x;
            int y;
            CGrille::resultat lettre;
            CGrille::resultat lettreAenvouyer = CGrille::resultat::F;
            CGrille::Case Case;

            grille.serialisation(x, y, messageEnnemi, lettre);
            std::cout << erreurs << std::endl; erreurs++; //2
            //mettre a jour la map de l'ennemi avec les coordonné CoordonneTemp + lettre 
           

         
            switch (lettre)
            {
            case CGrille::resultat::F:
                std::cout << "lettre = F" << std::endl;

                break;
            case CGrille::resultat::T:
                std::cout << "lettre = T"   << std::endl;

                break;
            case CGrille::resultat::L:
                std::cout << "lettre = L" << std::endl;

                break;
            case CGrille::resultat::G:
                std::cout << "lettre = G" << std::endl;

                break;
            case CGrille::resultat::P:
                std::cout << "lettre = P" << std::endl;

                break;
            
            }
            system("pause");




            if (lettre == CGrille::resultat::F)
            {
               std:: cout << "on est dans la boucle lettre = F  x = " << x << "y =" << y << std::endl;
                Case = grille.getCase(x, y);
                switch (Case) //pour du debug
                {
                case CGrille::Case::VIDE:
                    std::cout << "Getcase : vide " << std::endl;
                    break;
                case CGrille::Case::BATEAU:
                    std::cout << "Getcase : bateau " << std::endl;

                    break;
                case CGrille::Case::TOUCHEJ:
                    std::cout << "Getcase : touchej " << std::endl;

                    break;
                case CGrille::Case::TOUCHEE:
                    std::cout << "Getcase : touchee " << std::endl;

                    break;
                case CGrille::Case::EAUJ:
                    std::cout << "Getcase : eauj " << std::endl;

                    break;
                case CGrille::Case::EAUE:
                    std::cout << "Getcase : eaue " << std::endl;

                    break;
                case CGrille::Case::ERREUR:
                    std::cout << "Getcase : erreur " << std::endl;

                    break;
                } //fin debug
                 system("pause");
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
            std::cout << erreurs << std::endl; erreurs++; //3
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
            std::cout << erreurs << std::endl; erreurs++; //4
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
            std::cout << erreurs << std::endl; erreurs++; //5
            if (lettre == CGrille::resultat::P)
            {
                //partie remporté 
                std::cout << " Victoire";
                return 0;
            }
            std::cout << erreurs << std::endl; erreurs++; //6


            //fin analyse trame -------------------------------------------------------
            discussion = connection.reception();
            std::cout << discussion << std::endl;
            std::cout << erreurs << std::endl; erreurs++; //7
            std::cout << "Ou voulez-vous envoyer un missile ?" << std::endl;
            std::cin >> discussion;
            xTemp = std::stoi(std::to_string(discussion.at(0)));
            std::cout << erreurs << std::endl; erreurs++; //8
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
            std::cout << discussion << std::endl;
            std::cout << "juste ici" << std::endl; erreurs++; //9
            lettreAenvouyer = CGrille::resultat::T; //debug a enlever
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
            std::cout << erreurs << std::endl; erreurs++; //10
            std::cout << discussion << std::endl;
            connection.envoi(discussion);
            std::cout << erreurs << std::endl; erreurs++; //11
            grille.afficherGrille();
            std::cout << erreurs << std::endl; erreurs++; //12



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
            std::cout << erreurs << std::endl; erreurs++; //0
            std::string discussion;
            discussion = connection.reception();
            std::cout << erreurs << std::endl; erreurs++;//1
            std::cout << discussion << std::endl;

            std::cout << "Ou voulez-vous envoyer un missile ?" << std::endl;
            std::cin >> discussion;
            std::cout << std::endl;
            std::cout << erreurs << std::endl; erreurs++;//2
            xTemp = std::stoi(std::to_string(discussion.at(0)));
            std::cout << erreurs << std::endl; erreurs++;//3
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
            std::cout << erreurs << std::endl; erreurs++;//4
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
            std::cout << erreurs << std::endl; erreurs++;//5
            std::string messageEnnemi = connection.reception();
            std::cout << messageEnnemi << std::endl;
            std::cout << erreurs << std::endl; erreurs++;//6
            //ajouter une fonction de mise a jour de la map (fonction de serialisation)
       //analyse de la trame recu ---------------------------------------------------          
            int x;
            int y;
            CGrille::resultat lettre;
            //CGrille::resultat lettreAenvouyer; inschallah
            CGrille::Case Case;
            grille.serialisation(x, y, messageEnnemi, lettre);
            std::cout << erreurs << std::endl; erreurs++;//7
            //mettre a jour la map de l'ennemi avec les coordonné CoordonneTemp + lettre 

         
            switch (lettre)
            {
            case CGrille::resultat::F:
                std::cout << "lettre = F" << std::endl;

                break;
            case CGrille::resultat::T:
                std::cout << "lettre = T" << std::endl;

                break;
            case CGrille::resultat::L:
                std::cout << "lettre = L" << std::endl;

                break;
            case CGrille::resultat::G:
                std::cout << "lettre = G" << std::endl;

                break;
            case CGrille::resultat::P:
                std::cout << "lettre = P" << std::endl;

                break;

            }
            system("pause");
            
                if (lettre == CGrille::resultat::F)
                {
                    Case = grille.getCase(x, y); 
                    
                switch (Case) //pour du debug
                {
                case CGrille::Case::VIDE:
                    std::cout << "Getcase : vide " << std::endl;
                    break;
                case CGrille::Case::BATEAU:
                    std::cout << "Getcase : bateau " << std::endl;

                    break;
                case CGrille::Case::TOUCHEJ:
                    std::cout << "Getcase : touchej " << std::endl;
                   

                    break;
                case CGrille::Case::TOUCHEE:
                    std::cout << "Getcase : touchee " << std::endl;

                    break;
                case CGrille::Case::EAUJ:
                    std::cout << "Getcase : eauj " << std::endl;

                    break;
                case CGrille::Case::EAUE:
                    std::cout << "Getcase : eaue " << std::endl;

                    break;
                case CGrille::Case::ERREUR:
                    std::cout << "Getcase : erreur " << std::endl;

                    break;
                } //fin debug
                 system("pause");
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

                std::cout << erreurs << std::endl; erreurs++;//8
                grille.afficherGrille();



            } while (true);

        }




        return(0); //a verif
}//main 





