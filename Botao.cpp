//Feito pelo Lopídio Guigui
//Espero q naum dê bug
//Se der, naum foi ele que fez
//Boa sorte a todos nós!
//Ave Lopídio!
#include "Botao.h"
#include <allegro.h>
#include<X11/Xlib.h>


BITMAP* carregaBitmapBotao(char* nomeArquivo)
{
    BITMAP* bmp = load_bitmap(nomeArquivo, NULL);
    if (!bmp)
    {
        allegro_message("Impossivel carregar '%s'", nomeArquivo);
        exit(1);
    }
    return bmp;
}

Botao::Botao()
{
    //ctor
}

Botao::Botao(eTipoBotao tipo_, int x_, int y_)
{
    tipo = tipo_;
    x = x_;
    y = y_;
    if (tipo == B_AUMENTA)
        imagem = carregaBitmapBotao("Grapphics/botao seta.tga");
    else if (tipo == B_DIMINUE)
        imagem = carregaBitmapBotao("Grapphics/botao seta baixo.tga");
    else if (tipo == B_ALARGA)
        imagem = carregaBitmapBotao("Grapphics/botao seta direita.tga");
    else if (tipo == B_ESTREITA)
        imagem = carregaBitmapBotao("Grapphics/botao seta esquerda.tga");
    else if (tipo == B_MAIS)
        imagem = carregaBitmapBotao("Grapphics/botao mais.tga");
    else if (tipo == B_MENOS)
        imagem = carregaBitmapBotao("Grapphics/botao menos.tga");
    else if (tipo == B_MODO_FACIL)
        imagem = carregaBitmapBotao("Grapphics/botao facil.tga");
    else if (tipo == B_MODO_MEDIO)
        imagem = carregaBitmapBotao("Grapphics/botao medio.tga");
    else if (tipo == B_MODO_DIFICIL)
        imagem = carregaBitmapBotao("Grapphics/botao dificil.tga");
    else if (tipo == B_MODO_LOPIDIO)
        imagem = carregaBitmapBotao("Grapphics/botao lopidio.tga");
    largura = imagem->w;
    altura = imagem->h/2;
    apertado = false;
    mouseAnt = false;
}
Botao::~Botao()
{
    destroy_bitmap(imagem);
}

 bool Botao::clique()
 {
    if (mouse_x <= x || mouse_x >= x + largura || mouse_y <= y || mouse_y >= y + altura)
    {
        apertado = false;
        mouseAnt = false;
        return false;
    }
    bool b = (mouseAnt && !apertado); //Só dá certo se soltar o clique dentro do botão
    mouseAnt = apertado;
    apertado = mouse_b;
    return b;
 }

 void Botao::draw(BITMAP* buffer)
 {
    masked_blit( imagem, buffer, 0, altura*apertado, x, y, largura, altura);
 }
