#pragma once
#include <vector>
#include <string>
#include <locale>
class CGrille {
public :
	enum class Case { VIDE, BATEAU, TOUCHEJ,TOUCHEE, EAUJ, EAUE, ERREUR = 99 };
	CGrille();
	Case getCase(int ligne, int colonne);
	void setCase(int ligne, int colonne, Case type);
	void afficherGrille();
	std::vector<std::string> saisieJoueur(std::string abs, int ord, bool maGrille);
	bool partiePerdue();
	std::string placerBateau();
	
	void bateauToucherEnnemi(int ligne, int colonne);
	void bateauToucherAllier(int ligne, int colonne);
	void tirLoupeJoueur(int ligne, int colonne);
	void tirLoupeEnnemi(int ligne, int colonne);
	




	void InitGrille();



private:
	int colonne;
	int ligne;
	Case grille[11][11];
	int nbPorteAvion;
	int nbCroiseur; 
	int nbTorpilleur;
	int nbSousMarin;
};