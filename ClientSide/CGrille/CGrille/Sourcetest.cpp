#include <iostream>
#include "CGrille.h"
#include <Windows.h>

int main() {
	CGrille echoe;
	echoe.InitGrille();
	//echoe.getCase(1, 1);
	echoe.setCase(5, 5, CGrille::Case::EAUJ);
	echoe.setCase(5, 6, CGrille::Case::EAUE);
	echoe.setCase(5, 6, CGrille::Case::TOUCHEE);
	echoe.afficherGrille();
	echoe.placerBateau();
	return 0;
}
	