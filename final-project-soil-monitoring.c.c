#include <stdio.h>            
#include "pico/stdlib.h"
#include <inc/config_btn.h>
#include <inc/joystick.h>
#include <inc/display_ssd1306.h>

int main() {
    stdio_init_all();    // Inicializa entradas e saídas.
    joystick_init();    //Inicializa os pinos do joystick
    setup_gpio_leds(); //Inicializa os leds
    display_init();   //Inicializa o display

    setup_gpio_BTN_A();//Configuração inicial do botão A
    gpio_set_irq_interrupt_btn();// Configuração da interrupção com callback para botão
    
    initial_print_display();
    while (true) {
        
        //se todos os parâmetros estiverem salvos, mostra seus respectivos valores no display
        if (parameters_ok){
            printf("Umidade: %.2f\nTemperatura: %.2f\nCondutividade: %.2f\n\n", umidade, temperatura, condutividade);
            
            //se o botão B ainda pressionado, continua mostrando os valores salvos dos parâmetros no display
            if (!BTN_B_PRESS) display_info(umidade, temperatura, condutividade); 
            else { //se o botão B for pressionado, é mostrado os detalhes relacionado a cada parâmetro com uma dica sobre o solo no display
                if (detail_parameters == 0) detail_umi(umidade);
                else if (detail_parameters == 1) detail_temp(temperatura);
                else if (detail_parameters == 2) detail_cond(condutividade);
            }
        } else { // seção para que os parâmetros sejam lidos e salvos (o joystick que simula os parâmetros do solo)
            adc_select_input(1);  // Seleciona o pino do joystick X
            vrx_value = adc_read();  // Lê o valor do joystick (0 a 4095)

            if (umid_ok) {
                umidade = map_umidade(vrx_value);
                printf("Umidade: %.2f\n", umidade);
                print_display("UMIDADE;", umidade);
            
            } else if (temp_ok) {
                temperatura = map_temperatura(vrx_value);
                printf("Temperatura: %.2f\n", temperatura);
                print_display("TEMPERATURA", temperatura);
            
            } else if (cond_ok) {
                condutividade = map_condutividade(vrx_value);
                printf("Condutividade: %.2f\n", condutividade);
                print_display("CONDUTIVIDADE", condutividade);
            }
        }
        sleep_ms(500);
    }
    return 0;
}