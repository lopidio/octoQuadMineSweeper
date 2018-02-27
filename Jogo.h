#ifndef JOGO_H
#define JOGO_H
#include <allegro.h>
#include "Botao.h"
#include "BotaoPrincipal.h"
#include "Numero.h"
#include <iostream>

#ifndef TABULEIRO_H
#include "Tabuleiro.h"
#endif

enum eTipoJogo {J_FACIL, J_MEDIO, J_DIFICIL, J_LOPIDIO, J_CUSTOM};

class Jogo
{
    public:
        Jogo();
        virtual ~Jogo();
    protected:
    private:
        bool finalizado;
        void configuraPorTipo();
        void limiteConfiguracao();
        eTipoJogo tipoJogo;
        BITMAP* cenario;
        BITMAP* buffer;
        Botao** botao;
        bool iniciado;
        bool configAlterada; //Diz se tá customizado ou não
        BotaoPrincipal* botaoPrincipal;
        unsigned short numMinas;
        unsigned char largura;
        unsigned char altura;
        Tabuleiro* tabuleiro;
        Numero** numero;
        void reiniciar();
        void gamePlay();
        void drawBotoes();
        void drawNumeros();
        void updateBotoes();
        void updateNumeros();
        void draw();
        void pause();
        void update();
        void recorde();
};

#endif // JOGO_H
