#include "CClientServer.h"

void CClientServer::initServer()
{
	WSAStartup(nVersion, &donneeWS);

	//crea socket ecoute 

	if ((ids_ecoute = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		throw("Echec creation Socket");
		exit(1);
	}

	//binding

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
		throw("Echec Attachement Socket");
		exit(1);
	}

	//ecoute

	if (listen(ids_ecoute, 2) == SOCKET_ERROR)
	{
		throw("Echec Lecture");
		exit(1);
	}
	std::cout << "Serveur en ecoute " << std::endl; //pour le debug 

	//ensuite il faut appeler la fonction accepting 

}

uint CClientServer::accepting()
{
	// Acceptation d'une connexion cliente, création d'un nouveau socket qui 
	   // sera utilisé pour l'émission et la réception des caractères 
	   // @ inet du clietnt est récupérée
	addr_len = sizeof(adr_client);

	ids_connect = accept(ids_ecoute, (struct sockaddr*)&adr_client, &addr_len);
	return ids_connect;
}

void CClientServer::communication(uint ids_connect, uint ids_connect1)
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

	std::string Avous = "Serveur: communication";

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

}

void CClientServer::fermetureServer()
{

	closesocket(ids_connect);
	closesocket(ids_connect1);
	closesocket(ids_ecoute);
	WSACleanup();
}

void CClientServer::initClient(std::string IP_SERVEUR, std::string port)
{
	try
	{
		this->IP_SERVEUR = IP_SERVEUR;
		this->port = port;
		this->NUM_PORT = stoi(port);
	}
	catch (...)
	{
		throw("Mauvais format du port");
	}

	if (NUM_PORT <= 0)
	{
		throw("Port inferieur egal a 0");
	}

	//-

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

	// -

	if (connect(ids_client, (struct sockaddr*)&adr_serveur, sizeof(adr_serveur)) < 0)
	{
		throw("Echec connexion");
		exit(1);
	}

	// -



}

std::string CClientServer::reception()
{
	const ushort DIMMAX = 150; // Taille max des tableaux

	char trame_lect[DIMMAX + 1];

	// Reçoit la reponse du serveur
	noctets = recv(ids_client, trame_lect, DIMMAX, 0);
	trame_lect[noctets] = '\0';
	return trame_lect;
}

void CClientServer::envoi(std::string requete)
{
	send(ids_client, requete.c_str(), DIMMAX, 0);
}

void CClientServer::fermetureClient()
{
	// fermeture le socket ouvert
	closesocket(ids_client); // à la place de close() sous Linux

	// Fermeture de winsock
	WSACleanup();
}
