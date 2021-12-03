#include "CFonctionServer.h"

///\fn CFonctionServer()
///\brief constructeur de la class  
/// Ce constructeur ne prend aucun parametre et n'initialise aucune variable 
CFonctionServer::CFonctionServer()
{
   // nbconnec = 0;
   //const ushort PORT_NUM = 12345;
   //const ushort DIMMAX = 150;

}

///\fn initWinsock()
///\brief initialise winsock 
///\return void
void CFonctionServer::initWinsock()
{
	WSAStartup(nVersion, &donneeWS);
    std::cout << "Init de winsock " << std::endl; //pour le debug 
}

///\fn creaSockEcoute()
///\brief crée un socket d'ecoute 
/// socket qui prend en parametre AF_INET et SOCK_STREAM 
///\return void
void CFonctionServer::creaSockEcoute()
{
    if ((ids_ecoute = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        std::cout << "Echec creation Socket ! " << std::endl;
        exit(1);
    }
    std::cout << "creation socket ecoute " << std::endl; //pour le debug 
}

///\fn binding()
///\brief attache le socket d'écoute avec l'adresse et le port du serveur 
///\return void
void CFonctionServer::binding()
{
    // RAZ de la structure contenant @ inet serveur
    memset(&adr_serveur, 0, sizeof(adr_serveur));
    // Mise en forme de l'@ du socket d'écoute et attachement du socket
    adr_serveur.sin_family = AF_INET;            // Domain d'@ 
    adr_serveur.sin_port = htons(PORT_NUM);    // N° du port 
    adr_serveur.sin_addr.s_addr = htonl(INADDR_ANY);  // n'importe quel 
                                     // interface réseau

    if (bind(ids_ecoute, (struct sockaddr*)&adr_serveur,
        sizeof(adr_serveur)) == SOCKET_ERROR)
    {
        std::cout << "Echec Attachement Socket ! " << std::endl;
        exit(1);
    }
    std::cout << "bind socket ecoute sur le port : " << std::to_string(PORT_NUM) << std::endl; //pour le debug 
}

///\fn listening()
///\brief passe le socket en mode ecoute 
///\return void
void CFonctionServer::listening()
{
    if (listen(ids_ecoute, 2) == SOCKET_ERROR)
    {
        std::cout << "Echec Lecture ! " << std::endl;
        exit(1);
    }
    std::cout << "Serveur en ecoute " << std::endl; //pour le debug 
}

///\fn accepting()
///\brief retourne l'adresse d'un client qui se connecte
/// Quand le socket d'écoute trouve une connection il le renvoie sur un socket de communication et cette fonction retourne l'adresse de ce socket de communication  
///\return uint adresse des client connecté
uint CFonctionServer::accepting()
{

     // Acceptation d'une connexion cliente, création d'un nouveau socket qui 
        // sera utilisé pour l'émission et la réception des caractères 
        // @ inet du clietnt est récupérée
    addr_len = sizeof(adr_client);

    ids_connect = accept(ids_ecoute, (struct sockaddr*)&adr_client, &addr_len);
    return ids_connect; 
    std::cout << "Client accepté " << std::endl; //pour le debug 
}

///\fn communication(uint ids_connect, uint ids_connect1)
///\brief fait transiter des trame entre deux socket de communication 
/// Permet la communication entre deux clients, on reçoi une trame et on la renvoie 
///\param[in] uint ids_connect, uint ids_connect1 qui sont les deux adresse des socket de communication  
///\return void
void CFonctionServer::communication(uint ids_connect, uint ids_connect1)
{
    const ushort DIMMAX = 150; // Taille max des tableaux



    char trame_lect[DIMMAX + 1];
    char trame_lect1[DIMMAX + 1];
    std::string recive;
    std::string recive1;

    std::string waiting = "Serveur: Vous etes connecte";



   // send(ids_connect, waiting.c_str(), waiting.size() + 1, 0);
    send(ids_connect1, waiting.c_str(), waiting.size() + 1, 0);
    uint noctets;

    std::string placervosbateaux = "Serveur: Placez vos beateux";
    send(ids_connect, placervosbateaux.c_str(), placervosbateaux.size() + 1, 0);
    send(ids_connect1, placervosbateaux.c_str(), placervosbateaux.size() + 1, 0);

    std::string Avous = "Serveur: votre tour de jouer";

    //echange client serveur peroquet sauf pour BYE
    do
    {

        send(ids_connect, Avous.c_str(), Avous.size() + 1, 0);
        noctets = recv(ids_connect, trame_lect, DIMMAX, 0);
        trame_lect[noctets] = '\0';
        recive = trame_lect; 
        send(ids_connect1, recive.c_str(), recive.size() + 1, 0);

        Sleep(30); //a verif ?

        send(ids_connect1, Avous.c_str(), Avous.size() + 1, 0);
        noctets = recv(ids_connect1, trame_lect, DIMMAX, 0);
        trame_lect[noctets] = '\0';
        recive = trame_lect;
        send(ids_connect, recive.c_str(), recive.size() + 1, 0);


    } while (recive != "BYE");


    // fermeture des sockets ouverts
    closesocket(ids_connect);
    closesocket(ids_connect1);

};

///\fn sending(uint ids_connect, std::string message)
///\brief envoi une trame vers le client connecté au socket de communication
/// Permet la communication entre deux clients, on reçoi une trame et on la renvoie 
///\param[in]uint ids_connect, std::string message qui sont l'adresse du socket de communication et une string contenant le message
///\return void
void CFonctionServer::sending(uint ids_connect, std::string message)
{
    send(ids_connect, message.c_str(), message.size() + 1, 0);
};

///\fn reciving(uint ids_connect, uint ids_connect1, std::string& message)
///\brief ? pas fini mais sert a rien visiblement
///\param[in] uint ids_connect, uint ids_connect1
/// ///\param[out] std::string& message
///\return void
void CFonctionServer::reciving(uint ids_connect, uint ids_connect1, std::string& message)
{
    const ushort DIMMAX = 150; // Taille max des tableaux


    char trame_lect[DIMMAX + 1];
    std::string recive;

    uint noctets = recv(ids_connect, trame_lect, DIMMAX, 0);
    trame_lect[noctets] = '\0';
    recive = trame_lect;
    send(ids_connect1, recive.c_str(), recive.size() + 1, 0);
};

///\fn FermeturWinSock()
///\brief ferme proprement winsock
///\return void
void CFonctionServer::FermeturWinSock()
{
    WSACleanup();
    std::cout << "fermeture de winsock " << std::endl; //pour le debug 
}

///\fn fermetureSockEcoute()
///\brief ferme proprement le socket d'ecoute
/// Si on ne le ferme pas correctement le serveur crash
///\return void
void CFonctionServer::fermetureSockEcoute()
{
    closesocket(ids_ecoute);
}
