//Feito pelo Lop�dio Guigui
//Espero q naum d� bug
//Se der, naum foi ele que fez
//Boa sorte a todos n�s!
//Ave Lop�dio!
#include "Tabuleiro.h"
#include <iostream>

int random(int min, int max) //retorna um valor inteiro em no intervalo [min, max]
{
    int r = rand()%(max-min + 1) + min;
    if (r > max || r < min) allegro_message("erro no random");
    return r;
}

Tabuleiro::Tabuleiro()
{
    //ctor
}

Tabuleiro::Tabuleiro(unsigned char colunas_, unsigned char linhas_, unsigned short numMinas_)
{
    colunas = colunas_;
    linhas = linhas_;
    numMinas = numMinas_;
    numDesarmes = 0;
    ganhou = false;
    perdeu = false;
    jogoIniciado = false;
    mouse = false;
    mousePrev = false;
    countingDoubleClick = false;
    isDoubleClicking = false;
    milisecsFromLastChange = 0;
    xIni = ( SCREEN_W - getLargura())/2;
    yIni = 110+ ( SCREEN_H-55 - getAltura())/2;
    criaCelulas();//Cria as c�lulas
}
Tabuleiro::~Tabuleiro()
{
    for (int i = 0; i < linhas; i ++)
        for (int j = 0; j < colunas; j ++)
            delete celula[i][j];
    //delete celula;
}
void Tabuleiro::criaCelulas()
{
    bool* vetorRandom = randomizaMinas();//Cria o vetor de bool, s� pq eu pensei que seria mais r�pido
    celula = new Celula**[linhas];

    for (int i = 0; i < linhas; i ++)
        celula[i] = new Celula*[colunas];
    for (int i = 0; i < linhas; i ++)
        for (int j = 0; j < colunas; j ++)
        {
            celula[i][j] = new Celula( vetorRandom[i*linhas + j], j, i); //Passa o vetor para as c�lulas
        }
    Celula::setTabuleiro(this); //Passa o ponteiro do Tabuleiro
    delete vetorRandom; //Deleta o vetor
}

short Tabuleiro::getXIni()
{
    return xIni;
}
short Tabuleiro::getAltura()
{
    return (linhas/2 )* 46 + 30*(linhas%2==1);
}
short Tabuleiro::getLargura()
{
    return (colunas/2) * 46 + 30*(colunas%2==1);
}
short Tabuleiro::getYIni()
{
    return yIni;
}

bool* Tabuleiro::randomizaMinas()
{
    bool *mat = new bool[linhas * colunas];

    memset(mat, 0, linhas*colunas);

    unsigned short m = numMinas;
    while (m > 0)
    {
        int a = random(0, linhas * colunas - 1 );        //Randomizando bombas iniciais
        if (!mat[a])
        {
        	mat[a] = true;
        	--m;
        }
    }
    return mat;
}

void Tabuleiro::cliqueDoisBotoes(Celula*c)
{
    if (!c->getApertado()) return;
    unsigned char col = c->getX(); //coluna da c�lula c
    unsigned char lin = c->getY(); // Linha da celula c
    unsigned char cont = 0;
    for (int i = lin - 1; i <= lin+1; i++)
        for (int j = col - 1; j <= col+1; j++) //Dois for pra percorrer a redondeza
        {
            if ( !existeCelula(i, j) || (i== lin && j == col))  //VErifica se existe a c�lula
                continue;//N�o preciso me preocupar comigo msm.. :P
            if (c->getTipo() == C_QUADRADO)
                if (i != lin && j != col)
                    continue; //Se for quadrado, n�o quero saber das diagonais
            if (celula[i][j]->getBandeirado()) //Soma o contador
            {
                cont++;
            }
        }
    if ( numMinasCelula(c) == cont)
        apertaProximos(c);
}


unsigned short Tabuleiro::getNumMinas(){return numMinas;}
unsigned char Tabuleiro::getLinhas(){return linhas;}
unsigned char Tabuleiro::getColunas(){return colunas;}
bool Tabuleiro::getGanhou(){return ganhou;}
bool Tabuleiro::getPerdeu(){return perdeu;}
bool Tabuleiro::getJogoIniciado(){ return jogoIniciado;}
unsigned char Tabuleiro::getNumDesarmes(){
    return numDesarmes;
}
void Tabuleiro::acaoVitoria(){
    for (int i=0; i< linhas; i++)
        for (int j = 0; j < colunas; j++)
            celula[i][j]->desarmar(); //Desarmar os n�o clicados
    ganhou = true;
    numDesarmes = numMinas;
}

