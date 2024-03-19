#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct PGM
{
    string tipo;
    int larg;
    int alt;
    int vmax;
    unsigned char *pixels; // unsigned char -> 0 a 255
    PGM()                  // construtor -> inicializar variaveis
    {
        pixels = nullptr;
        larg = 0;
        alt = 0;
        vmax = 255;
        tipo = "";
    }
};

void destruir(PGM *pgm)
{
    if (pgm->pixels)
        delete pgm->pixels;
    pgm->pixels = nullptr;
    pgm->larg = 0;
    pgm->alt = 0;
    pgm->tipo = "";
    pgm->vmax = 255;
}

void imprimir(PGM *pgm)
{
    cout << "\nPGM\n";
    cout << "Tipo: " << pgm->tipo << endl;
    cout << "Dimensao: " << pgm->larg << "x" << pgm->alt << endl;
    cout << "vMax: " << pgm->vmax << endl;
    if (pgm->pixels) // verifica se o vetor de pixels está alocado
        cout << "Vetor de pixels: " << &(pgm->pixels) << endl;
    else
        cout << "Vetor de pixels: NULL\n";
}

void criar(PGM *pgm, int largura, int altura)
{
    if (pgm->pixels)
        delete pgm->pixels;

    int tamanho = largura * altura;

    pgm->tipo = "P2";
    pgm->larg = largura;
    pgm->alt = altura;
    pgm->vmax = 255;
    pgm->pixels = new unsigned char[tamanho];

    // definir a cor preta para todos os pixels
    for (int i = 0; i < tamanho; i++)
        pgm->pixels[i] = 0;
}

bool gravar(PGM *pgm, string caminho)
{
    if (!pgm->pixels)
        return false;

    ofstream arq;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    arq << pgm->tipo << endl;

    arq << pgm->larg << " " << pgm->alt << endl;

    arq << 255 << endl; // valor máximo de cor fixo em 255

    int tam = pgm->larg * pgm->alt;
    for (int i = 0; i < tam; i++)
    {
        arq << (int)pgm->pixels[i] << endl;
        arq.flush();
    }

    arq.close();
    return true;
}

string lerLinhaArquivo(std::ifstream &arq)
{
    string linha = "", dadoLido = "";
    while (!arq.eof())
    {
        linha = "";
        std::getline(arq, linha);
        if (linha.size() > 0 && linha[0] != '#')
            return linha;
    }
    return linha;
}

bool ler(PGM *pgm, string caminho)
{
    ifstream arq;
    string dado;
    stringstream str;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    // ler o tipo
    dado = lerLinhaArquivo(arq);
    if (dado == "P2")
        pgm->tipo = dado;
    else
    {
        cout << "PGM: erro ao ler o tipo da imagem\n";
        return false;
    }

    // ler largura e altura
    dado = lerLinhaArquivo(arq);
    str = stringstream(dado);
    if (!(str >> pgm->larg))
    {
        cout << "PGM: erro ao ler a largura\n";
        return false;
    }
    if (!(str >> pgm->alt))
    {
        cout << "PGM: erro ao ler a largura\n";
        return false;
    }

    // ler vmax
    dado = lerLinhaArquivo(arq);
    str = stringstream(dado);
    if (!(str >> pgm->vmax))
    {
        cout << "PGM: erro ao ler vmax\n";
        return false;
    }

    if (pgm->pixels)
        delete pgm->pixels;

    int tam = pgm->larg * pgm->alt;

    pgm->pixels = new unsigned char[tam];

    int i = 0, p;
    while (!arq.eof())
    {

        if (arq >> p)
        {
            if (i < tam)
                pgm->pixels[i] = (unsigned char)p;
            i++;
        }
        else
            break;
    }

    if (i != tam)
    {
        cout << "PGM: erro ao ler os pixels\n";
        return false;
    }
    arq.close();
    return true;
}

unsigned char getPixel(PGM *pgm, int x, int y)
{
    if (!pgm->pixels)
        return 0;

    return pgm->pixels[y * pgm->larg + x];
}

void setPixel(PGM *pgm, int x, int y, unsigned char cor)
{
    if (!pgm->pixels)
        return;

    pgm->pixels[y * pgm->larg + x] = cor;
}

// Lista 1 - Exercicio 4
void criarCorDeFundo(PGM *pgm, int largura, int altura, unsigned char corFundo)
{
    cout << corFundo;
    if (pgm->pixels)
        delete pgm->pixels;

    int tamanho = largura * altura;

    pgm->tipo = "P2";
    pgm->larg = largura;
    pgm->alt = altura;
    pgm->vmax = 255;
    pgm->pixels = new unsigned char[tamanho];

    // definir a cor preta para todos os pixels
    for (int i = 0; i < tamanho; i++)
        pgm->pixels[i] = corFundo;
}

