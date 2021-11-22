#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <time.h>
#include <iostream>
#include <string>
#include <random>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

const ushort PORT_NUM = 12345;
const ushort DIMMAX = 150; // Taille max des tableaux

void communication(uint ids_connect) {

    char trame_lect[DIMMAX + 1];
    std::string recive;

    //echange client serveur peroquet sauf pour BYE
    do
    {
        uint noctets = recv(ids_connect, trame_lect, DIMMAX, 0);
        trame_lect[noctets] = '\0';
        recive = trame_lect;

       
            send(ids_connect, recive.c_str(), recive.size() + 1, 0);
        


    } while (recive != "BYE");


    // fermeture des sockets ouverts
    closesocket(ids_connect);

};



int main()
{

    WORD nVersion = MAKEWORD(2, 2);
    WSADATA donneeWS;

    struct sockaddr_in   adr_serveur;       // @ internet du serveur
    struct sockaddr_in   adr_client;        // @ internet du client

    uint ids_ecoute;        // id du socket d'écoute du serveur
    uint ids_connect;       // id du socket de connection
    uint nb_car_emis;       // nb car émis par send

    int  addr_len;          // taille de l'@ internet 


    uint n = 0, noctets;

    // initialisation du winsock
    WSAStartup(nVersion, &donneeWS);

    std::cout << "--- DEBUT du prog " << std::endl;

    // Création du socket d'écoute
    if ((ids_ecoute = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        std::cout << "Echec creation Socket ! " << std::endl;
        exit(1);
    }


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
    while (true)
    {


        // Mise à disposition du socket (service) (1: une connection au max)
        if (listen(ids_ecoute, 1) == SOCKET_ERROR)
        {
            std::cout << "Echec Lecture ! " << std::endl;
            exit(1);
        }

        // Acceptation d'une connexion cliente, création d'un nouveau socket qui 
        // sera utilisé pour l'émission et la réception des caractères 
        // @ inet du clietnt est récupérée
        addr_len = sizeof(adr_client);

        ids_connect = accept(ids_ecoute, (struct sockaddr*)&adr_client, &addr_len);
        std::thread th1(communication, ids_connect);
        th1.detach();
    }

    // fermeture des sockets ouverts
    closesocket(ids_ecoute);


    // Fermeture de winsock
    WSACleanup();

    std::cout << "--- FIN du prog" << std::endl;
    std::cin.get();
    return 0;






    



}

