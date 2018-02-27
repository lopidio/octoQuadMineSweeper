//Feito pelo Lop�dio Guigui
//Espero q naum d� bug
//Se der, naum foi ele que fez
//Boa sorte a todos n�s!
//Ave Lop�dio!
#include "Jogo.h"
#include <stdio.h>

unsigned int* carrega();

unsigned char cript(unsigned char & x)
{
    x = x ^90134534;
    return x;
}

unsigned int cript(unsigned int& x)
{
    x = x ^90134534;
    return x;
}
unsigned short cript(unsigned short& x)
{
    x = x ^90134534;
    return x;
}

unsigned int miliseconds = 0;
void incTempo()
{
    miliseconds++;
}
LOCK_FUNCTION(incTempo);
LOCK_VARIABLE(miliseconds);

bool botaoFechar = false;
void fecharBotao()
{
    botaoFechar = true;
}

Jogo::Jogo()
{
    cenario = load_bitmap("Grapphics/background.tga", NULL);
    if (!cenario)
    {
            allegro_message("impossivel carregar 'Graphics/background.tga'");
            exit(1);
    }
    buffer = create_bitmap( SCREEN_W, SCREEN_H); //Criando o Buffer
//{    Carregando os bot�es
    {
    int modoX = 668, modoY = 22;
    botao = new Botao*[10];
    botao[0] = new Botao(B_ALARGA, 128, 20); //Largura
    botao[1] = new Botao(B_ESTREITA, 32, 20);    //Largura
    botao[2] = new Botao(B_AUMENTA, 128, 69); //Altura
    botao[3] = new Botao(B_DIMINUE, 32, 69);    //Altura
    botao[4] = new Botao(B_MAIS, 128, 118); //numMinas
    botao[5] = new Botao(B_MENOS, 32, 118);    //numMinas
    botao[6] = new Botao(B_MODO_FACIL, modoX , modoY); //Modo f�cil
    botao[7] = new Botao(B_MODO_MEDIO, modoX , modoY + 30); //Modo M�dio
    botao[8] = new Botao(B_MODO_DIFICIL, modoX , modoY + 60); //Modo dif�cil
    botao[9] = new Botao(B_MODO_LOPIDIO, modoX , modoY + 90); //Modo Lop�dio
    botaoPrincipal = new BotaoPrincipal(); //Bot�o principal
    }
//}
//{    Carregando os n�meros
    numero = new Numero*[5];
    numero[0] = new Numero(75,20, N_PEQUENO, 2); //Largura
    numero[1] = new Numero(75,69, N_PEQUENO, 2);  // Altura
    numero[2] = new Numero(67,118, N_PEQUENO, 3); // numMinas
    numero[3] = new Numero(200,40, N_GRANDE, 3);  // numDesarmes
    numero[4] = new Numero(460,40, N_GRANDE, 3);  // Tempo
//}
    FILE* fp = fopen("criptRegister.gui", "rb");
    if (fp == NULL)
    {
        tipoJogo = J_MEDIO;
    }
    else
    {
         unsigned int *vet = carrega();
         tipoJogo = (eTipoJogo)vet[0];
         largura = vet[1];
         if (tipoJogo <0 || tipoJogo > 4) tipoJogo = J_MEDIO;
         altura = vet[2];
         numMinas = vet[3];
         delete vet;
         fclose(fp);
    }
    set_close_button_callback( fecharBotao);
    configuraPorTipo();
    tabuleiro = new Tabuleiro( largura, altura, numMinas);
    iniciado = false;
    configAlterada = false;
    finalizado = false;
    gamePlay();
}

Jogo::~Jogo()
{
    destroy_bitmap(buffer);
    for (int i = 0; i < 10; i++)
        delete botao[i];
    delete botao;
    delete botaoPrincipal;
    for (int i = 0; i < 5; i++)
        delete numero[i];
    delete numero;
    delete cenario;
    delete tabuleiro;
}

