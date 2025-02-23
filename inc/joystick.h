#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "hardware/adc.h"   

// Definição dos pinos dos potenciômetros do joystick
#define VRX_PIN 27   // Pino de entrada analógica para eixo X do joystick

uint16_t vrx_value;

void joystick_init() {
    adc_init();              // Inicializa o ADC (conversor analógico-digital)
    adc_gpio_init(VRX_PIN); // Configura o pino do joystick como entrada analógica
}

//Função para o joystick simular a variação da umidade do solo
float map_umidade(float joystick_value) {
    return (joystick_value / 4095.0) * 100.0;  // Mapeia para 0% a 100%
}

//Função para o joystick simular a variação da temperatura do solo
float map_temperatura(float joystick_value) {
    return (joystick_value / 4095.0) * 50.0;  // Mapeia para 0°C a 50°C
}

//Função para o joystick simular a variação da condutividade elétrica do solo
float map_condutividade(float joystick_value) {
    return (joystick_value / 4095.0) * 5.0;  // Mapeia para 0 dS/m a 5 dS/m
}

#endif