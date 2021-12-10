
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

   
   

    if (message == "Serveur: communication") //on previent le joueur 2 que l'on a fini de placer les bateaux 
    {

        connection.envoi("joueur: J'ai fini de placer mes bateaux");
        std::string etats; //a verif mais je pense que ça sert plus 
        int etat(0); //ça non plus 
        int xTemp = 0;
        int yTemp = 0;
        do
        {
              
            std::string discussion;
            std::string messageEnnemi;
              
            messageEnnemi = connection.reception();
            std::cout << messageEnnemi << std::endl;
             
            //pour optimiser le code la partie ci dessous dois etre sortie de la boucle do while
            // declaration --------------------------------------------------------------
            int x;
            int y;
            CGrille::resultat lettre;
            CGrille::resultat lettreAenvouyer = CGrille::resultat::F; //valeur par defaut
            CGrille::Case Case;
            // ---------------------------------------------------------------------------


            //analyse de la trame recu --------------------------------------------------- debut  
            
            grille.serialisation(x, y, messageEnnemi, lettre); //en faite c'est plus de la déserialisation 

            //debug ---------------------------------------------------------------------- a supprimer
            std::cout << "serialisation,  x et y " << x << " " << y << std::endl;
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
            // fin debug ---------------------------------------------------------------------- jusque la
           
            //pour optimiser on pourrais remplacer par un switch avec un default qui ne fait rien 
            if (lettre == CGrille::resultat::T)
            {
                grille.XGrilleEnnemie(xTemp, yTemp);
                
            }  
            if (lettre == CGrille::resultat::L)
            {
                grille.TildGrilleEnnemie(xTemp, yTemp);
          
            } 
            if (lettre == CGrille::resultat::P)
            {
                //partie remporté 
                std::cout << " Victoire";
                return 0;
            }


            Case = grille.getCase(x, y);
            // a remplacer par un switch également 
            if (Case == CGrille::Case::BATEAU)
            {
                grille.XGrilleJoueur(x, y);
                lettreAenvouyer = CGrille::resultat::T;
                grille.setnbDeCaseBateau();
                bool perdu=grille.partiePerdue();
                if (perdu == true) {
                lettreAenvouyer = CGrille::resultat::P;
                }
            }
            if (Case == CGrille::Case::TOUCHEJ)
            {
                grille.XGrilleJoueur(x, y);
                lettreAenvouyer = CGrille::resultat::T;
            }
            if (Case == CGrille::Case::VIDE)
            {
                grille.TildGrilleJoueur(x, y);
                lettreAenvouyer = CGrille::resultat::L;
            }
            if (Case == CGrille::Case::EAUJ)
            {
                grille.TildGrilleJoueur(x, y);
                lettreAenvouyer = CGrille::resultat::L;
            }
               
            //fin analyse trame -------------------------------------------------------
            
            discussion = connection.reception(); //on attend que le serveur envoi une trame qui nous indique que c'est notre tour de parler
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
            
            
            switch (lettreAenvouyer) //suivant le résultat du tir ennemi sur notre grille on ajoute le résultat devant les coordonnées que l'on renvoi
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
                discussion = "P:" + discussion;
                break;

            }
              
            std::cout << discussion << std::endl;
            connection.envoi(discussion); 
              
        } while (true);
    }

    if (message == "joueur: J'ai fini de placer mes bateaux") //si on reçoit le message que le joueur 2 a fini on peux envoyer une trame puisque c'est notre tour coté serveur
    {
      
        int etat(0); //a verifier pas sur que ce soit utile 
        int xTemp = 0;
        int yTemp = 0;
        CGrille::resultat lettreAenvouyer;
        lettreAenvouyer = CGrille::resultat::F; //valeur par défaut
        do
        {
              
            std::string discussion; //on pourrait le sortir de la boucle pour opti mais bien penser a verif que ça marche encore
            discussion = connection.reception(); //on attend la trame du serveur qui dit que c'est a notre tour de jouer 
             
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
          
            switch (lettreAenvouyer) //suivant le résultat du tir ennemi sur notre grille on ajoute le résultat devant les coordonnées que l'on renvoi
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
                discussion = "P:" + discussion;
                break;

            }

            connection.envoi(discussion);
             
            std::string messageEnnemi = connection.reception();
            std::cout << messageEnnemi << std::endl;
             
            
            //analyse de la trame recu --------------------------------------------------- debut         
            int x;
            int y;
            CGrille::resultat lettre;
            CGrille::Case Case;
            grille.serialisation(x, y, messageEnnemi, lettre);
           
            //debug ---------------------------------------------------------------------- a supprimer
            std::cout << "serialisation,  x et y " << x << " " << y << std::endl;
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
            // fin debug ---------------------------------------------------------------------- jusque la   

                if (lettre == CGrille::resultat::T)
                {
                    grille.XGrilleEnnemie(xTemp, yTemp);
                    
                }

                if (lettre == CGrille::resultat::L)
                {
                    grille.TildGrilleEnnemie(xTemp, yTemp);
                    
                }

                if (lettre == CGrille::resultat::P)
                {
                    //partie remporté 
                    std::cout << " Victoire";
                    return 0;
                }

                Case = grille.getCase(x, y);
                if (Case == CGrille::Case::BATEAU)
                {
                    grille.XGrilleJoueur(x, y);
                    lettreAenvouyer = CGrille::resultat::T;
                    grille.setnbDeCaseBateau();
                    bool perdu = grille.partiePerdue();
                    if (perdu == true) {
                        lettreAenvouyer = CGrille::resultat::P;
                    }
                }
                if (Case == CGrille::Case::TOUCHEJ)
                {
                    grille.XGrilleJoueur(x, y);
                    lettreAenvouyer = CGrille::resultat::T;
                }
                if (Case == CGrille::Case::VIDE)
                {
                    grille.TildGrilleJoueur(x, y);
                    lettreAenvouyer = CGrille::resultat::L;
                }
                if (Case == CGrille::Case::EAUJ)
                {
                    grille.TildGrilleJoueur(x, y);
                    lettreAenvouyer = CGrille::resultat::L;
                }

                //fin analyse trame -------------------------------------------------------

            } while (true);
        }

        return(0); //si on ne reçoit aucun message du serveur
}//main 





