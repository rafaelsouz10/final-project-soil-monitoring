#ifndef CONFIG_BTN_H
#define CONFIG_BTN_H

#include "hardware/timer.h"

//definição de GPIO botões
#define BTN_A 5

// Variáveis globais 
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
static int parameters = 0;
float umidade = 0.0, temperatura = 0.0, condutividade = 0.0;
bool umid_ok = false, temp_ok = false, cond_ok = false, parameters_ok = false;

// Configuração inicial ds botões
void setup_gpio_BTN_A() {
  //Botão A
  gpio_init(BTN_A);
  gpio_set_dir(BTN_A, GPIO_IN);
  gpio_pull_up(BTN_A);
}

// Função de interrupção com debouncing do botão
void gpio_irq_handler(uint gpio, uint32_t events){
  uint32_t current_time = to_us_since_boot(get_absolute_time());// Obtém o tempo atual em microssegundos
  // Verifica se passou tempo suficiente desde o último evento
  if (current_time - last_time > 200000) { // 200 ms de debouncing
    last_time = current_time; // Atualiza o tempo do último evento

    switch(parameters){
      case 0:
        printf("Leitura Umidade Iniciada.\n");
        umid_ok = true;
        parameters = 1;
        parameters_ok = false;
      break;
      case 1:
        printf("Leitura Temperatura Iniciada.\n");
        umid_ok = false;
        temp_ok = true;
        parameters = 2;
      break;
      case 2:
        printf("Leitura Condutividade Elétrica Iniciada.\n");
        temp_ok = false;
        cond_ok = true;
        parameters = 3;
      break;
      case 3:
        printf("Leituras Finalizadas.\n");
        temp_ok = false;
        cond_ok = false;
        temp_ok = false;
        parameters_ok = true;
        parameters = 0;
        
      break;
    }
  }
}

#endif