//Embarcatec 
//Tarefa 1 - Aula Sincrona - 29/01/2025
//Discente: Alexsami


#include <stdio.h>
#include "pico/stdlib.h"   // Inclui a biblioteca padrão para funcionalidades básicas como GPIO, temporização e comunicação serial.
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.

#define LED_PIN_RED 11
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 13

int count = 0;  // Controla o estado do semáforo

// Callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    printf("3 segundos se passaram\n");

    // Definir qual LED deve ser desligado
    int previous_led;
    if (count == 0) {
        previous_led = LED_PIN_GREEN;  // O último LED é o verde, então ele deve ser desligado ao voltar para o vermelho
    } else {
        previous_led = LED_PIN_RED + (count - 1);  // O LED anterior
    }

    gpio_put(previous_led, false);  // Desliga o LED anterior
    gpio_put(LED_PIN_RED + count, true);  // Liga o LED atual

    count++;  // Avança para o próximo estado
    if (count == 3) {
        count = 0;  // Volta para o primeiro LED (vermelho)
    }

    return true;  // Mantém o timer ativo
}

int main() {
    // Inicializa a comunicação serial, permitindo o uso de funções como printf.
    stdio_init_all();

    // Inicializar o pino GPIO11
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED,true);
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW,true);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN,true);
    // Declaração de uma estrutura de temporizador de repetição.
    // Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 1 segundo.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito que mantém o programa em execução.
    while (true) {
        // Pausa de 1 segundo para reduzir o uso da CPU.
        sleep_ms(1000);
        printf("rotina de repetição de 1 segundo\n");
    }
    return 0;
}
