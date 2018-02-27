#ifndef BOTAOPRINCIPAL_H
#define BOTAOPRINCIPAL_H
#include <allegro.h>

class BotaoPrincipal
{
    public:
        BotaoPrincipal();
        void setVitoria(bool vitoria_);
        void setDerrota(bool derrota_);
        void draw(BITMAP*);
        bool clique();
        virtual ~BotaoPrincipal();
    protected:
    private:
        BITMAP* imagem;
        bool apertado;
        int x;
        int y;
        unsigned char largura;
        unsigned char altura;
        char mouseAnt; //Armazena o valor do mouse_b na iteração anterior
        bool derrota;
        bool vitoria;
};

#endif // BOTAOPRINCIPAL_H
