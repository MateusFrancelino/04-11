#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

using namespace std;

const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;

const int TAMANHO_MIRA = 50;

const int ALVOS = 1; // número de alvos que precisam ser destruídos



struct jogador{
    string nome;
    float pontos=99;

};


int main()
{

jogador player[5];

    ifstream ler;
    string dados;
    ler.open("Save.txt");
    for(int j=0;j<5;j++){
    getline(ler,dados);
    cout<<dados<<endl;
    }

    srand(time(0));

    cout << "Digite seu nome de jogador:" << endl << endl;

    string nome;
    cin >> nome;

    cout << endl << endl << "Iniciando Jogo..." << endl;
    cout << endl << "Atire em " << ALVOS << " alvos o mais rapido que puder!" << endl;

    SDL_Init(SDL_INIT_EVERYTHING);

    bool gameOver = false;
    int alvosDestruidos = 0;
    int tempoAnterior = 0;
    int mouseX, mouseY;

    SDL_Rect retangulo = {LARGURA_TELA/2, ALTURA_TELA/2, 50, 50};

    //cria janela & renderizador
    SDL_Window *janela;
    SDL_Renderer *renderizador;
    SDL_CreateWindowAndRenderer(LARGURA_TELA, ALTURA_TELA, 0, &janela, &renderizador);

    // esconde o cursor do mouse
    SDL_ShowCursor(SDL_DISABLE);

    int tempoInicial = SDL_GetTicks(); // armazena o momento em que o jogo inicia

    while (!gameOver) { // game loop

        // verifica se é necessário sortear uma nova posição para o retângulo

        int tempoAtual = SDL_GetTicks();
        if (tempoAtual - tempoAnterior >= 2000) { // já passou dois segundos (2000 milisegundos)?
            retangulo.x = rand() % (LARGURA_TELA - 50);
            retangulo.y = rand() % (ALTURA_TELA - 50);

            tempoAnterior = tempoAtual;
        }

        SDL_Event evento;
        while (SDL_PollEvent(&evento)) { // consome todos os eventos
            switch (evento.type) {
                case SDL_QUIT: // fechamento da janela
                    gameOver = true;
                break;

                case SDL_MOUSEBUTTONDOWN: // clique do mouse

                    //verifica se o jogador acertou o retângulo
                    SDL_GetMouseState(&mouseX, &mouseY); // pega a posição do mouse na tela

                    // verifica se o mouse está encima do retângulo
                    SDL_Point posicaoMouse = {mouseX, mouseY};
                    if(SDL_PointInRect(&posicaoMouse, &retangulo)) {
                        alvosDestruidos++;

                        tempoAnterior = SDL_GetTicks() - 2000; // força que o retângulo apareça em uma nova posição no próximo quadro

                        gameOver = alvosDestruidos >= ALVOS;
                    }

                break;
            }
        }

        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0); // define a cor de fundo para branco
        SDL_RenderClear(renderizador);

        // pega a posição atual do mouse
        SDL_GetMouseState(&mouseX, &mouseY);

        // desenha o retangulo
        SDL_SetRenderDrawColor(renderizador, 0, 255, 80, 0);
        SDL_RenderFillRect(renderizador, &retangulo);

        // desenha a borda do retângulo
        SDL_SetRenderDrawColor(renderizador, 0, 80, 0, 0); // verde escuro
        SDL_RenderDrawRect(renderizador, &retangulo);

        // desenha a mira do mouse em vermelho
        SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 0); // vermelho

        //desenha linha horizontal da mira
        SDL_RenderDrawLine(renderizador, mouseX - TAMANHO_MIRA/2, mouseY, mouseX + TAMANHO_MIRA/2, mouseY);

        // desenha linha vertical da mira
        SDL_RenderDrawLine(renderizador, mouseX, mouseY - TAMANHO_MIRA/2, mouseX, mouseY + TAMANHO_MIRA/2);

        SDL_RenderPresent(renderizador); // mostra o frame na tela

        SDL_Delay(1000/30); // aproximadamente 30 frames por segundo

    }

    int tempoAtual = SDL_GetTicks();
    int tempoTotal = tempoAtual - tempoInicial;


    for (int i=0; i<5; i++)
    {

         if (player[i].pontos<tempoTotal&&player[i].pontos!=tempoTotal)
         {
              player[i].pontos=tempoTotal;
              player[i].nome=nome;
              cout<<nome;
              break;
         }
    }


    ofstream Salvar;
    Salvar.open("Save.txt");

for(int i=0; i<5;i++)
{
     Salvar <<  player[i].nome;
     Salvar << ";";
     Salvar << player[i].pontos;
     Salvar << endl;
}
    Salvar.close();
///////////////////////////////////////////////////////////////////////////////

    cout << endl << endl;
    cout << "Voce destruiu " << alvosDestruidos << " alvos em " << tempoTotal << " milisegundos!" << endl << endl;

    SDL_Quit();

    return 0;
}
