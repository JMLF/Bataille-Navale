#include "CFonctionServer.h"

int main() 
{
	int nbconnection=0;
	

	CFonctionServer serveur;

	serveur.initWinsock();
	serveur.creaSockEcoute();
	serveur.binding();
	serveur.listening();


	

	while (true)
	{
		
		uint adr_1;
		uint adr_2;
		adr_2 = serveur.accepting();

		nbconnection++;

		if (nbconnection == 1)
		{
			adr_1 = adr_2;
		}
		if (nbconnection == 2)
		{
			std::thread th1(&CFonctionServer::communication, &serveur, adr_1, adr_2);
			th1.detach();
		}
	}







}