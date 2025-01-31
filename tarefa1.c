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
  R = r * 255; //devo multiplicar?
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
                uint32_t cor = cor_binario(matriz[linha][coluna].red,matriz[linha][coluna].green,matriz[linha][coluna].blue);
                pio_sm_put_blocking(pio, sm, cor);
            };
        }else{                                      //Se falso, a numeração das colunas começa em 0 e incrementam
            for(int coluna=4;coluna>=0;coluna--){
                uint32_t cor = cor_binario(matriz[linha][coluna].red,matriz[linha][coluna].green,matriz[linha][coluna].blue);
                pio_sm_put_blocking(pio, sm, cor);
            }
        }
    }
}

//Função que será chamada na interrupção para mostrar números na matriz de leds
void numeros(int i){

    //Definindo cores
    COR_RGB apagado = {0.0,0.0,0.0};
    COR_RGB vermelhoForte = {0.5,0.0,0.0};
    COR_RGB vermelhoClaro = {0.2,0.0,0.0};

    //Serão estabelecidos 3 frames para cada um dos Leds

    Matriz_leds zero [] =
    {
        {{apagado, vermelhoClaro, vermelhoForte, vermelhoClaro, apagado},
        {vermelhoForte, apagado, apagado,apagado, vermelhoForte},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoClaro},
        {vermelhoForte, apagado, apagado,apagado, vermelhoForte},
        {apagado, vermelhoClaro, vermelhoForte, vermelhoClaro,apagado}},
        {{apagado, vermelhoForte, vermelhoClaro, vermelhoForte, apagado},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoClaro},
        {vermelhoForte, apagado, apagado,apagado, vermelhoForte},
        {vermelhoClaro, apagado, apagado,apagado, vermelhoClaro},
        {apagado, vermelhoForte, vermelhoClaro, vermelhoForte,apagado}}
    }
    ;

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

    switch(acumulador){
        case 0:
            for(int i =0; i<2;i++){
                acender_leds(zero[i]);
                gpio_put(LedR,0.5);
                sleep_ms(100);
                gpio_put(LedR,0);
                sleep_ms(100);
            };
            break;
        default:
            gpio_put(LedR,0.5);
            sleep_ms(100);
            gpio_put(LedR,0);
            sleep_ms(100);
            break;
    }; 

};

void piscar_ledR(){
    for(int i =0;i<6;i++){
        gpio_put(LedR, 1);
        sleep_ms(100);
        gpio_put(LedR, 0);
        sleep_ms(100);
    }
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

    gpio_put(LedG,0);
    gpio_put(LedB,0);
    // Configuração da interrupção com callback
    gpio_set_irq_enabled_with_callback(ButtonA, GPIO_IRQ_EDGE_FALL, true, &interrupcao_Botao);
    gpio_set_irq_enabled_with_callback(ButtonB, GPIO_IRQ_EDGE_FALL, true, &interrupcao_Botao);

    while (true) {

        //piscar_ledR();        //Chamando função para piscar Led Vermelho em loop
        numeros(acumulador); //A variável acumulador passa para a chamada da função o número atualizado
        valor_anterior=acumulador;
        if(valor_anterior==acumulador){
            gpio_put(LedB,0);
            gpio_put(LedG,0);
        }
    };
};


// Função de interrupção com debouncing

/*
    Ao pressionar o Botão A o led Azul acende e a variável global 'acumulador' incrementa. 
    Já ao pressionar o botão B, o led Verde acende e a variável global 'acumulador' decrementa. 
    Quando azul/verde acende ficam acesso apenas durante a mudança de número.
    Quando a contagem passa de nove, o acumulador volta para 0.
    E não decrementa para números negativos
*/

void interrupcao_Botao (uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t tempo_atual = to_us_since_boot(get_absolute_time());
    
    if (tempo_atual - tempo_anterior > 300000) // 200 ms de debouncing
    {
        tempo_anterior = tempo_atual; // Atualiza o tempo do último evento
        if(gpio==ButtonA){
            printf("Botão A pressionado!\n");
            if(acumulador == 9)
                acumulador = 0;
            else
                acumulador++;
            gpio_put(LedB, 0.001);
        }else{
            printf("Botão B pressionado!\n");
            acumulador--;
            gpio_put(LedG, 0.001);
        }
        printf("Número exibido na Matriz de Leds: %d\n", acumulador);
    }
}