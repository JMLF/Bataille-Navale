#pragma once

///\mainpage 
///\brief Classe qui s'occupe de la gestion de la grille de jeu


#include <vector>
#include <string>

///\file CGrille.h
///\brief Fichier de définition de la classe CGrille 

///\class CGrille CGrille.h
class CGrille {

public :
	
	enum class alphabet {A=0,B,C,D,E,F,G,H,I,J,T,L,P}; //a verifier 

	///\enum Case 
	/// Les differents type de case 
	enum class Case { VIDE, BATEAU, TOUCHEJ,TOUCHEE, EAUJ, EAUE, ERREUR = 99 };
	
	///\fn CGrille
	///\brief constructeur de la classe 
	CGrille();
	
	///\fn getCase
	///\brief retourne l'etat d'une case 
	///\param ligne : int, colonne : int
	///\return Case : enum  
	Case getCase(int ligne, int colonne);
	
	///\fn setCase
	///\brief met une case a un etat 
	///\param ligne : int, colonne : int, type : Case (enum)
	///\return void
	void setCase(int ligne, int colonne, Case type);
	
	///\fn afficherGrille
	///\brief affiche la grille mise a jour 
	///\return void
	void afficherGrille();
	
	std::vector<std::string> saisieJoueur(std::string abs, int ord, bool maGrille);
	
	bool partiePerdue();
	
	std::string placerBateau();

	
	void bateauToucherEnnemi(int ligne, int colonne);
	
	void bateauToucherAllier(int ligne, int colonne);
	
	void tirLoupeJoueur(int ligne, int colonne);
	
	void tirLoupeEnnemi(int ligne, int colonne);
	
	void InitGrille();

	void serialisation(int &x, int &y, std::string trame, alphabet& lettre);

private:

	int colonne;

	int ligne;

	Case grille[11][11];

	int nbPorteAvion;

	int nbCroiseur; 

	int nbTorpilleur;

	int nbSousMarin;

};