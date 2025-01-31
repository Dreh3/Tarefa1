//Código desenvolvido por Andressa Sousa Fonseca

//Incluindo bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

//Arquivo .pio
#include "pio_matrix.pio.h"

#define IS_RGBW false

//Definindo pinos
#define ButtonA 5       //Pino do botão A
#define ButtonB 6       //Pino do botão B
#define MatrizLeds 7    //Pino da Matriz de Leds 5x5
#define LedR 11         //Pino do Led Vermelho
#define LedG 12         //Pino do Led Verde
#define LedB 13         //Pino do Led Azul

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
  R = r * 255; //devo multiplicar?
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

//Função responsável por acender os leds desejados 
void acender_leds(Matriz_leds matriz, PIO pio, uint sm){
    //Primeiro for para percorrer cada linha
    for (int linha =0; linha<5;linha ++){
        /*
        Devido à ordem de disposição dos leds na matriz de leds 5X5, é necessário
        ter o cuidado para imprimir o desenho na orientação correta. Assim, o if abaixo permite o 
        desenho saia extamente como projetado.
        */

        if(linha%2==0){                             //Se verdadeiro, a numeração das colunas começa em 4 e decrementam
            for(int coluna=4;coluna>=0;coluna--){
                uint32_t cor = cor_binario(matriz[linha][coluna].red,matriz[linha][coluna].green,matriz[linha][coluna].blue);
                pio_sm_put_blocking(pio, sm, cor);
            };
        }else{                                      //Se falso, a numeração das colunas começa em 0 e incrementam
            for(int coluna=0;coluna<5;coluna++){
                uint32_t cor = cor_binario(matriz[linha][coluna].red,matriz[linha][coluna].green,matriz[linha][coluna].blue);
                pio_sm_put_blocking(pio, sm, cor);
            }
        }
    }
}

void numeros(PIO pio, uint sm){
    //Definindo cores
    COR_RGB apagado = {0.0,0.0,0.0};
    COR_RGB vermelho = {1.0,0.0,0.0};

    Matriz_leds zero ={
        {apagado, apagado, vermelho, vermelho},
        {apagado, apagado, vermelho, apagado},
        {apagado, apagado, vermelho, vermelho},
        {apagado, apagado, vermelho, vermelho},
        {apagado, apagado, vermelho, vermelho},
    };

    Matriz_leds um ={
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
    };

    Matriz_leds dois ={
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
    };

    Matriz_leds tres ={
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
    };

    Matriz_leds quatro ={
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
    };

    Matriz_leds cinco ={
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
    };

    Matriz_leds seis ={
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
    };

    Matriz_leds sete ={
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
    };

    Matriz_leds oito ={
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
    };

    Matriz_leds nove ={
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
        {apagado, apagado, apagado, apagado},
    };

}

void piscar_ledR(){
    for(int i =0;i<6;i++){
        gpio_put(LedR, 1);
        sleep_ms(100);
        gpio_put(LedR, 0);
        sleep_ms(100);
    }
};

int main()
{
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &pio_matrix_program);

    stdio_init_all();
    config_pinos();

    pio_matrix_program_init(pio, sm, offset, MatrizLeds, 800000, IS_RGBW);

    while (true) {
        piscar_ledR();
    }
}
