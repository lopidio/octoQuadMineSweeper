#ifndef BOTAO_H
#define BOTAO_H
#include <allegro.h>

enum eTipoBotao { B_AUMENTA, B_DIMINUE, B_MODO_FACIL, B_MODO_MEDIO, B_MODO_DIFICIL, B_MODO_LOPIDIO, B_ALARGA, B_ESTREITA, B_MAIS, B_MENOS};

class Botao
{
    public:
        Botao();
        Botao(eTipoBotao tipo_, int x_, int y_);
        bool clique();
        virtual void draw(BITMAP*);
        virtual ~Botao();
    protected:
        eTipoBotao tipo;
        BITMAP* imagem;
        bool apertado;
        int x;
        int y;
        unsigned char largura;
        unsigned char altura;
        char mouseAnt; //Armazena o valor do mouse_b na iteração anterior
    private:
};

#endif // BOTAO_H
