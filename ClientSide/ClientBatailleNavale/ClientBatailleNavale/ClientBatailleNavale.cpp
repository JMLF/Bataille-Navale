#include "CConnectionServeur.h"
#include "CGrille.h"
#include <iostream>

nt main(int argc, char* argv[])
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
    
    CGrille grille;

    //grille.placerBateau();

    /*
    do
    {
        cin coup
        connection.envoi(coup)
        connection.reciv
        maj grille
        envoi maj grille 

    } while (win or loose);
    */


}


