/*
------------------------------------------------------------------------------------------------------------------
    Seja bem-vindo(a)!

    Este é um projeto desenvolvido para a disciplina de Algoritmos e Estruturas de Dados (SIN 211)
    do curso de Sistemas de Informação da UFV - Universidade Federal de Viçosa Campus Rio Paranaíba.

    O projeto consiste em um jogo de três fases, onde o player ('P') deve se movimentar dentro do tabuleiro
    até alcançar o objetivo ('O'). Serão fornecidas algumas sequências de comandos e o jogador deve decidir
    qual delas usar e quantas vezes usar.

    SOBRE OS COMANDOS:  'F' = player (P) move para frente na direção em que estiver apontado;
                        'D' = player (P) altera a direção uma vez no sentido horário;
                        'E' = player (P) altera a direção uma vez no sentido anti-horário;

    O jogador irá iniciar cada fase possuindo três chances de vencer, caso não consiga atingir o objetivo, o
    jogador perde e o jogo termina (game over). Caso o jogador alcance o objetivo em todas as três fases, o
    jogador vence e o jogo termina. Boa sorte!

-------------------------------------------------------------------------------------------------------------------
    AUTORES: * Fabio Henrique Sena Bastos (Turma: 1 | Matrícula: 7554)
             * Luiz Benedito Alves Neto(Turma: 1 | Matrícula: 7557)
             * Reinaldo Gonçalves Pereira Neto (Turma: 2 | Matrícula: 7627)

-------------------------------------------------------------------------------------------------------------------
    VERSÃO: Alpha 2.5.0

-------------------------------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "tabuleiroEcomandos.h"

int main()
{
    char Tabuleiro[8][8];
    char sentido = 'd'; // sent d = (>) sent b = (V), sent c = (^), sent e = (<)
    int opcao = 5, tentativas = 3, aux, fase = 3, aux2 = 0;

    // Inicialização da estrutura fila
    ComandoFila F;
    Fila *fileira;
    fileira = (Fila *)malloc(sizeof(Fila));

    if (fileira == NULL)
    {
        printf("ERRO! O programa nao pode ser executado. Falha na alocacao de memoria.\n\n");
        exit(1); // O programa encerra caso o sistema não consiga alocar memória para a fila dinâmica.
    }

    inic(fileira);

    // Inicialização da estrutura PILHA
    ComandoPilha P;
    NO2 *pilha;
    iniciar(&pilha);

    system("cls||clear");

    while (tentativas != 0) // As instruções do jogo só executam enquanto o jogador ainda possuir tentativas.
    {

        switch (fase)
        {
        case 1:
            system("color 03");

            if (aux2 == 0)
            {
                tentativas = 3;
                aux2++;
            }

            criar_tabuleiro(Tabuleiro);

            do
            {
                F = registraComandosFila(fileira, fase, sentido, Tabuleiro);

                enfileirar(fileira, F);
                opcao = continuar(opcao);

            } while (opcao != 0);

            ExecucaoClassicaFila(fileira, sentido, Tabuleiro, fase);
            aux = tentativas;
            tentativas = verificarVitoria(tentativas, Tabuleiro);
            if (tentativas == aux)
            {
                fase = passou_de_fase(fase);
            }
            else
            {
                voceFalhou(tentativas);
            }
            system("cls||clear");
            break;
            // SEGUNDA FASE =================================================
        case 2:
            system("color 02");

            if (aux2 == 1)
            {
                tentativas = 3;
                aux2++;
            }

            criar_tabuleiro(Tabuleiro);

            do
            {
                P = registraComandosPilha(pilha, fase, sentido, Tabuleiro);

                empilhar(&pilha, P);

                opcao = continuar(opcao);

            } while (opcao != 0);
            ExecucaoClassicaPilha(&pilha, sentido, Tabuleiro, fase);

            aux = tentativas;
            tentativas = verificarVitoria(tentativas, Tabuleiro);
            if (tentativas == aux)
            {
                fase = passou_de_fase(fase);
            }
            else
            {
                voceFalhou(tentativas);
            }
            system("cls||clear");
            break;
            // FASE TRÊS pt1 ==============================================================================
        case 3:
            system("color 07");

            if (aux2 == 2)
            {
                tentativas = 3;
                aux2++;
            }
            criar_tabuleiro(Tabuleiro);
            sentido = 'd';

            do
            {
                F = registraComandosFila(fileira, fase, sentido, Tabuleiro);

                enfileirar(fileira, F);
                opcao = continuar(opcao);

            } while (opcao != 0);

            sentido = ExecucaoClassicaFila(fileira, sentido, Tabuleiro, fase);
            aux = tentativas;
            tentativas = verificarVitoria(tentativas, Tabuleiro);
            if (tentativas == aux)
            {
                fase = passou_de_fase(fase);
            }
            else
            {
                voceFalhou(tentativas);
            }
            system("cls||clear");
            break;
            // FASE TRÊS pt2 ==============================================================================
        case 4:
            system("color 09");

            if (aux2 == 3)
            {
                tentativas = 3;
                aux2++;
            }
            Tabuleiro[0][0] = 'O';
            do
            {
                P = registraComandosPilha(pilha, fase, sentido, Tabuleiro);
                empilhar(&pilha, P);

                opcao = continuar(opcao);

            } while (opcao != 0);
            ExecucaoClassicaPilha(&pilha, sentido, Tabuleiro, fase);
            aux = tentativas;

            tentativas = verificarVitoriaFinal(tentativas, Tabuleiro);
            if (tentativas == aux)
            {
                fase = passou_de_fase(fase);
                tentativas = 0;
            }
            else
            {
                voceFalhou(tentativas);
            }
            break;
        }
    }
    printf("\n");

    printf("*** FIM DE JOGO ***\n");

    do
    {
        printf("Jogar novamente? (1 = SIM | 0 = NAO)\n");
        printf("--> ");
        scanf("%d", &opcao);

        if (opcao == 1)
            main();
        else if (opcao != 1 && opcao != 0)
            printf("Opcao invalida, tente novamente!\n\n");

    } while (opcao != 1 && opcao != 0);

    system("color");

    free(fileira);
    fileira = NULL;

    return 0;
}