void Jogo::drawBotoes()
{
    for (int i = 0; i < 10; i++)
        botao[i]->draw(buffer);
    botaoPrincipal->draw(buffer);
}
void Jogo::drawNumeros()
{
    for (int i = 0; i < 5; i++)
        numero[i]->draw(buffer);
}
void Jogo::configuraPorTipo()
{
    if ( tipoJogo == J_FACIL)
    {
        largura = 11;
        altura = 11;
        numMinas = 11;
    }
    else if ( tipoJogo == J_MEDIO)
    {
        largura = 19;
        altura = 13;
        numMinas = 31;
    }
    else if (tipoJogo == J_DIFICIL)
    {
        largura = 25;
        altura = 15;
        numMinas = 51;
    }
    else if (tipoJogo == J_CUSTOM) //Customizado
        limiteConfiguracao();
    else //Lop�dio!
    {
        largura = 33;
        altura = 17;
        numMinas = 91;
    }
    limiteConfiguracao();
}
void Jogo::updateBotoes()
{
    if ( botao[0]->clique())
    {
        unsigned char aux = largura;
        largura+=2;
        limiteConfiguracao();
        if (aux != largura)
        configAlterada = true;
    }
    else if ( botao[1]->clique())
    {
        unsigned char aux = largura;
        largura-=2;
        limiteConfiguracao();
        if (aux != largura)
        configAlterada = true;
    }
    else if ( botao[2]->clique())
    {
        unsigned char aux = altura;
        altura+=2;
        limiteConfiguracao();
        if (aux != altura)
        configAlterada = true;
    }
    else if ( botao[3]->clique())
    {
        unsigned char aux = altura;
        altura-=2;
        limiteConfiguracao();
        if (aux != altura)
        configAlterada = true;
    }
    else if ( botao[4]->clique())
    {
        unsigned char aux =numMinas;
        numMinas+=2;
        limiteConfiguracao();
        if (aux != numMinas)
        configAlterada = true;
    }
    else if ( botao[5]->clique())
    {
        unsigned char aux = numMinas;
        numMinas-=2;
        limiteConfiguracao();
        if (aux != numMinas)
        configAlterada = true;
    }
    else if (botaoPrincipal->clique()){
        if ( configAlterada) tipoJogo = J_CUSTOM;
        reiniciar();
    }
    else if (botao[6]->clique() ||( key[KEY_ALT] && key[KEY_E] )){
        tipoJogo = J_FACIL;
        configAlterada = false;
        reiniciar();
    }
    else if (botao[7]->clique()  || ( key[KEY_ALT] && key[KEY_M] )){
        tipoJogo = J_MEDIO;
        configAlterada = false;
        reiniciar();
    }
    else if (botao[8]->clique() ||( key[KEY_ALT] && key[KEY_H] )){
        tipoJogo = J_DIFICIL;
        configAlterada = false;
        reiniciar();
    }
    else if (botao[9]->clique()  || ( key[KEY_ALT] && key[KEY_G] )){
        tipoJogo = J_LOPIDIO;
        configAlterada = false;
        reiniciar();
    }
    botaoPrincipal->setDerrota( tabuleiro->getPerdeu());
    botaoPrincipal->setVitoria( tabuleiro->getGanhou());
}
void Jogo::limiteConfiguracao() //Limita a altura, a largura e o n�mero de minas
{
    if (largura > 33) largura = 33;
    if (largura < 11) largura = 11;
    if (altura > 17) altura = 17;
    if (altura < 11) altura = 11;
    int menor = (largura < altura)? largura: altura;
    if (numMinas < menor + 2) numMinas = menor+2;
    if (numMinas > (largura-1)*(altura - 1)) numMinas = (largura-1)*(altura - 1);
    if ( numMinas%2 == 0) numMinas++;
}

void Jogo::updateNumeros()
{
    numero[0]->setValor(largura);
    numero[1]->setValor(altura);
    numero[2]->setValor(numMinas);
    numero[3]->setValor(MAX(0,tabuleiro->getNumMinas()-tabuleiro->getNumDesarmes() ));// lembrar que esse pega do tabuleironumDesarmes()
    numero[4]->setValor( miliseconds/1000);
}

void Jogo::draw()
{
    draw_sprite(buffer, cenario,0,0);
    tabuleiro->draw(buffer);
    drawBotoes();
    drawNumeros();
    circlefill(buffer, mouse_x, mouse_y, 4, makecol(200, 200, 200));
    circle(buffer, mouse_x, mouse_y, 4, makecol(128, 128, 128));
    draw_sprite(screen, buffer,0,0);
}

