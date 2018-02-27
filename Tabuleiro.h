#ifndef TABULEIRO_H
#define TABULEIRO_H
#include <allegro.h>
#include <time.h>

#ifndef CELULA_H
#include "Celula.h"
#endif

class Celula;

class Tabuleiro
{
    public:
        Tabuleiro();
        Tabuleiro(unsigned char colunas_, unsigned char linhas_, unsigned short numMinas_);//---
        unsigned char numMinasCelula(Celula*); //Responde qtas minas existem pr�xima � c�lula
        void apertaProximos(Celula*);// Aperta ao redor da mina.. Caso seja 0
        unsigned short getNumMinas(); //---
        short getXIni(); //----
        short getYIni(); // -----
        unsigned char getLinhas(); //===
        unsigned char getColunas();//===
        bool getGanhou();//===
        bool getPerdeu();//===
        bool getJogoIniciado();//===
        void draw(BITMAP*); //===
        unsigned char getNumDesarmes(); //=
        void update(int deltaTimeDecimalSeconds);
        virtual ~Tabuleiro();
    protected:
    private:
        Celula* colidePorVolta(Celula*); // Retorna a colis�o EXATA
        void criaCelulas();
        short getLargura(); //----
        short getAltura();// ----
        void pressionaEsquerdo(Celula*);
        void pressionaDois(Celula*);
        void cliqueEsquerdo(Celula*); //= M�todo do clique esquerdo
        void cliqueDireito(Celula*); //== Lique direito, bota e desbota a bandeira.. :P
        void cliqueDoisBotoes(Celula*);
        void acaoVitoria(); //====
        void acaoDerrota(Celula*); //Recebe a c�lula minada
        bool* randomizaMinas(); // ----
        bool existeCelula(int, int); //=====
        void primeiroClique(Celula*);
        void modificaMinasCelula(Celula*);
        bool verificaVitoria(); // Dentro do clique esquero... Faz as contagens.. E v� se o cara ganhou
	void updateDoubleClicking(int deltaTimeDecimalSeconds);

	//{ Atributos
        unsigned char colunas;
        unsigned char linhas;
        unsigned short numMinas;
        unsigned short numDesarmes;
        Celula *** celula;
        short xIni;
        short yIni;
        bool ganhou;
        bool perdeu;
        bool jogoIniciado;
        bool countingDoubleClick;
        bool isDoubleClicking;
        int milisecsFromLastChange;
        char mouse;
        char mousePrev;
//}
};

#endif // TABULEIRO_H
