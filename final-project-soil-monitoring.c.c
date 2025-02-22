#include <stdio.h>            
#include "pico/stdlib.h"
#include <inc/config_btn.h>
#include <inc/joystick.h>
#include <inc/display_ssd1306.h>

// Definição dos pinos dos LEDs PWM
#define LED_PIN_RED 13  
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11

void setup_gpio_leds(){
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
}

int main() {
    stdio_init_all();    // Inicializa entradas e saídas.
    joystick_init();    //Inicializa os pinos do joystick
    setup_gpio_leds(); //Inicializa os leds
    display_init();   //Inicializa o display

    setup_gpio_BTN_A();//Configuração inicial do botão A
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);//Interrupção callback para botão A
    
    while (true) {
        
        if(!parameters_ok){
            initial_print_display();
        }else{
            if (!umid_ok && !temp_ok && !cond_ok){
                printf("Umidade: %.2f\nTemperatura: %.2f\nCondutividade: %.2f\n\n", umidade, temperatura, condutividade);
            }else{
                adc_select_input(1);  // Seleciona o pino do joystick X
                vrx_value = adc_read();  // Lê o valor do joystick (0 a 4095)

                if (umid_ok) {
                    umidade = map_umidade(vrx_value);
                    printf("Umidade: %.2f\n", umidade);
                    print_display("Umidade;", umidade);
                }
                else if (temp_ok) {
                    temperatura = map_temperatura(vrx_value);
                    printf("Temperatura: %.2f\n", temperatura);
                    print_display("Temperatura", temperatura);
                }
                else if (cond_ok) {
                    condutividade = map_condutividade(vrx_value);
                    printf("Condutividade: %.2f\n", condutividade);
                    print_display("Condutividade", condutividade);
                }
            }
        }
        sleep_ms(500);
    }
    
    return 0;
}