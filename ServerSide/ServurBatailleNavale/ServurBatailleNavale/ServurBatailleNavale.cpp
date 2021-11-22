
/*
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


void sending(uint ids_connect, std::string message)
{
    send(ids_connect, message.c_str(), message.size() + 1, 0);
};

void reciving(uint ids_connect, uint ids_connect1,std::string& message)
{
    char trame_lect[DIMMAX + 1];
    std::string recive;

    uint noctets = recv(ids_connect, trame_lect, DIMMAX, 0);
    trame_lect[noctets] = '\0';
    recive = trame_lect;
    send(ids_connect1, recive.c_str(), recive.size() + 1, 0);
};

void communication(uint ids_connect, uint ids_connect1) {

   
    char trame_lect[DIMMAX + 1];
    char trame_lect1[DIMMAX + 1];
    std::string recive;
    std::string recive1;

    std::string waiting = "Serveur: Vous etes connecte "  ;

    std::thread th1(sending, ids_connect, waiting);
    th1.detach();
    std::thread th2(sending, ids_connect1, waiting);
    th2.detach();

    //send(ids_connect, waiting.c_str(), waiting.size() + 1, 0);
    //send(ids_connect1, waiting.c_str(), waiting.size() + 1, 0);
    uint noctets;
    
    std::thread threcv1(reciving, ids_connect,ids_connect1, std::ref(recive));
    std::thread threcv2(reciving, ids_connect1, ids_connect, std::ref(recive1));

    //echange client serveur peroquet sauf pour BYE
    do
    {
       // std::thread threcv1(reciving, ids_connect, ids_connect1, std::ref(recive));
       // std::thread threcv2(reciving, ids_connect1, ids_connect, std::ref(recive1));
        
       // threcv1.detach();
       // threcv2.detach();
      
        
        noctets = recv(ids_connect, trame_lect, DIMMAX, 0);
        trame_lect[noctets] = '\0';
        recive = trame_lect;
        send(ids_connect1, recive.c_str(), recive.size() + 1, 0);
        
        noctets = recv(ids_connect1, trame_lect, DIMMAX, 0);
        trame_lect[noctets] = '\0';
        recive = trame_lect;
        send(ids_connect, recive.c_str(), recive.size() + 1, 0);
        

    } while (recive != "BYE");


    // fermeture des sockets ouverts
    closesocket(ids_connect);
    closesocket(ids_connect1);

};



int main()
{

    WORD nVersion = MAKEWORD(2, 2);
    WSADATA donneeWS;

    struct sockaddr_in   adr_serveur;       // @ internet du serveur
    struct sockaddr_in   adr_client;        // @ internet du client

    uint ids_ecoute;        // id du socket d'écoute du serveur
    uint ids_connect;       // id du socket de connection
    uint ids_connect1;
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

    int nbconnec(0); //on compte le nombre de connection 

    while (true)
    {

        // Mise à disposition du socket (service) (2: deux connection au max la troisiemme est refusé immediatement)
        if (listen(ids_ecoute, 2) == SOCKET_ERROR)
        {
            std::cout << "Echec Lecture ! " << std::endl;
            exit(1);
        }

        // Acceptation d'une connexion cliente, création d'un nouveau socket qui 
        // sera utilisé pour l'émission et la réception des caractères 
        // @ inet du clietnt est récupérée
        addr_len = sizeof(adr_client);

        ids_connect = accept(ids_ecoute, (struct sockaddr*)&adr_client, &addr_len);
        nbconnec++;

        if (nbconnec ==1)
        {
            ids_connect1 = ids_connect;
        }

        if (nbconnec ==2)
        {
        std::thread th1(communication, ids_connect, ids_connect1);
        th1.detach();
        nbconnec = 0;
        }

        
        
    }

    // fermeture des sockets ouverts
    closesocket(ids_ecoute);


    // Fermeture de winsock
    WSACleanup();

    std::cout << "--- FIN du prog" << std::endl;
    std::cin.get();
    return 0;


}

*/