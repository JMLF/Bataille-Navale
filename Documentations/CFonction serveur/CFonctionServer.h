#pragma once

///\mainpage
/// Classe CFonctionServeur en charge du controle du serveur 

#define _CRT_SECURE_NO_WARNINGS

///\file CFonctionServer.h
///\version 1
///\brief Classe de deployement du serveur 


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

	///\def PORT_NUM 
	///\brief Numero de port
	/// Constante unsigned short qui correspond au numero de port sur lequel on se connecte
	const ushort PORT_NUM = 12345;;
    ///\def DIMMAX 
    ///\brief Taille max de trame re�u
    /// Constante unsigned short qui correspond a la taille max des tableux ou trame re�u
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

   // int nbconnec; //on compte le nombre de connection 



public: 

    ///\fn CFonctionServer()
    ///\brief constructeur de la class  
    /// Ce constructeur ne prend aucun parametre et n'initialise aucune variable 
    CFonctionServer();

    ///\fn initWinsock()
    ///\brief initialise winsock 
    ///\return void
    void initWinsock(); 

    // Cr�ation du socket d'�coute (etape 2)
    ///\fn creaSockEcoute()
    ///\brief cr�e un socket d'ecoute 
    /// socket qui prend en parametre AF_INET et SOCK_STREAM 
    ///\return void
    void creaSockEcoute(); 

    //Bind du socket (etape 3)
    ///\fn binding()
    ///\brief attache le socket d'�coute avec l'adresse et le port du serveur 
    ///\return void
    void binding();

    //�coute du socket (etape 4)
    ///\fn listening()
    ///\brief passe le socket en mode ecoute 
    ///\return void
    void listening();

    // Acceptation d'une connexion cliente, cr�ation d'un nouveau socket qui 
    // sera utilis� pour l'�mission et la r�ception des caract�res (etape 5)
    ///\fn accepting()
    ///\brief retourne l'adresse d'un client qui se connecte
    /// Quand le socket d'�coute trouve une connection il le renvoie sur un socket de communication et cette fonction retourne l'adresse de ce socket de communication  
    ///\return uint adresse des client connect�
    uint accepting();

    ///\fn communication(uint ids_connect, uint ids_connect1)
    ///\brief fait transiter des trame entre deux socket de communication 
    /// Permet la communication entre deux clients, on re�oi une trame et on la renvoie 
    ///\param[in] uint ids_connect, uint ids_connect1 qui sont les deux adresse des socket de communication  
    ///\return void
    void communication(uint ids_connect, uint ids_connect1);

    ///\fn sending(uint ids_connect, std::string message)
    ///\brief envoi une trame vers le client connect� au socket de communication
    /// Permet la communication entre deux clients, on re�oi une trame et on la renvoie 
    ///\param[in]uint ids_connect, std::string message qui sont l'adresse du socket de communication et une string contenant le message
    ///\return void
    void sending(uint ids_connect, std::string message);

    ///\fn reciving(uint ids_connect, uint ids_connect1, std::string& message)
    ///\brief ? pas fini mais sert a rien visiblement
    ///\param[in] uint ids_connect, uint ids_connect1
    /// ///\param[out] std::string& message
    ///\return void
    void reciving(uint ids_connect, uint ids_connect1, std::string& message);

    // fermeture du socket d'�coute
    ///\fn FermeturWinSock()
    ///\brief ferme proprement winsock
    ///\return void
    void fermetureSockEcoute();

    // Fermeture de winsock
    ///\fn fermetureSockEcoute()
    ///\brief ferme proprement le socket d'ecoute
    /// Si on ne le ferme pas correctement le serveur crash
    ///\return void
    void FermeturWinSock();

};

