#pragma once
#include <vector>
#include <string>
class CGrille {
private :
	int collone;
	int ligne;
	std::vector<std::string> grille;
public :
	CGrille();
	enum class Case{ VIDE,BATEAU,TOUCHE,EAU,ERREUR = 99};
	Case getCase(int ligne, std::string collone);
	void setCase(int ligne, std::string collone, Case type);
	void afficherGrille();
	std::vector<std::string> saisieJoueur();
	bool partiePerdue();

};