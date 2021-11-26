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
    grille.placerBateau();
    message = connection.reception(); //reception du message qui dit qu'on peux parler ou que l'autre joueur place ses bateau
    std::cout << message << std::endl;


    if (message == "Serveur: votre tour de jouer") //on previent le joueur 2 que l'on a fini de placer les bateaux 
    {
        connection.envoi("joueur: J'ai ini de placer mes bateaux");    
    }
    if (message == "joueur: J'ai ini de placer mes bateaux") //si on reçoit le message que le joueur 2 a fini on peux envoyer une trame puisque c'est notre tour coté serveur
    {
        do
        {
            
            std::string discussion;
            discussion = connection.reception();
            std::cout << discussion << std::endl;
            std::cin >> discussion;
            std::cout << std::endl;
            connection.envoi(discussion);
            discussion = connection.reception();
            std::cout << discussion << std::endl;

        } while (true);

    }

    do
    {

        std::string discussion;
        discussion = connection.reception();
        std::cout << discussion << std::endl;
        std::cin >> discussion;
        std::cout << std::endl;
        connection.envoi(discussion);
        discussion = connection.reception();
        std::cout << discussion << std::endl;

    } while (true);
  

    return(0);
}


