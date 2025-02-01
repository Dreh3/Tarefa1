//Código desenvolvido por Andressa Sousa Fonseca

//Incluindo bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"


//Arquivo .pio
#include "pio_matrix.pio.h"

#define IS_RGBW false
static volatile uint32_t tempo_anterior = 0;
static volatile uint acumulador = 0;
PIO pio = pio0;
int sm =0;

//Definindo pinos
#define ButtonA 5       //Pino do botão A
#define ButtonB 6       //Pino do botão B
#define MatrizLeds 7    //Pino da Matriz de Leds 5x5
#define LedG 11         //Pino do Led Verde
#define LedB 12         //Pino do Led Azul
#define LedR 13         //Pino do Led Vermelho

//Função para iniciar pinos e configurá-los como entrada/saída
void config_pinos(){
    //Inicialização
    gpio_init(ButtonA);
    gpio_init(ButtonB);
    gpio_init(LedR);
    gpio_init(LedG);
    gpio_init(LedB);

    //Entrada/Saída
    gpio_set_dir(ButtonA, GPIO_IN); //Definindo Botões como entrada
    gpio_set_dir(ButtonB, GPIO_IN);
    gpio_set_dir(LedR, GPIO_OUT);   //Definindo Leds como saída
    gpio_set_dir(LedG, GPIO_OUT);
    gpio_set_dir(LedB, GPIO_OUT);

    gpio_pull_up(ButtonA);  //Definindo Botões como Pull-Up
    gpio_pull_up(ButtonB);
};

                               //Configurações para a matriz de Leds
                               
//Definindo struct para cores personalizadas
typedef struct {
    double red;
    double green;
    double blue;
}Led_RGB;

//Definindo tipo Cor
typedef Led_RGB COR_RGB;

// Definição de tipo da matriz de leds
typedef Led_RGB Matriz_leds[5][5];

