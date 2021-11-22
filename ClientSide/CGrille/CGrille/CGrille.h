#pragma once
#include <vector>
#include <string>
class CGrille {
public :
	enum class Case { VIDE, BATEAU, TOUCHE, EAU, ERREUR = 99 };
	CGrille();
	Case getCase(int ligne, int colonne);
	void setCase(int ligne, int colonne, Case type);
	void afficherGrille();
	std::vector<std::string> saisieJoueur(std::string abs, int ord, bool maGrille);
	bool partiePerdue();
	std::string placerBateau(int ligne, char colonne);





private:
	int colonne = 10;
	int ligne = 10;
	Case grille[10][10];
	int nbPorteAvion = 1;
	int nbCroiseur = 1; 
	int nbTorpilleur = 2;
	int nbSousMarin = 3;
};