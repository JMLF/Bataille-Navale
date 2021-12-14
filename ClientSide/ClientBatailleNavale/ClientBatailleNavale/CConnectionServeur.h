#pragma once

#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex> 


#pragma comment(lib, "ws2_32.lib") //pour ajouter la lib manquante 

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;



class CConnectionServeur
{

private:

	const ushort DIMMAX = 150; // Taille max des tableaux

	std::string IP_SERVEUR;
	std::string port;
	std::string requete;
	ushort NUM_PORT;

	uint n = 0, noctets;

	// Particularités Windows
	WORD nVersion = MAKEWORD(2, 2);
	WSADATA donneeWS;

	struct sockaddr_in  adr_serveur; // @ internet du serveur

	uint  ids_client;   // id du socket client                  



public:

	//constructeur de la class
	CConnectionServeur(std::string IP_SERVEUR, std::string port);

	//initialise tout ce qu'il faut
	void initConnec();

	//se connecte au serveur 
	void connection();

	//bloquant : attend une trame et renvoi cette trame en string 
	std::string reception();

	//bloquant : envoi un string au serveur 
	void envoi(std::string);

	//On ferme le socket et on delete tout 
	void fermetureSocket();

};