//Retorno o valor binário para a cor passada por parâmetro
uint32_t cor_binario (double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255; 
  G = g * 255;  
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

//Função responsável por acender os leds desejados 
void acender_leds(Matriz_leds matriz){
    //Primeiro for para percorrer cada linha
    for (int linha =4;linha>=0;linha--){
        /*
        Devido à ordem de disposição dos leds na matriz de leds 5X5, é necessário
        ter o cuidado para imprimir o desenho na orientação correta. Assim, o if abaixo permite o 
        desenho saia extamente como projetado.
        */

        if(linha%2){                             //Se verdadeiro, a numeração das colunas começa em 4 e decrementam
            for(int coluna=0;coluna<5;coluna++){
                uint32_t cor = cor_binario(matriz[linha][coluna].blue,matriz[linha][coluna].red,matriz[linha][coluna].green);
                pio_sm_put_blocking(pio, sm, cor);
            };
        }else{                                      //Se falso, a numeração das colunas começa em 0 e incrementam
            for(int coluna=4;coluna>=0;coluna--){
                uint32_t cor = cor_binario(matriz[linha][coluna].blue,matriz[linha][coluna].red,matriz[linha][coluna].green);
                pio_sm_put_blocking(pio, sm, cor);
            }
        }
    }
}

//Função para fazer o led vermelho piscar continuamente 5 vezes por segundo
void piscar_ledR(){
        gpio_put(LedR, 0.2);
        sleep_ms(100);
        gpio_put(LedR, 0);
        sleep_ms(100);
};

//Função para mostrar números na matriz de leds
void numeros(){

    //Declarando variáveis necessárias para modificar intensidade
    int inten =4, inten2 =2;

    //Definindo cores e tonalidades
    COR_RGB apagado = {0.0,0.0,0.0};
    COR_RGB vermelhoForte = {0.5*inten,0.0,0.0};
    COR_RGB vermelhoClaro = {0.2*inten2,0.0,0.0};
    COR_RGB azulForte = {0.0,0.0,0.5*inten};
    COR_RGB azulClaro = {0.0,0.0,0.2*inten2};
    COR_RGB verdeForte = {0.0,0.5*inten,0.0};
    COR_RGB verdeClaro = {0.0,0.2*inten2,0.0};
    COR_RGB marromForte = {0.345*inten2,0.065*inten2,0.065*inten2};
    COR_RGB marromClaro = {0.69*inten,0.13*inten,0.13*inten};
    COR_RGB magentaForte = {0.5*inten,0.0,0.5*inten};
    COR_RGB magentaClaro = {0.25*inten2,0.0,0.25*inten2};


    //Foram estabelecidos 6 frames para cada um dos Leds

    //Matriz que mostrará o zero com transição de tonalidade da esquerda para a direita
    Matriz_leds zero [] =
    {
        {{apagado, vermelhoForte, vermelhoForte, vermelhoForte, apagado},
        {vermelhoForte, apagado, apagado,apagado, vermelhoForte},
        {vermelhoForte, apagado, vermelhoForte,apagado, vermelhoForte},
        {vermelhoForte, apagado, apagado,apagado, vermelhoForte},
        {apagado, vermelhoForte, vermelhoForte, vermelhoForte,apagado}},
        {{apagado, vermelhoForte, vermelhoForte, vermelhoForte, apagado},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoForte},
        {vermelhoClaro, apagado, vermelhoForte,apagado, vermelhoForte},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoForte},
        {apagado, vermelhoForte, vermelhoForte, vermelhoForte,apagado}},
        {{apagado, vermelhoClaro, vermelhoForte, vermelhoForte, apagado},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoForte},
        {vermelhoClaro, apagado, vermelhoForte,apagado, vermelhoForte},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoForte},
        {apagado, vermelhoClaro, vermelhoForte, vermelhoForte,apagado}},
        {{apagado, vermelhoClaro, vermelhoClaro, vermelhoForte, apagado},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoForte},
        {vermelhoClaro, apagado, vermelhoClaro,apagado, vermelhoForte},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoForte},
        {apagado, vermelhoClaro, vermelhoClaro, vermelhoForte,apagado}},
        {{apagado, vermelhoClaro, vermelhoClaro, vermelhoClaro, apagado},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoForte},
        {vermelhoClaro, apagado, vermelhoClaro,apagado, vermelhoForte},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoForte},
        {apagado, vermelhoClaro, vermelhoClaro, vermelhoClaro,apagado}},
        {{apagado, vermelhoClaro, vermelhoClaro, vermelhoClaro, apagado},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoClaro},
        {vermelhoClaro, apagado, vermelhoClaro,apagado, vermelhoClaro},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoClaro},
        {apagado, vermelhoClaro, vermelhoClaro, vermelhoClaro,apagado}}
    };
    //Matriz que mostrará o um com transição de tonalidade da esquerda para a direita
    Matriz_leds um[] =
    {
        {{apagado, apagado, azulForte, apagado, apagado},
        {apagado, azulForte, azulForte,apagado, apagado},
        {apagado, apagado, azulForte,apagado, apagado},
        {apagado, apagado, azulForte,apagado, apagado},
        {azulForte, azulForte, azulForte, azulForte,azulForte}},
        {{apagado, apagado, azulForte, apagado, apagado},
        {apagado, azulForte, azulForte,apagado, apagado},
        {apagado, apagado, azulForte,apagado, apagado},
        {apagado, apagado, azulForte,apagado, apagado},
        {azulClaro, azulForte, azulForte, azulForte,azulForte}},
        {{apagado, apagado, azulForte, apagado, apagado},
        {apagado, azulClaro, azulForte,apagado, apagado},
        {apagado, apagado, azulForte,apagado, apagado},
        {apagado, apagado, azulForte,apagado, apagado},
        {azulClaro, azulClaro, azulForte, azulForte,azulForte}},
        {{apagado, apagado, azulClaro, apagado, apagado},
        {apagado, azulClaro, azulClaro,apagado, apagado},
        {apagado, apagado, azulClaro,apagado, apagado},
        {apagado, apagado, azulClaro,apagado, apagado},
        {azulClaro, azulClaro, azulClaro, azulForte,azulForte}},
        {{apagado, apagado, azulClaro, apagado, apagado},
        {apagado, azulClaro, azulClaro,apagado, apagado},
        {apagado, apagado, azulClaro,apagado, apagado},
        {apagado, apagado, azulClaro,apagado, apagado},
        {azulClaro, azulClaro, azulClaro, azulClaro,azulForte}},
        {{apagado, apagado, azulClaro, apagado, apagado},
        {apagado, azulClaro, azulClaro,apagado, apagado},
        {apagado, apagado, azulClaro,apagado, apagado},
        {apagado, apagado, azulClaro,apagado, apagado},
        {azulClaro, azulClaro, azulClaro, azulClaro,azulClaro}}
    };
    //Matriz que mostrará o dois com transição de tonalidade da direita para a esquerda
    Matriz_leds dois[] ={
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaClaro},
        {apagado, apagado, magentaClaro,magentaClaro, apagado},
        {apagado, magentaClaro, apagado,apagado, apagado},
        {magentaClaro, magentaClaro, magentaClaro, magentaClaro,magentaClaro}},
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaForte},
        {apagado, apagado, magentaClaro,magentaClaro, apagado},
        {apagado, magentaClaro, apagado,apagado, apagado},
        {magentaClaro, magentaClaro, magentaClaro, magentaClaro,magentaForte}},
        {{apagado, magentaClaro, magentaClaro, magentaForte, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaForte},
        {apagado, apagado, magentaClaro,magentaForte, apagado},
        {apagado, magentaClaro, apagado,apagado, apagado},
        {magentaClaro, magentaClaro, magentaClaro, magentaForte,magentaForte}},
        {{apagado, magentaClaro, magentaForte, magentaForte, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaForte},
        {apagado, apagado, magentaForte,magentaForte, apagado},
        {apagado, magentaClaro, apagado,apagado, apagado},
        {magentaClaro, magentaClaro, magentaForte, magentaForte,magentaForte}},
        {{apagado, magentaForte, magentaForte, magentaForte, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaForte},
        {apagado, apagado, magentaForte,magentaForte, apagado},
        {apagado, magentaForte, apagado,apagado, apagado},
        {magentaClaro, magentaForte, magentaForte, magentaForte,magentaForte}},
        {{apagado, magentaForte, magentaForte, magentaForte, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, apagado, magentaForte,magentaForte, apagado},
        {apagado, magentaForte, apagado,apagado, apagado},
        {magentaForte, magentaForte, magentaForte, magentaForte,magentaForte}}
        
    };
    //Matriz que mostrará o três com transição de tonalidade da direita para a esquerda
    Matriz_leds tres []={
        {{apagado, azulClaro, azulClaro, azulClaro, apagado},
        {azulClaro, apagado, apagado,apagado, azulClaro},
        {apagado, apagado, azulClaro,azulClaro, apagado},
        {azulClaro, apagado, apagado,apagado, azulClaro},
        {apagado, azulClaro, azulClaro, azulClaro,apagado}},
        {{apagado, azulClaro, azulClaro, azulClaro, apagado},
        {azulClaro, apagado, apagado,apagado, azulForte},
        {apagado, apagado, azulClaro,azulClaro, apagado},
        {azulClaro, apagado, apagado,apagado, azulForte},
        {apagado, azulClaro, azulClaro, azulClaro,apagado}},
        {{apagado, azulClaro, azulClaro, azulForte, apagado},
        {azulClaro, apagado, apagado,apagado, azulForte},
        {apagado, apagado, azulClaro,azulForte, apagado},
        {azulClaro, apagado, apagado,apagado, azulForte},
        {apagado, azulClaro, azulClaro, azulForte,apagado}},
        {{apagado, azulClaro, azulForte, azulForte, apagado},
        {azulClaro, apagado, apagado,apagado, azulForte},
        {apagado, apagado, azulForte,azulForte, apagado},
        {azulClaro, apagado, apagado,apagado, azulForte},
        {apagado, azulClaro, azulForte, azulForte,apagado}},
        {{apagado, azulForte, azulForte, azulForte, apagado},
        {azulClaro, apagado, apagado,apagado, azulForte},
        {apagado, apagado, azulForte,azulForte, apagado},
        {azulClaro, apagado, apagado,apagado, azulForte},
        {apagado, azulForte, azulForte, azulForte,apagado}},
        {{apagado, azulForte, azulForte, azulForte, apagado},
        {azulForte, apagado, apagado,apagado, azulForte},
        {apagado, apagado, azulForte,azulForte, apagado},
        {azulForte, apagado, apagado,apagado, azulForte},
        {apagado, azulForte, azulForte, azulForte,apagado}}
       
    };
    //Matriz que mostrará o quatro com transição de tonalidade de cima para baixo
    Matriz_leds quatro [] ={
        {{apagado, apagado, apagado, marromForte, apagado},
        {apagado, apagado, marromForte,marromForte, apagado},
        {apagado, marromForte, apagado,marromForte, apagado},
        {marromForte, marromForte, marromForte,marromForte, marromForte},
        {apagado, apagado, apagado, marromForte, apagado}},
        {{apagado, apagado, apagado, marromClaro, apagado},
        {apagado, apagado, marromForte,marromForte, apagado},
        {apagado, marromForte, apagado,marromForte, apagado},
        {marromForte, marromForte, marromForte,marromForte, marromForte},
        {apagado, apagado, apagado, marromForte, apagado}},
        {{apagado, apagado, apagado, marromClaro, apagado},
        {apagado, apagado, marromClaro,marromClaro, apagado},
        {apagado, marromForte, apagado,marromForte, apagado},
        {marromForte, marromForte, marromForte,marromForte, marromForte},
        {apagado, apagado, apagado, marromForte, apagado}},
        {{apagado, apagado, apagado, marromClaro, apagado},
        {apagado, apagado, marromClaro,marromClaro, apagado},
        {apagado, marromClaro, apagado,marromClaro, apagado},
        {marromForte, marromForte, marromForte,marromForte, marromForte},
        {apagado, apagado, apagado, marromForte, apagado}},
        {{apagado, apagado, apagado, marromClaro, apagado},
        {apagado, apagado, marromClaro,marromClaro, apagado},
        {apagado, marromClaro, apagado,marromClaro, apagado},
        {marromClaro, marromClaro, marromClaro,marromClaro, marromClaro},
        {apagado, apagado, apagado, marromForte, apagado}},
        {{apagado, apagado, apagado, marromClaro, apagado},
        {apagado, apagado, marromClaro,marromClaro, apagado},
        {apagado, marromClaro, apagado,marromClaro, apagado},
        {marromClaro, marromClaro, marromClaro,marromClaro, marromClaro},
        {apagado, apagado, apagado, marromClaro, apagado}},
        
    };
    //Matriz que mostrará o cinco com transição de tonalidade de baixo para cima
    Matriz_leds cinco[] ={
        {{azulForte, azulForte, azulForte, azulForte, apagado},
        {azulForte, apagado, apagado,apagado, apagado},
        {azulForte, azulForte, azulForte,azulForte, apagado},
        {apagado, apagado, apagado,apagado, azulForte},
        {azulForte, azulForte, azulForte, azulForte, apagado}},
        {{azulForte, azulForte, azulForte, azulForte, apagado},
        {azulForte, apagado, apagado,apagado, apagado},
        {azulForte, azulForte, azulForte,azulForte, apagado},
        {apagado, apagado, apagado,apagado, azulForte},
        {azulClaro, azulClaro, azulClaro, azulClaro, apagado}},
        {{azulForte, azulForte, azulForte, azulForte, apagado},
        {azulForte, apagado, apagado,apagado, apagado},
        {azulForte, azulForte, azulForte,azulForte, apagado},
        {apagado, apagado, apagado,apagado, azulClaro},
        {azulClaro, azulClaro, azulClaro, azulClaro, apagado}},
        {{azulForte, azulForte, azulForte, azulForte, apagado},
        {azulForte, apagado, apagado,apagado, apagado},
        {azulClaro, azulClaro, azulClaro,azulClaro, apagado},
        {apagado, apagado, apagado,apagado, azulClaro},
        {azulClaro, azulClaro, azulClaro, azulClaro, apagado}},
        {{azulForte, azulForte, azulForte, azulForte, apagado},
        {azulClaro, apagado, apagado,apagado, apagado},
        {azulClaro, azulClaro, azulClaro,azulClaro, apagado},
        {apagado, apagado, apagado,apagado, azulClaro},
        {azulClaro, azulClaro, azulClaro, azulClaro, apagado}},
        {{azulClaro, azulClaro, azulClaro, azulClaro, apagado},
        {azulClaro, apagado, apagado,apagado, apagado},
        {azulClaro, azulClaro, azulClaro,azulClaro, apagado},
        {apagado, apagado, apagado,apagado, azulClaro},
        {azulClaro, azulClaro, azulClaro, azulClaro, apagado}},
        

    };
    //Matriz que mostrará o seis com transição de tonalidade de cima para baixo
    Matriz_leds seis [] ={
        {{apagado, magentaForte, magentaForte, magentaForte, apagado},
        {magentaForte, apagado, apagado,apagado, apagado},
        {magentaForte, magentaForte, magentaForte,magentaForte, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, magentaForte, magentaForte, magentaForte,apagado}},
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaForte, apagado, apagado,apagado, apagado},
        {magentaForte, magentaForte, magentaForte,magentaForte, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, magentaForte, magentaForte, magentaForte,apagado}},
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, apagado},
        {magentaForte, magentaForte, magentaForte,magentaForte, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, magentaForte, magentaForte, magentaForte,apagado}},
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, apagado},
        {magentaClaro, magentaClaro, magentaClaro,magentaClaro, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, magentaForte, magentaForte, magentaForte,apagado}},
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, apagado},
        {magentaClaro, magentaClaro, magentaClaro,magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaClaro},
        {apagado, magentaForte, magentaForte, magentaForte,apagado}},
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, apagado},
        {magentaClaro, magentaClaro, magentaClaro,magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaClaro},
        {apagado, magentaClaro, magentaClaro, magentaClaro,apagado}}
    };
    //Matriz que mostrará o sete com transição de tonalidade de cima para baixo
    Matriz_leds sete [] ={
        {{verdeClaro, verdeClaro, verdeClaro, verdeClaro, verdeClaro},
        {apagado, apagado, apagado,apagado, verdeClaro},
        {apagado, apagado, apagado,verdeClaro, apagado},
        {apagado, apagado, verdeClaro,apagado, apagado},
        {apagado, apagado, verdeClaro, apagado,apagado}},
        {{verdeForte, verdeForte, verdeForte, verdeForte, verdeForte},
        {apagado, apagado, apagado,apagado, verdeClaro},
        {apagado, apagado, apagado,verdeClaro, apagado},
        {apagado, apagado, verdeClaro,apagado, apagado},
        {apagado, apagado, verdeClaro, apagado,apagado}},
        {{verdeForte, verdeForte, verdeForte, verdeForte, verdeForte},
        {apagado, apagado, apagado,apagado, verdeForte},
        {apagado, apagado, apagado,verdeClaro, apagado},
        {apagado, apagado, verdeClaro,apagado, apagado},
        {apagado, apagado, verdeClaro, apagado,apagado}},
        {{verdeForte, verdeForte, verdeForte, verdeForte, verdeForte},
        {apagado, apagado, apagado,apagado, verdeForte},
        {apagado, apagado, apagado,verdeForte, apagado},
        {apagado, apagado, verdeClaro,apagado, apagado},
        {apagado, apagado, verdeClaro, apagado,apagado}},
        {{verdeForte, verdeForte, verdeForte, verdeForte, verdeForte},
        {apagado, apagado, apagado,apagado, verdeForte},
        {apagado, apagado, apagado,verdeForte, apagado},
        {apagado, apagado, verdeForte,apagado, apagado},
        {apagado, apagado, verdeClaro, apagado,apagado}},
        {{verdeForte, verdeForte, verdeForte, verdeForte, verdeForte},
        {apagado, apagado, apagado,apagado, verdeForte},
        {apagado, apagado, apagado,verdeForte, apagado},
        {apagado, apagado, verdeForte,apagado, apagado},
        {apagado, apagado, verdeForte, apagado,apagado}}

    };
    //Matriz que mostrará o oito com transição de tonalidade de baixo para cima
    Matriz_leds oito [] ={
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaClaro},
        {apagado, magentaClaro, magentaClaro,magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaClaro},
        {apagado, magentaClaro, magentaClaro, magentaClaro, apagado}},
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaClaro},
        {apagado, magentaClaro, magentaClaro,magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaClaro},
        {apagado, magentaForte, magentaForte, magentaForte, apagado}},
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaClaro},
        {apagado, magentaClaro, magentaClaro,magentaClaro, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, magentaForte, magentaForte, magentaForte, apagado}},
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaClaro, apagado, apagado,apagado, magentaClaro},
        {apagado, magentaForte, magentaForte,magentaForte, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, magentaForte, magentaForte, magentaForte, apagado}},
        {{apagado, magentaClaro, magentaClaro, magentaClaro, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, magentaForte, magentaForte,magentaForte, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, magentaForte, magentaForte, magentaForte, apagado}},
        {{apagado, magentaForte, magentaForte, magentaForte, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, magentaForte, magentaForte,magentaForte, apagado},
        {magentaForte, apagado, apagado,apagado, magentaForte},
        {apagado, magentaForte, magentaForte, magentaForte, apagado}}
        
    };
    //Matriz que mostrará o nove com transição de tonalidade de cima para baixo
    Matriz_leds nove [] ={
        {{apagado, marromClaro, marromClaro, marromClaro, apagado},
        {marromClaro, apagado, apagado,apagado, marromClaro},
        {apagado, marromClaro, marromClaro,marromClaro, marromClaro},
        {apagado, apagado, apagado,apagado, marromClaro},
        {apagado, marromClaro, marromClaro, marromClaro, apagado}},
       {{apagado, marromForte, marromForte, marromForte, apagado},
        {marromClaro, apagado, apagado,apagado, marromClaro},
        {apagado, marromClaro, marromClaro,marromClaro, marromClaro},
        {apagado, apagado, apagado,apagado, marromClaro},
        {apagado, marromClaro, marromClaro, marromClaro, apagado}},
        {{apagado, marromForte, marromForte, marromForte, apagado},
        {marromForte, apagado, apagado,apagado, marromForte},
        {apagado, marromClaro, marromClaro,marromClaro, marromClaro},
        {apagado, apagado, apagado,apagado, marromClaro},
        {apagado, marromClaro, marromClaro, marromClaro, apagado}},
        {{apagado, marromForte, marromForte, marromForte, apagado},
        {marromForte, apagado, apagado,apagado, marromForte},
        {apagado, marromForte, marromForte,marromForte, marromForte},
        {apagado, apagado, apagado,apagado, marromClaro},
        {apagado, marromClaro, marromClaro, marromClaro, apagado}},
        {{apagado, marromForte, marromForte, marromForte, apagado},
        {marromForte, apagado, apagado,apagado, marromForte},
        {apagado, marromForte, marromForte,marromForte, marromForte},
        {apagado, apagado, apagado,apagado, marromForte},
        {apagado, marromClaro, marromClaro, marromClaro, apagado}},
        {{apagado, marromForte, marromForte, marromForte, apagado},
        {marromForte, apagado, apagado,apagado, marromForte},
        {apagado, marromForte, marromForte,marromForte, marromForte},
        {apagado, apagado, apagado,apagado, marromForte},
        {apagado, marromForte, marromForte, marromForte, apagado}}
    };

    //Laço de repetição para mostrar todos os frames na matriz de Leds
    for(int i=0; i<6; i++){
        switch(acumulador){
            case 0:
                    acender_leds(zero[i]);
                break;
            case 1:
                    acender_leds(um[i]);
                break;
            case 2:
                    acender_leds(dois[i]);
                break;
            case 3:
                    acender_leds(tres[i]);
                break;
            case 4:
                    acender_leds(quatro[i]);
                break;
            case 5:
                    acender_leds(cinco[i]);
                    break;
            case 6:
                    acender_leds(seis[i]);
                    break;
            case 7:
                    acender_leds(sete[i]);
                    break;
            case 8:
                    acender_leds(oito[i]);
                    break;
            case 9: 
                    acender_leds(nove[i]);
                    break;
            default:
                break;
            }; 
        piscar_ledR();      //Chamando a função piscar_ledR() que fará o led Vermelho piscar
    };

};


