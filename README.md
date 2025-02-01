 # Tarefa 1 

__Tarefa 1 - Aula Síncrona 27/01__<br>
Repositório criado com o intuito de realizar a Tarefa 1 da aula Síncrona do dia 27 de janeiro de 2025 sobre Interrupções.

__Responsável pelo desenvolvimento:__
Andressa Sousa Fonseca

## Descrição Da Tarefa 
__Aplicação de Interrupções por software, Matriz de Leds 5x5 e Leds RGB__  <br>

__Os Componentes necessários para a execução da atividade são:__
1) Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7.
2) LED RGB, com os pinos conectados às GPIOs (11, 12 e 13).
3) Botão A conectado à GPIO 5.
4) Botão B conectado à GPIO 6.

__As funcionalidade básicas especificadas para a atividade são:__
1) O LED vermelho do LED RGB deve piscar continuamente 5 vezes por segundo..
2) O botão A deve incrementar o número exibido na matriz de LEDs cada vez que for pressionado.
3) O botão B deve decrementar o número exibido na matriz de LEDs cada vez que for pressionado.
4) Os LEDs WS2812 devem ser usados para criar efeitos visuais representando números de 0 a 9.


__Uma breve explicação do desenvolvimento e resultados obtidos podem ser vistos no vídeo endereçado no seguine link: [Aplicação de Rotinas de Interrupção]().__

## Detalhamento Do Desenvolvimento

### 1. Explicação do funcionamento

A matriz de leds 5x5 inicia com o número 0 sendo mostrado. O valor muda de acordo com o acionamento dos botões. Assim, ao pressionar o botão A, o número passa de 0 para 1, e vai incrementando se o Botão A for pressionado novamente. Em contrapartida, ao pressionar o Botão B, sendo o número exibido no momento 1, ele passará a ser 0. Ademais, ao pressionar o Botão A estando com o número em exibição 9, o valor voltará a ser 0, reiniciando a contagem. O mesmo ocorre com o Botão B, caso o valor seja 0, ele ao decrementar passará a ser 9, estabelecendo-se, assim, um ciclo entre os números. 
A utilização de dois botões permitiu implementar um tratamento de debouncing via software aliado a rotinas de interupção, detalhadas na aula. Foi utilizada a seguinte função de interrupção:
```bash
static void interrupcao_Botao(uint gpio, uint32_t events);
```
Na main, a função acima é chamada pela função de interrupção com callback a seguir:
```bash
gpio_set_irq_enabled_with_callback(ButtonA, GPIO_IRQ_EDGE_FALL, true, &interrupcao_Botao);
gpio_set_irq_enabled_with_callback(ButtonB, GPIO_IRQ_EDGE_FALL, true, &interrupcao_Botao);
```
É possível perceber que os dois botões chamam a mesma função, interrupcao_Botao(). O diferenciamento entre os botões é feito dentro da função a partie de um if, que incrementa ou decrementa de acordo com o desejado, depois de uma verificação deboucing que estabelece um tempo de 200ms para aceitar que o botão foi pressionado.

### 2. Funcionalidades adicionais
O projeto hospedado nesse repositório possui as configurações básicas exigidas, já enumeradas acima. Em composição a isso, foi adicionado um efeito visual na exibição dos números com transição entre duas tonalidades para as cinco diferentes cores utilizadas: azul, vermelho, marrom, magenta e verde (obtidos pela combinação de vermelho, verde e azul). E por último, o Botão A ao ser pressionado acende brevemente o led Azul (pino 12) e, por sua vez, o Botão B acende o led Verde (pino 11).

### 3. Formatação dos números
A formatação usada nos números pode ser previamente visualizada abaixo:

As imagens acima são do simulador Wokwi integrado, para visualizar o resultado na placa é necessário assiste ao vídeo.

Se necessário, é possível ajustar as padrões de intensidade das cores na função numeros(), modificando os valores das variáveis inten e inten2, sendo, o tom mais forte e o mais fraco, respectivamente.
