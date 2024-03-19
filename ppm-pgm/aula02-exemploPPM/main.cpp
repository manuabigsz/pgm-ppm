#include <iostream>
#include "PPM.hpp"
#include "PGM.hpp"

using namespace std;

int main(void)
{

	PPM img2;
	int x1;
	int y1;
	int x2;
	int y2;
	bool isValid = false;
	cout << "#Set Linha#\n";
	criar(&img2, 500, 500);
	// ler(&img2, "numeros.ppm");

	// PGM nova = convertePGM(&img2);
	// inverteImagem(&img2);
	atribuiCorLinha(&img2);
	// marcaAreaComTamanho(&img2, 200, 200, 500, 500, RGB(255,130,2),20);

	gravar(&img2, "com_borda.pgm");

	cout << "Pressione uma tecla para encerrar o programa.\n";
	getchar();
	return EXIT_SUCCESS;
}