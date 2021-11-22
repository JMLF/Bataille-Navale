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
    //connection.envoi("Bonjour !");
    message = connection.reception(); //on reçoit la confirmation de connection entre deux clients
    std::cout << message << std::endl;
    do
    {
    
        message = connection.reception();
        std::cout << message << std::endl;
        std::cin >> message;
        connection.envoi(message);

        
    
    } while (message != "BYE");

   
   

   
}