Celula* Tabuleiro::colidePorVolta(Celula* c)
{
    unsigned char col = c->getX(); //coluna da c�lula c
    unsigned char lin = c->getY(); // Linha da celula c
    for (int i = lin - 1; i <= lin+1; i++) //Verifica s� os quadrados
        for (int j = col - 1; j <= col+1; j++) //Dois for pra percorrer a redondeza
        {
            if (existeCelula(i,j))
                if (celula[i][j]->getTipo() == C_QUADRADO || (i!=lin && j!= col))
                        if (celula[i][j]->colide(mouse_x, mouse_y))
                            return celula[i][j];
        }
    for (int i = lin - 1; i <= lin+1; i++) //Verifica s� octogonos
        for (int j = col - 1; j <= col+1; j++) //Dois for pra percorrer a redondeza
        {
            if (existeCelula(i,j))
                        if (celula[i][j]->colide(mouse_x, mouse_y))
                            return celula[i][j];
        }
        return NULL;
}

void Tabuleiro::updateDoubleClicking(int deltaTimeDecimalSeconds) {
 	std::cout << "Mouse: " << (int)mouse << "; prev: " << (int)mousePrev << "; double: " << (int)isDoubleClicking << "; decsecs: " << (int)milisecsFromLastChange << "\n";

 	static int DOUBLE_CLICK_INTERVAL = 200;
// 	milisecsFromLastChange += deltaTimeDecimalSeconds;
	if (mouse == 0)
	{
		isDoubleClicking = false;
		if (mousePrev != 0)
		{
			milisecsFromLastChange = 0;
			countingDoubleClick = true;
		}
	}
	if (countingDoubleClick && milisecsFromLastChange >= DOUBLE_CLICK_INTERVAL)
	{
		milisecsFromLastChange = DOUBLE_CLICK_INTERVAL + 1;
		countingDoubleClick = false;
	}

	if (countingDoubleClick)
		milisecsFromLastChange += deltaTimeDecimalSeconds;

	if (countingDoubleClick && milisecsFromLastChange < DOUBLE_CLICK_INTERVAL && mouse == 1)
		isDoubleClicking = true;
}

void Tabuleiro::update(int deltaMiliseconds)
{
    if (ganhou || perdeu) return;
    if (mouse_x > xIni && mouse_y > yIni)
    {
        int i = (mouse_y - yIni)/(getAltura()/ linhas); //Linha do mouse
        int j = (mouse_x-xIni)/(getLargura()/ colunas); //Coluna do mouse
        if (existeCelula(i,j))
        {
            Celula* c = colidePorVolta( celula[i][j]); //Pega a colis�o EXATA do bicho!!!
            if(c != NULL) //Verifica se existe C�LULA
            {
                if (mouse == 0 && mousePrev == 1 && !isDoubleClicking){
                    if (!jogoIniciado) primeiroClique(c); //Primeiro clique s� rola
                    cliqueEsquerdo(c);//Clique esquerdo
                }
                else if (mouse == 0 && mousePrev == 3)  cliqueDoisBotoes(c);//Dois cliques
                else if (mouse == 0 && mousePrev != 0 && isDoubleClicking)  cliqueDoisBotoes(c);//Dois cliques
               else if (mouse == 1 && mousePrev ==1 && !isDoubleClicking) pressionaEsquerdo(c);
               else if (mouse == 3 && mousePrev ==3) pressionaDois(c);
               else if (mouse == 0 && mousePrev == 2)  cliqueDireito(c);//Clique direito
               else if (isDoubleClicking) pressionaDois(c);
            }
        }
    }

	updateDoubleClicking(deltaMiliseconds);
    mousePrev = mouse; //Lembran�a antiga do mouse
    mouse = mouse_b; //Lembran�a atual do mouse
}

void Tabuleiro::pressionaDois(Celula*c)
{
    unsigned char col = c->getX(); //coluna da c�lula c
    unsigned char lin = c->getY(); // Linha da celula c
    for (int i = lin - 1; i <= lin+1; i++)
        for (int j = col - 1; j <= col+1; j++) //Dois for pra percorrer a redondeza
        {
            if ( !existeCelula(i, j) )  //VErifica se existe a c�lula
                continue;//N�o preciso me preocupar comigo msm.. :P
            if (c->getTipo() == C_QUADRADO)
                if (i != lin && j != col)
                    continue; //Se for quadrado, n�o quero saber das diagonais
           celula[i][j]->semiApertar();
        }
}

void Tabuleiro::primeiroClique(Celula* c)
{
    jogoIniciado = true;
    if ( numMinasCelula(c) != 0 || c->getMinado())
    {
        modificaMinasCelula(c);
    }
}

