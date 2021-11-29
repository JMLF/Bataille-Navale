#include "CConnectionServeur.h"
#include "CGrille.h"
#include <iostream>

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

    enum class trame{AVOUS=0,FIRE,TOUCH,MISS,WIN=4}; //pour l'analyse des trame reçu

    if (message == "Serveur: votre tour de jouer") //on previent le joueur 2 que l'on a fini de placer les bateaux 
    {

        connection.envoi("joueur: J'ai ini de placer mes bateaux"); 
        std::string etats;
        int etat(0);
        do
        {
            //std::cout << "on entre dans la boucle 1" << std::endl; pour debug
            std::string discussion;
            discussion = connection.reception();// petit probleme sur le premier echange on reçoit a votre tour alors que non
            std::cout << discussion << std::endl;
            discussion = connection.reception(); 
            std::cout << discussion << std::endl; 
            //ajouter une fonction de mise a jour de la map 
            std::cout << "Ou voulez-vous envoyer un missile ?" << std::endl;
            std::cin >> discussion;
            std::cout << std::endl;
            connection.envoi(discussion);
            //etats = discussion;
           // discussion = connection.reception();
           // std::cout << discussion << std::endl;
          
            /*
            if (discussion.find("Serveur: votre tour de jouer") != )
            {

            }
            */

            /*
            switch (etat)
            {
            case 0:
                //trame = a vous de jouer, on ne fait rien
                break;
            case 1:
                //trame = FIRE+coordonné
                //on analyse pour voir si on été touché 
                //si on a été touché on revoi touch sinon miss si tout nos bateau sont mort on renvoi WIN a l'adversaire
                // if coordonné = coordonné d'un bateau le passer 
               //grille.getCase();
               //grille.setCase();
                break;
            case 2:
                //trame = touch+coordonné
                //on a touché ladrversaire au coordonné reçu
                break;
            case 3:
                //trame = miss+coordonné
                //on a loupé l'adversaire
                break;
            case 4:
                //trame = WIN 
                //on a gagné
                break;

            }
            */

        } while (true);
    }
    if (message == "joueur: J'ai ini de placer mes bateaux") //si on reçoit le message que le joueur 2 a fini on peux envoyer une trame puisque c'est notre tour coté serveur
    {
        std::string etats;
        int etat(0);
        do
        {
          //  std::cout << "on entre dans la boucle 2" << std::endl; pour debug
            std::string discussion;
            discussion = connection.reception();
            std::cout << discussion << std::endl;
            std::cout << "Ou voulez-vous envoyer un missile ?" << std::endl;
            std::cin >> discussion;
            std::cout << std::endl;
            connection.envoi(discussion);
            discussion = connection.reception();
            std::cout << discussion << std::endl;
            etats = discussion;


            /*
            switch (etat)
            {
            case 0:
            //trame = a vous de jouer, on ne fait rien
                break;
            case 1:
                //trame = FIRE+coordonné
                //on analyse pour voir si on été touché 
                //si on a été touché on revoi touch sinon miss si tout nos bateau sont mort on renvoi WIN a l'adversaire
                break;
            case 2:
                //trame = touch+coordonné
                //on a touché ladrversaire au coordonné reçu
                break;
            case 3:
                //trame = miss+coordonné
                //on a loupé l'adversaire
                break;
            case 4:
                //trame = WIN 
                //on a gagné
                break;

            }
            */

        } while (true);

    }

    
  

    return(0);
}


