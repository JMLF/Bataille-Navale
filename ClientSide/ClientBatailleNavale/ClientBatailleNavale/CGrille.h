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
	
	enum class alphabet {A=1,B,C,D,E,F,G,H,I,J=9}; //a verifier 
	enum class resultat { F, T, L, G, P };
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

	
	void XGrilleEnnemie(int ligne, int colonne);
	
	void XGrilleJoueur(int ligne, int colonne);
	
	void TildGrilleEnnemie(int ligne, int colonne);
	
	void TildGrilleJoueur(int ligne, int colonne);
	
	void InitGrille();

	void serialisation(int& x, int& y, std::string trame, resultat& lettre);

	

private:
	static int const TAILLEGRILLE = 11;

	int colonne;

	int ligne;

	Case grille[TAILLEGRILLE][TAILLEGRILLE];

	int nbPorteAvion;

	int nbCroiseur; 

	int nbTorpilleur;

	int nbSousMarin;

};