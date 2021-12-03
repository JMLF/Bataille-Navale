#pragma once

///\file CConnectionServeur.h
///\brief Fichier de déclaration de la classe CConnectionServeur 
///\version 1

#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

///\mainpage 
///\brief Classe de connction au serveur cote client
/// On utilise cette classe cote client pour se connecter et communiquer avec le serveur de jeu 

///ajoute la lib manquante 
#pragma comment(lib, "ws2_32.lib") 

///\def uint (unsigned int)
typedef unsigned int uint;
///\def ushort (unsigned short)
typedef unsigned short ushort;
///\def uchar (unsigned char)
typedef unsigned char uchar;


///\class CConnectionServeur 
///\brief Methode de connection, d'envoi et reception de message avec le serveur de jeu
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
	///\fn CConnectionServeur(std::string IP_SERVEUR, std::string port)
	///\brief Constructeur de la classe avec parametre en entrée 
	///\param[in] IP_SERVEUR:string et port:string
	CConnectionServeur(std::string IP_SERVEUR, std::string port);

	//initialise tout ce qu'il faut
	///\fn initConnec()
	///\brief Initialise tout 
	///\return void
	void initConnec();

	//se connecte au serveur 
	///\fn connection()
	///\brief se connection au serveur entrée en parametre dans le constructeur  
	///\return void
	void connection();

	//bloquant : attend une trame et renvoi cette trame en string 
	///\fn reception()
	///\brief attend de recevoir une trame du serveur (!bloquant) 
	///\warning BLOQUANT 
	///\return string
	std::string reception();
	
	//bloquant : envoi un string au serveur 
	///\fn envoi()
	///\brief envoi une trame au serveur (!bloquant) 
	///\warning BLOQUANT 
	///\param[in] trame a envoyer : string 
	///\return void
	void envoi(std::string);

	//On ferme le socket et on delete tout 
	///\fn fermetureSocket()
	///\brief on ferme le socket et la communication avec le serveur 
	///\return void
	void fermetureSocket();

};

