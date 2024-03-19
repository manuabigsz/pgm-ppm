#include <iostream>
#include "PGM.hpp"

using namespace std;

int main(void)
{

    int x_c2;
    int x_c1;
    int y_c1;
    int y_c2;

    PGM img1;
    int tam;
    unsigned char corP;
    criarCorDeFundo(&img1,50,50,(unsigned char) 0);

   cout << "Defina a cor do x:";
   cin >> corP;

   desenhaX(&img1, corP);

    gravar(&img1, "cores.pgm");


    
	
	cout << "Pressione uma tecla para encerrar o programa.\n";
	getchar();

    return EXIT_SUCCESS;
}