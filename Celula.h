#ifndef CELULA_H
#define CELULA_H
#include <allegro.h>

#ifndef TABULEIRO_H
#include "Tabuleiro.h"
#endif

class Tabuleiro;

enum eTipoCelula { C_OCTOGONO, C_QUADRADO};

class Celula
{
    public:
        Celula();
        Celula(bool minado_, unsigned char x_, unsigned char y_);
        static void setTabuleiro(Tabuleiro* tabuleiro_); //Pegar o xIni e o Y ini
        unsigned char getX();
        unsigned char getY();
        bool celulaVizinha(Celula*);
        bool getApertado();
        void desarmar();
        void mudaBandeira();
        void armar();
        void apertar(); //Chama o ponteiro do tabuleiro numMinasCelula!
        bool getMinado();
        void semiApertar();
        bool getBandeirado();
        void draw(BITMAP*);
        eTipoCelula getTipo();
        short getXCenter();
        short getYCenter();
        bool colide(int mouseX, int mouseY);
        void acaoDerrota(); //Bota os X nas minas erradas
        unsigned char getMinasProx();
        void setCulpado();
        void setMinado(bool minado_); //Método que muda se possui mina ou não
        virtual ~Celula();
    protected:
    private:
        void auxDraw( int xIni_, BITMAP* buffer);
        bool errado; //Diz se o desarme foi correto
        bool culpado; // Diz se é a bomba apertada pra que o cara tenha perdido
        bool semiApertado;
        bool minado;
        bool apertado;
        bool bandeira;
        unsigned char minasProx;
        eTipoCelula tipo;
        BITMAP* octogonoBMP; //Gambiarra para virar estático!
        BITMAP* quadradoBMP;
        static Tabuleiro* tabuleiro; //Ponteiro para o tabuleiro;
        unsigned char x;
        unsigned char y;
        unsigned char largura;
        unsigned char altura;
        static short tabXIni;
        static short tabYIni;
        short xPrint;
        short yPrint;
};

#endif // CELULA_H
