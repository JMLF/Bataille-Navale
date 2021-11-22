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

    uint ids_ecoute;        // id du socket d'�coute du serveur
    uint ids_connect;       // id du socket de connection
    uint ids_connect1;
    uint nb_car_emis;       // nb car �mis par send


    int  addr_len;          // taille de l'@ internet 

    uint n = 0, noctets;

    int nbconnec; //on compte le nombre de connection 

public: 

    //constructeur de la classe
    CFonctionServer();

    // initialisation du winsock (etape 1)
    void initWinsock(); 

    // Cr�ation du socket d'�coute (etape 2)
    void creaSockEcoute(); 

    //Bind du socket (etape 3)
    void binding();

    //�coute du socket (etape 4)
    void listening();

    // Acceptation d'une connexion cliente, cr�ation d'un nouveau socket qui 
    // sera utilis� pour l'�mission et la r�ception des caract�res (etape 5)
    void accepting();

    //communication entre deux clients
    void communication(uint ids_connect, uint ids_connect1);

    //envoi d'une trame vers un client
    void sending(uint ids_connect, std::string message);

    //reception d'une trame et renvoi (perroquet)
    void reciving(uint ids_connect, uint ids_connect1, std::string& message); 

    // fermeture du socket d'�coute
    void fermetureSockEcoute();

    // Fermeture de winsock
    void FermeturWinSock();

};