void Tabuleiro::modificaMinasCelula(Celula* c)
{
    unsigned char col = c->getX(); //coluna da c�lula c
    unsigned char lin = c->getY(); // Linha da celula c
    unsigned char cont = 0;
    for (int i = lin - 1; i <= lin+1; i++)
        for (int j = col - 1; j <= col+1; j++) //Dois for pra percorrer a redondeza
            if ( existeCelula(i, j))
                if (c->celulaVizinha(celula[i][j]))
                    if (celula[i][j]->getMinado())
                    {
                        celula[i][j]->setMinado(false);
                        cont++;
                    }
    while (cont > 0)
    {
        int lin2 = random(0, linhas-1);
        int col2 = random(0, colunas-1);
        if (!celula[lin2][col2]->getMinado() && !celula[lin2][col2]->celulaVizinha(c))
        {
            celula[lin2][col2]->setMinado(true);
            cont--;
        }
    }
}

void Tabuleiro::draw(BITMAP* buffer)
{
    rectfill(buffer,xIni-1, yIni-1 , xIni + getLargura()-1, yIni +getAltura()-1, makecol(0,32,32));
    for (int i=0; i< linhas; i++)
        for (int j = 0; j < colunas; j++)
            celula[i][j]->draw(buffer); //Imprime todas as c�lulas
}

bool Tabuleiro::existeCelula(int lin, int col)
{
        return lin >= 0 && col >= 0 && lin < linhas && col < colunas; //Verifica se existe a c�lula
}

void Tabuleiro::pressionaEsquerdo(Celula* c)
{
    c->semiApertar();
}

unsigned char Tabuleiro::numMinasCelula(Celula * c) //Perfei��o da natureza
{
    unsigned char col = c->getX(); //coluna da c�lula c
    unsigned char lin = c->getY(); // Linha da celula c
    unsigned char cont = 0;
    for (int i = lin - 1; i <= lin+1; i++)
        for (int j = col - 1; j <= col+1; j++) //Dois for pra percorrer a redondeza
        {
            if ( !existeCelula(i, j) )  //VErifica se existe a c�lula
                continue;//N�o preciso me preocupar comigo msm.. :P
            if (c->getTipo() == C_QUADRADO)
                if (i != lin && j != col)
                    continue; //Se for quadrado, n�o quero saber das diagonais
            if (celula[i][j]->getMinado()) //Soma o contador
                cont++;
        }
    return cont;
}

void Tabuleiro::apertaProximos(Celula* c)
{
    unsigned char col = c->getX(); //coluna da c�lula c
    unsigned char lin = c->getY(); // Linha da celula c
    for (int i = lin - 1; i <= lin+1; i++)
        for (int j = col - 1; j <= col+1; j++) //Dois for pra percorrer a redondeza
        {
            if ( !existeCelula(i, j) )  //VErifica se existe a c�lula
                continue;//N�o preciso me preocupar comigo msm.. :P
            if (c->getTipo() == C_QUADRADO)
                if (i != lin && j != col)
                    continue; //Se for quadrado, n�o quero saber das diagonais
           cliqueEsquerdo( celula[i][j]);
        }
}

void Tabuleiro::cliqueDireito(Celula* c)
{
    if (c->getApertado()) return;
    c-> mudaBandeira();
    if ( c->getBandeirado())
        numDesarmes++;
    else
        numDesarmes--;
}

void Tabuleiro::cliqueEsquerdo(Celula*c) //= M�todo do clique esquerdo
{
    if ( c->getBandeirado() || c->getApertado())
        return;
    c->apertar();
    if (c->getMinado() && !c->getBandeirado()) acaoDerrota(c);
    if ( verificaVitoria() ) acaoVitoria();

}

bool Tabuleiro::verificaVitoria()
{
    int cont = 0;
    for (int i = 0; i < linhas; i++) //Conta quantas c�lulas apertadas existem
        for (int j = 0; j < colunas; j++)
            if (celula[i][j]->getApertado() && !celula[i][j]->getMinado()) cont++;
    return (cont == colunas*linhas - numMinas);
}

void Tabuleiro::acaoDerrota(Celula* c)
{
    c->setCulpado();
    perdeu = true;
    for (int i = 0; i < linhas; i++) //Conta quantas c�lulas apertadas existem
        for (int j = 0; j < colunas; j++)
        {
            if (celula[i][j]->getMinado() )
                celula[i][j]->apertar();
            celula[i][j]->acaoDerrota();
        }
    //imprimir a bomba diferenta na celula
}

