#include "CConnectionServeur.h"

CConnectionServeur::CConnectionServeur(std::string IP_SERVEUR, std::string port)
{
   
    try
    {
       this-> IP_SERVEUR = IP_SERVEUR;
       this -> port = port;
       this ->   NUM_PORT = stoi(port);
    }
    catch (...)
    {
        throw("Mauvais format du port");        
    }

    if (NUM_PORT <= 0)
    {
        throw("Port inferieur egal a 0");
    }

}

void CConnectionServeur::initConnec()
{
    // initialisation du winsock
    WSAStartup(nVersion, &donneeWS);

    // Création du socket client
    if ((ids_client = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        throw("Echec creation Socket");
        exit(1);
    }

    // Mise en place de l'@ inet et demande de connexion au serveur 
    adr_serveur.sin_family = AF_INET;                  // Domaine d'@ 
    adr_serveur.sin_port = htons(NUM_PORT);          // N° du port 
    inet_pton(AF_INET, IP_SERVEUR.c_str(), &adr_serveur.sin_addr.s_addr); //IP du serv

}

void CConnectionServeur::connection()
{
    if (connect(ids_client, (struct sockaddr*)&adr_serveur, sizeof(adr_serveur)) < 0)
    {
        throw("Echec connexion");
        exit(1);
    }
}

std::string CConnectionServeur::reception()
{
    const ushort DIMMAX = 150; // Taille max des tableaux

    char trame_lect[DIMMAX + 1];

    // Reçoit la reponse du serveur
    noctets = recv(ids_client, trame_lect, DIMMAX, 0);
    trame_lect[noctets] = '\0';
    return trame_lect; 

}

void CConnectionServeur::envoi(std::string requete)
{
    send(ids_client, requete.c_str(), DIMMAX, 0);
}

void CConnectionServeur::fermetureSocket()
{
    // fermeture le socket ouvert
    closesocket(ids_client); // à la place de close() sous Linux

    // Fermeture de winsock
    WSACleanup();
}