unsigned int* carrega()
{
    unsigned int * vet = new unsigned int [8];
    FILE* fp = fopen( "criptRegister.gui", "rb");
    if (fp != NULL)
    {
        fscanf( fp, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", &vet[0], &vet[1], &vet[2], &vet[3], &vet[4], &vet[5], &vet[6], &vet[7]);
        for (int i = 0; i < 8; i++)
            cript(vet[i]);
        fclose(fp);
    }
    else
    {
        vet[0] = J_MEDIO;
        vet[1]  = 35;
        vet[2]  = 19;
        vet[3]  = 13;
        vet[4] = 999999999;
        vet[5] = 999999999;
        vet[6] = 999999999;
        vet[7] = 999999999;
    }
    return vet;
}

void salvarRegistros(unsigned int* v)
{
    FILE* fp = fopen("criptRegister.gui", "wb");
    for(int i = 0; i < 8; i++)
        fprintf(fp, "%d " , cript(v[i]));
    for(unsigned int j = cript(v[0])*cript(v[2]); j < 100; j++) //Esse For � s� pra encher o arquivo com n�meros aleat�rios
    {
        unsigned int i = j;
        i = (cript(i)*i/1000);
        fprintf(fp, "%d%d " , 100 - j/10, ABS(i));
    }
    fclose(fp);
}

void Jogo::recorde()
{

    unsigned int* vet = carrega();
    vet[0] = tipoJogo;
    vet[1] = largura;
    vet[2] = altura;
    vet[3] = numMinas;
    salvarRegistros(vet);
    if ( tabuleiro->getGanhou() && tipoJogo !=J_CUSTOM) // Se ganhar e for menor!
    {
        unsigned int * vitoria = carrega();
        allegro_message("Last Time:      %d.%d s\n\nEasy:           %d.%d s\nMedium:       %d.%d s\nHard:           %d.%d s\nGui:              %d.%d s\n", miliseconds/1000, miliseconds%1000, vitoria[4]/10, vitoria[4]%10, vitoria[5]/10, vitoria[5]%10, vitoria[6]/10, vitoria[6]%10, vitoria[7]/10, vitoria[7]%10);
        vitoria[4] = ( tipoJogo == J_FACIL && miliseconds < vitoria[4])?miliseconds: vitoria[4]; //Grava o facilFile
        vitoria[5] = ( tipoJogo == J_MEDIO && miliseconds < vitoria[5])?miliseconds: vitoria[5]; //Grava o medioFile
        vitoria[6] = ( tipoJogo == J_DIFICIL && miliseconds < vitoria[6])?miliseconds: vitoria[6]; //Grava o dificilFile
        vitoria[7] = ( tipoJogo == J_LOPIDIO && miliseconds < vitoria[7])?miliseconds: vitoria[7]; //Grava o lopidioFILE
        salvarRegistros(vitoria);
        delete vitoria;
    }
    delete vet;
}

BITMAP* carregaBitmapPonto(char* nomeArquivo)
{
    BITMAP* bmp = load_bitmap(nomeArquivo, NULL);
    if (!bmp)
    {
        allegro_message("Impossivel carregar '%s'", nomeArquivo);
        exit(1);
    }
    return bmp;
}

void Jogo::pause()
{
    unsigned int* vet = carrega();
    remove_int (incTempo);
    draw_sprite(buffer, cenario,0,0);
    Numero ** n = new Numero*[8];
    BITMAP* ponto = carregaBitmapPonto("Grapphics/ponto.tga");
    int linhaInicial = 40, colunaInicial = 400;
    for (int i = 0; i < 8; i+=2)
    {
        n[i] = new Numero( colunaInicial,linhaInicial+ 136*(i/2), N_GRANDE, 4);
        n[i]->setValor(vet[(i/2)+4]/10);
        n[i + 1] = new Numero( colunaInicial + 211,linhaInicial+ 136*(i/2), N_GRANDE, 1);
        n[i + 1]->setValor(vet[(i/2)+4]%10);
        n[i]->draw(buffer);
        draw_sprite(buffer, ponto, colunaInicial+197, linhaInicial+ 136*(i/2));
        n[i+1]->draw(buffer);
    }
    draw_sprite(screen, buffer,0,0);
    while (!mouse_b && !botaoFechar)
    {
    }
    if (!botaoFechar)
    {
        while (mouse_b){}
    }
    delete vet;
    destroy_bitmap(ponto);
    for (int i = 0; i < 8; i+=2)
        delete n[i];
    delete n;
    if (iniciado && !finalizado) install_int (incTempo, 1);
}

void Jogo::reiniciar()
{
    delete tabuleiro;
    configuraPorTipo();
    iniciado = false;
    remove_int( incTempo);
    finalizado = false;
    limiteConfiguracao();
    miliseconds = 0;
    tabuleiro = new Tabuleiro( largura, altura, numMinas);
}
void Jogo::gamePlay()
{
    while(!botaoFechar)
    {
        if (key[KEY_ESC] || key[KEY_ENTER])
        {
            pause();
        }
        update();
        draw();
    }
}

void Jogo::update()
{
    if (tabuleiro->getJogoIniciado() && !iniciado)
    {
        iniciado = true;
        install_int( incTempo, 1);
    }
    if ( (tabuleiro->getGanhou() || tabuleiro->getPerdeu()) && !finalizado)
    {
        remove_int (incTempo);
        finalizado = true;
        recorde();
    }
    tabuleiro->update(1);
    updateBotoes();
    updateNumeros();
}
