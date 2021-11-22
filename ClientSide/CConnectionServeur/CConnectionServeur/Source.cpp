#include <iostream>
#include "CConnectionServeur.h"

int main(int argc, char* argv[])
{
    //Verif des arguments -----------------------------------------------------------------------------------------

    if (argc != 3) //different de 3 car exe vaut pour 1
    {
        std::cout << " manque 1 argument ( IP / Port ) " << std::endl;
        return 0;
    }
    //--------------------------------------------------------------------------------------------------------------




    std::cout << "Hello World!\n";
}