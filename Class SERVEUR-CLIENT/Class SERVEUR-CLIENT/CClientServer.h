
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



class CClientServer
{

private:

	const ushort PORT_NUM = 12345; //serveur
	const ushort DIMMAX = 150; // Taille max des tableaux

	WORD nVersion = MAKEWORD(2, 2);
	WSADATA donneeWS;

	struct sockaddr_in   adr_serveur;       // @ internet du serveur
	struct sockaddr_in   adr_client;        // @ internet du client

	uint ids_ecoute;        // id du socket d'écoute du serveur
	uint ids_connect;       // id du socket de connection
	uint ids_connect1;
	uint ids_client; //client 
	uint nb_car_emis;       // nb car émis par send

	std::string IP_SERVEUR; //client 
	std::string port; //client 
	std::string requete; //client
	ushort NUM_PORT; //client

	int  addr_len;          // taille de l'@ internet 

	uint n = 0, noctets;


public:

	//initialise le serveur et le met en mode ecoute (server side)
	void initServer();

	//retourne l'ids connect d'un client (server side)
	uint accepting(); 

	//communication entre deux ids connect a mettre dans un thread (server side)
	void communication(uint ids_connect, uint ids_connect1);

	//fermeture "propre du serveur" (server side)
	void fermetureServer();

	//initialise le client (client side)
	void initClient(std::string IP_SERVEUR, std::string port);

	//attend de recevoir une trame (client side + bloquant)
	std::string reception();

	//envoi une trame vers le serveur (client side)
	void envoi(std::string requete);

	//pour une fermeture propre du client (client side)
	void fermetureClient();

};

