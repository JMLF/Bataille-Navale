#pragma once

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



class CFonctionServer
{

private: 

	const ushort PORT_NUM = 12345;;
	const ushort DIMMAX = 150; // Taille max des tableaux

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

   // int nbconnec; //on compte le nombre de connection 



public: 

    //constructeur de la classe
    CFonctionServer();

    // initialisation du winsock (etape 1)
    void initWinsock(); 

    // Création du socket d'écoute (etape 2)
    void creaSockEcoute(); 

    //Bind du socket (etape 3)
    void binding();

    //écoute du socket (etape 4)
    void listening();

    // Acceptation d'une connexion cliente, création d'un nouveau socket qui 
    // sera utilisé pour l'émission et la réception des caractères (etape 5)
    uint accepting();

    void communication(uint ids_connect, uint ids_connect1);

    void sending(uint ids_connect, std::string message);

    void reciving(uint ids_connect, uint ids_connect1, std::string& message);

    // fermeture du socket d'écoute
    void fermetureSockEcoute();

    // Fermeture de winsock
    void FermeturWinSock();

};

