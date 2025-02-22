#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "hardware/adc.h" 

uint16_t vrx_value;  

// Definição dos pinos dos potenciômetros do joystick
#define VRX_PIN 27   // Pino de entrada analógica para eixo X do joystick


void joystick_init() {
    adc_init();          // Inicializa o ADC (conversor analógico-digital)
    // Configura os pinos do joystick como entradas analógicas
    adc_gpio_init(VRX_PIN);
}


float map_umidade(float joystick_value) {
    return (joystick_value / 4095.0) * 100.0;  // Mapeia para 0% a 100%
}

float map_temperatura(float joystick_value) {
    return (joystick_value / 4095.0) * 50.0;  // Mapeia para 0°C a 50°C
}

float map_condutividade(float joystick_value) {
    return (joystick_value / 4095.0) * 5.0;  // Mapeia para 0 dS/m a 5 dS/m
}

#endif