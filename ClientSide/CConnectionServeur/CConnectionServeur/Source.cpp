#include <iostream>
#include "CConnectionServeur.h"

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
    connection.connection();

    std::string message;
    connection.envoi("Bonjour !");
    do
    {
    
        message = connection.reception();
        connection.envoi(message);
        std::cout << message << std::endl;
    
    } while (message != "BYE");

   
   

   
}