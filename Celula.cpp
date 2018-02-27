//Feito pelo Lopídio Guigui
//Espero q naum dê bug
//Se der, naum foi ele que fez
//Boa sorte a todos nós!
//Ave Lopídio!
#include "Celula.h"

Tabuleiro* Celula::tabuleiro = NULL;
short Celula::tabXIni = 0;
short Celula::tabYIni = 0;

BITMAP* carregaOctogono()
{
    static BITMAP* retorno = load_bitmap("Grapphics/octogonos.tga", NULL);
    if (retorno)
        return retorno;
    allegro_message("impossivel carregar octogonos");
    exit(1);
}
BITMAP* carregaQuadrado()
{
    static BITMAP* retorno = load_bitmap("Grapphics/quadrados.tga", NULL);
    if (retorno)
        return retorno;
    allegro_message("impossivel carregar quadrados");
    exit(1);
}

Celula::Celula()
{
    //ctor
}

Celula::Celula(bool minado_, unsigned char x_, unsigned char y_)
{
    minado = minado_;
    x = x_;
    y = y_;
    tipo = ( (x+y) %2 ==0 )? C_OCTOGONO: C_QUADRADO; //Definindo o tipo
    errado = false;
    apertado = false;
    culpado = false;
    bandeira = false;
    minasProx = 0;
    octogonoBMP = carregaOctogono();
    quadradoBMP = carregaQuadrado();

//{ xPrint e yPrints
    xPrint = (x/2)* 46;
    if ( y%2 == 0 )
    {
        if(tipo == C_QUADRADO)
            xPrint += 28;
    }
    else
    {
        xPrint += 5;
        if (tipo == C_OCTOGONO)
            xPrint+= 18;
    }
    yPrint = (y/2)*46;
    if ( x%2 == 0 )
    {
        if(tipo == C_QUADRADO)
            yPrint += 28;
    }
    else
    {
        yPrint += 5;
        if (tipo == C_OCTOGONO)
            yPrint+= 18;
    }
//}
    if (tipo == C_OCTOGONO)
    {
        largura = octogonoBMP->w/14;
        altura = octogonoBMP->h;
    }
    else //Se for quadrado
    {
        largura = quadradoBMP->w/10;
        altura = quadradoBMP->h;
    }
}

Celula::~Celula()
{
    //dtor
}

void Celula::setCulpado()
{
    culpado = true;
}

void Celula::mudaBandeira(){
    bandeira = bandeira ^true;
}

void Celula::semiApertar()
{
    if (apertado || bandeira) return;
    semiApertado = true;
}

void Celula::setTabuleiro(Tabuleiro* tabuleiro_) //Pegar o xIni e o Y ini
{
    tabuleiro = tabuleiro_;
    tabXIni = tabuleiro->getXIni();
    tabYIni = tabuleiro->getYIni();
}

unsigned char Celula::getX(){ return x;}
unsigned char Celula::getY(){ return y;}
void Celula::desarmar(){
     if (!apertado)
        bandeira = true;
}
void Celula::armar(){
    if (!apertado)
        bandeira = false;
}

void Celula::acaoDerrota()
{
    if ( bandeira && !minado)
        errado = true;
}
bool Celula::getApertado()
{
    return apertado;
}

bool Celula::celulaVizinha(Celula* c)
{
    unsigned char col = c->getX(); //coluna da célula c
    unsigned char lin = c->getY(); // Linha da celula c
    for (int i = y - 1; i <= y+1; i++)
        for (int j = x - 1; j <= x+1; j++) //Dois for pra percorrer a redondeza da celula dona da classe
        {
            if (tipo== C_QUADRADO)
                if ( i != y && j != x)
                    continue;
            if ( i == lin && j == col) // Se uma delas for a c. retorna true!
                return true;
        }
    return false;
}
bool Celula::getBandeirado()
{
    if (apertado)
    {
        bandeira = false;
    }
    return bandeira;
}

void Celula::apertar()
{
    if (apertado) return;
    if (!apertado && !bandeira)
    {
        apertado = true;
        bandeira = false;
    }
    if (!minado) minasProx = tabuleiro->numMinasCelula(this);
    //Se for 0, chamar apertaProx do tabuleiro! :)
    if ( minasProx ==0 && !minado) tabuleiro->apertaProximos(this);
}

bool Celula::getMinado(){ return minado;}

void Celula::auxDraw(int xIni_, BITMAP* buffer)
{
    if (tipo == C_OCTOGONO)
        masked_blit( octogonoBMP, buffer, xIni_ , 0, xPrint + tabXIni, yPrint+tabYIni, largura, altura);
    else
        masked_blit( quadradoBMP, buffer, xIni_ , 0, xPrint+ tabXIni, yPrint+ tabYIni, largura, altura);
}

void Celula::draw(BITMAP * buffer)
{
    if (tipo == C_OCTOGONO)
    {
        if ( !apertado)
        {
            if (semiApertado)
            {
                auxDraw( 3*largura, buffer); //Imprimir bomba
            }
            else if ( !bandeira)
            {
                auxDraw(0, buffer); //Normal
            }
            else if (errado)
                auxDraw(largura*2, buffer); //Com o X
            else
                auxDraw(largura, buffer); //Com bandeirinha
        }
        else if (culpado && minado)
            auxDraw(largura*13, buffer); //Culpada
        else if (minado)
        {
            auxDraw( 12*largura, buffer); //Imprimir bomba
        }
        else
        {
            auxDraw( (3 + minasProx)*largura, buffer); //Imprimir algum número
        }
    }
    else //Se for quadrado
    {
        if ( !apertado)
        {
            if (semiApertado)
            {
                auxDraw( 3*largura, buffer); //Imprimir bomba
            }
            else if ( !bandeira)
                auxDraw(0, buffer); //Normal
            else if (errado)
                auxDraw(largura*2, buffer); //Com o X
            else
                auxDraw(largura, buffer); //Com bandeirinha
        }
        else if (culpado && minado)
            auxDraw(largura*9, buffer); //Culpada
        else if (minado)
        {
            auxDraw( 8*largura, buffer); //Imprimir bomba
        }
        else
        {
            auxDraw( (3 + minasProx)*largura, buffer); //Imprimir algum número
        }
    }
    semiApertado = false;
}

eTipoCelula Celula::getTipo(){ return tipo;}

short Celula::getXCenter(){
    short xCenter = xPrint;
    if (tipo == C_OCTOGONO)
        xCenter += 15;
    else
        xCenter+= 9;
    return xCenter;
}
short Celula::getYCenter(){
    short yCenter = yPrint;
    if (tipo == C_OCTOGONO)
        yCenter += 15;
    else
        yCenter+= 9;
    return yCenter;
}

bool Celula::colide(int mouseX, int mouseY)
{
    int xCentral = tabXIni + getXCenter();
    int yCentral = tabYIni + getYCenter();
    int xInicial = xPrint + tabXIni;
    int yInicial = yPrint + tabYIni;
    if (tipo == C_OCTOGONO)
    {
        return ( 17*17 > (mouseX - xCentral)* (mouseX - xCentral) + (mouseY - yCentral)*(mouseY - yCentral));
    }
    else
        return (mouseX > xInicial && mouseX <= xInicial + largura && mouseY > yInicial && mouseY <= yInicial + altura);
}

unsigned char Celula::getMinasProx(){return minasProx;}
void Celula::setMinado(bool minado_){ minado = minado_;}

