//Feito pelo Lopídio Guigui
//Espero q naum dê bug
//Se der, naum foi ele que fez
//Boa sorte a todos nós!
//Ave Lopídio!
#include "Numero.h"

BITMAP* carrega(char* nomeArquivo)
{
    BITMAP* retorno = load_bitmap(nomeArquivo, NULL);
    if (retorno)
        return retorno;
    allegro_message("impossivel carregar %s",nomeArquivo);
    exit(1);
}

/*BITMAP* Numero::numGrande = carrega("Numeros grandes");
BITMAP* Numero::numPequeno = carrega("Numeros pequenos.bmp");*/


Numero::Numero()
{
    //ctor
}

Numero::Numero(short x_, short y_, eTipoNumero tipo_, unsigned char precisao_)
{
    x = x_;
    y = y_;
    tipo = tipo_;
    precisao = precisao_;
    valor = 0;
    if (tipo == N_GRANDE)
    {
        imagem = carrega("Grapphics/Numeros grandes.tga");//numGrande;
    }
    else
    {
        imagem = carrega("Grapphics/Numeros pequenos.tga");//numPequeno;
    }
        largura = imagem->w/10;
        altura = imagem->h;
}

Numero::~Numero()
{
    destroy_bitmap(imagem);
}

void Numero::setValor(int valor_)
{
    valor = valor_;
}

void Numero::draw(BITMAP* buffer)
{
    BITMAP* aux = create_bitmap(largura*precisao,altura);
    int p = precisao;
    int x2 = valor; //Variavel auxiliar
    for (;p>0 ;p--)
    {
        blit(imagem, aux, (x2%10)*largura,0, (p-1)*largura,0,largura,altura);
        x2/=10;
    }
    draw_sprite(buffer,aux,x,y);
    destroy_bitmap(aux);
}