// Lista 1 - Exercicio 5
void setLinha(PGM *pgm, int linha, unsigned char cor)
{
    if (linha > 0 && linha < pgm->larg)
    {
        for (int i = 0; i < pgm->larg; i++)
        {
            setPixel(pgm, i, linha, cor);
        }
    }
}

void setColuna(PGM *pgm, int coluna, unsigned char cor)
{
    cout << "entrou em setColuna";
    if (coluna > 0 && coluna < pgm->alt)
    {
        for (int i = 0; i < pgm->alt; i++)
        {
            cout << "setPixel";
            setPixel(pgm, coluna, i, cor);
        }
    }
}

// Lista 1 - Exercicio 6
bool coordValida(PGM *pgm, int x, int y)
{
    for (int i = 0; i < pgm->larg; i++)
    {
        for (int j = 0; j < pgm->alt; j++)
        {
            if (i == x && j == y)
            {
                return true;
            }
        }
    }
    return false;
}

// Lista 1 - Exercicio 7
void preencheRegiao(PGM *pgm, int x1, int y1, int x2, int y2, unsigned char corFundo)
{

    int xMin = min(x1, x2);
    int xMax = max(x1, x2);
    int yMin = min(y1, y2);
    int yMax = max(y1, y2);

    for (int i = xMin; i <= xMax; i++)
    {
        for (int j = yMin; j <= yMax; j++)
        {
            setPixel(pgm, i, j, corFundo);
        }
    }
}

void criarCorLinhas(PGM *pgm)
{
    for (int i = 0; i < pgm->alt; i++)
    {
        if (((i + 1) % 50 == 0))
        {
            for (int j = 0; j < pgm->larg; j++)
            {
                setPixel(pgm, j, i, (unsigned char)255);
            }
        }
    }
}

void inverteImagem(PGM *pgm)
{
    for (int x = 0; x < pgm->larg; x++) // y
    {
        for (int y = 0; y <= pgm->alt / 2; y++) // x
        {

            unsigned char get1 = getPixel(pgm, x, (pgm->alt - y - 1));
            unsigned char get2 = getPixel(pgm, x, y);

            setPixel(pgm, x, y, get1);
            setPixel(pgm, x, (pgm->alt - y - 1), get2);
        }
    }
}

PGM geraNovCorte(PGM *pgm, int x1, int y1, int x2, int y2)
{
    PGM nova;
    criarCorDeFundo(&nova, 500, 500, (unsigned char)0);

    int xMin = min(x1, x2);
    int xMax = max(x1, x2);
    int yMin = min(y1, y2);
    int yMax = max(y1, y2);

    for (int i = xMin; i <= xMax; i++)
    {
        for (int j = yMin; j <= yMax; j++)
        {
            unsigned char get1 = getPixel(pgm, i, j);
            setPixel(&nova, i, j, get1);
        }
    }
    return nova;
}

void geraBorda(PGM *pgm, int espessura)
{

    for (int x = 0; x <= pgm->larg; x++)
    {
        for (int y = 0; y <= pgm->alt; y++)
        {
            if (x <= espessura - 1 || y <= espessura - 1 ||
                x >= pgm->larg - espessura || y >= pgm->alt - espessura)
            {
                cout << "é igual a " << espessura << "\n";
                setPixel(pgm, x, y, (unsigned char)255);
            }
        }
    }
}

void geraBordaSetLinha(PGM *pgm, int espessura)
{

    for (int x = 0; x <= espessura; x++)
    {

        setLinha(pgm, x, (unsigned char)255);
    }

    for (int x = pgm->alt - 1; x >= pgm->alt - espessura; x--)
    {
        setLinha(pgm, x, (unsigned char)255);
    }

    for (int y = 0; y <= pgm->larg; y++)
    {
        if (y <= espessura)
        {
            setColuna(pgm, y, (unsigned char)255);
        }
    }

    for (int y = 0; y <= pgm->larg; y++)
    {
        if (y >= pgm->alt - espessura)
        {
            setColuna(pgm, y, (unsigned char)255);
        }
    }
}

void desenhaX(PGM *pgm, unsigned char cor)
{
    for (int x = 0; x < pgm->alt; x++)
    {
        for (int y = 0; y < pgm->larg; y++)
        {
            if (x==y || x+y == pgm->larg-1)
            {
                setPixel(pgm, x, y, cor);
            }
        }
    }

   
}
#endif