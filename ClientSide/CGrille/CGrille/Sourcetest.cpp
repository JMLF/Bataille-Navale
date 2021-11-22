#include <iostream>
#include "CGrille.h"
#include <Windows.h>

int main() {
	CGrille echoe;
	//echoe.getCase(1, 1);
	echoe.afficherGrille();
	echoe.placerBateau(1, 'A');
	return 0;
}
	