// Prototipo da função de interrupção
static void interrupcao_Botao(uint gpio, uint32_t events);


int main()
{
    int valor_anterior;
    uint offset = pio_add_program(pio, &pio_matrix_program);

    stdio_init_all();
    config_pinos();

    pio_matrix_program_init(pio, sm, offset, MatrizLeds, 800000, IS_RGBW);

    //Leds Verde e Azul inicialmente apagados
    gpio_put(LedG,0);
    gpio_put(LedB,0);

    // Configuração da interrupção com callback
    gpio_set_irq_enabled_with_callback(ButtonA, GPIO_IRQ_EDGE_FALL, true, &interrupcao_Botao);
    gpio_set_irq_enabled_with_callback(ButtonB, GPIO_IRQ_EDGE_FALL, true, &interrupcao_Botao);

    while (true) {
        numeros();              //A variável acumulador utilizada dentro da função atualiza a cada interrupção
        valor_anterior=acumulador;      //Passo para poder verificar se algum Led além do vermelho foi aceso
        if(valor_anterior==acumulador){
            gpio_put(LedB,0);           //Permite apagar os leds Verde e Azul logo após a rotina de interrupção
            gpio_put(LedG,0);
        }
    };
};


// Função de interrupção com debouncing

/*
    Ao pressionar o Botão A o led Azul acende e a variável global 'acumulador' incrementa. 
    Já ao pressionar o botão B, o led Verde acende e a variável global 'acumulador' decrementa. 
    Quando azul/verde acende e fica acesso apenas durante a mudança de número.
    Quando a contagem passa de nove, o acumulador volta para 0, e vice-versa.
*/

void interrupcao_Botao (uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t tempo_atual = to_us_since_boot(get_absolute_time());
    
    if (tempo_atual - tempo_anterior > 300000) // 200 ms de debouncing
    {
        tempo_anterior = tempo_atual; // Atualiza o tempo do último evento
        if(gpio==ButtonA){              //Verifica qual botão foi pressionado
            printf("Botão A pressionado!\n");       //Nesse caso botão A
            if(acumulador == 9)         //Permite que o contador volte para 0 depois do 9
                acumulador = 0;
            else
                acumulador++;           //Incrementa
            gpio_put(LedB, 0.001);
        }else{
            printf("Botão B pressionado!\n");       //Nesse caso botão B
            if(acumulador == 0)         //Permite que o contador volte para 9 depois do 0
                acumulador = 9;
            else
                acumulador--;           //Decrementa
            gpio_put(LedG, 0.001);
        }
        printf("Número exibido na Matriz de Leds: %d\n", acumulador);
    }
}