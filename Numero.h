#ifndef NUMERO_H
#define NUMERO_H
#include <allegro.h>

enum eTipoNumero {N_GRANDE, N_PEQUENO};

class Numero
{
    public:
        Numero();
        Numero(short x_, short y_, eTipoNumero tipo_, unsigned char precisao);
        void setValor(int valor_);
        void draw(BITMAP*);
        virtual ~Numero();
    protected:
    private:
        int valor;
        short x;
        short y;
        int largura;
        int altura;
        unsigned char precisao;
        eTipoNumero tipo;
        //static BITMAP* numGrande;
//        static BITMAP* numPequeno;
        BITMAP* imagem;
};

#endif // NUMERO_H
