#ifndef CONFIG_BTN_H
#define CONFIG_BTN_H

#include "hardware/timer.h"

//definição de GPIO botões
#define BTN_A 5
#define BTN_B 6

// Variáveis globais 
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
int parameters = 0, detail_parameters = 3;
bool umid_ok = false, temp_ok = false, cond_ok = false, parameters_ok = false, BTN_B_PRESS = false;

// Configuração inicial ds botões
void setup_gpio_BTN() {
  //Botão A
  gpio_init(BTN_A);
  gpio_set_dir(BTN_A, GPIO_IN);
  gpio_pull_up(BTN_A);

  //Botão B
  gpio_init(BTN_B);
  gpio_set_dir(BTN_B, GPIO_IN);
  gpio_pull_up(BTN_B);
}

// Função de interrupção com debouncing do botão
void gpio_irq_handler(uint gpio, uint32_t events){
  uint32_t current_time = to_us_since_boot(get_absolute_time());// Obtém o tempo atual em microssegundos
  // Verifica se passou tempo suficiente desde o último evento
  if (current_time - last_time > 300000) { // 300 ms de debouncing
    last_time = current_time; // Atualiza o tempo do último evento

    if (gpio == BTN_A) {
      BTN_B_PRESS = false;
      switch(parameters){
        case 0: //Leitura umidade
          umid_ok = true;
          parameters = 1;
          parameters_ok = false;
        break;
        case 1: //Leitura temperatura
          umid_ok = false;
          temp_ok = true;
          parameters = 2;
        break;
        case 2: //Leitura condutividade elétrica
          temp_ok = false;
          cond_ok = true;
          parameters = 3;
        break;
        case 3:
          cond_ok = false; 
          parameters_ok = true;
          parameters = 0;
        break;
      }    
    } else if (gpio == BTN_B) {
      if (parameters_ok) {
        BTN_B_PRESS = true;
        if (detail_parameters == 0) detail_parameters = 1;
        else if (detail_parameters == 1) detail_parameters = 2;
        else if (detail_parameters == 2) detail_parameters = 3;
        else if (detail_parameters == 3) detail_parameters = 0;
      }
    }
  }
}

void gpio_set_irq_interrupt_btn(){
  // Configuração da interrupção com callback para botão A
  gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
  // Configuração da interrupção com callback para botão B
  gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}

#endif