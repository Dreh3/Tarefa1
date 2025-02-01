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

###1. Configurações adicionais
 O projeto hospedado nesse repositório possui as configurações básicas exigidas, já enumeradas acima. Em composição a isso, foi adicionado um efeito visual na exibição dos números com transição entre duas tonalidades para cinco diferntes cores utilizadas: azul, vermelho, marrom, magenta e verde (obtidos pela combinação de vermelho, verde e azul).

###2. Explicação do funcionamento
A utilização de dois botões permitiu implementar um tratamento de debouncing via software aliado a rotinas de interupção, detalhadas na aula.
A matriz de leds 5x5 inicia com o número 0 sendo mostrado. O valor muda de acordo com o acionamento dos botões. Assim, ao pressionar o botão A
