#include <iostream>
#include "CGrille.h"
#include <Windows.h>
using namespace std;
int main() {
	



	//std::cout << "                                        "<<endl<<"                 &&&&&&&                "<<endl<<"                 &&&&&&&                "<<endl<<"                 &&&&&&&                " <<endl<< "                                        "<<endl<<"       &&&&&&&&  &&&&&&&  &&&&&&&&      "<<endl<<"       &&&&&&&  &&&&&&&  &&&&&&&&      "<<endl<<"       &&&&&&&&  &&&&&&&  &&&&&&&&      " <<endl<< "                                        ";
	system("pause");
	CGrille echoe;
	echoe.InitGrille();
	//echoe.getCase(1, 1);
	//echoe.setCase(5, 5, CGrille::Case::EAUJ);
	//echoe.setCase(5, 6, CGrille::Case::EAUE);
	//echoe.setCase(5, 6, CGrille::Case::TOUCHEE);
	echoe.afficherGrille();
	echoe.placerBateau();
	system("pause");
	echoe.bateauToucherAllier(1, 1);
	echoe.bateauToucherEnnemi(5, 5);







	return 0;
}
	