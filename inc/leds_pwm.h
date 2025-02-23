#include "hardware/pwm.h" 

// Definição dos pinos dos LEDs
#define LED_PIN_RED 13  
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11

uint pwm_slice_red;
uint pwm_slice_blue;
uint pwm_slice_green;
uint16_t intensidade_media = 2046;

//Função com todos os leds pwm desligados
void leds_off(){
    pwm_set_gpio_level(LED_PIN_RED, 0);
    pwm_set_gpio_level(LED_PIN_BLUE, 0);
    pwm_set_gpio_level(LED_PIN_GREEN, 0);
}

uint pwm_init_gpio(uint gpio, uint wrap) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice_num, wrap);
    
    pwm_set_enabled(slice_num, true);  
    return slice_num;  
}

void pwm_leds_init(){
    uint pwm_wrap = 4096;  
    pwm_slice_red = pwm_init_gpio(LED_PIN_RED, pwm_wrap);
    pwm_slice_blue = pwm_init_gpio(LED_PIN_BLUE, pwm_wrap);
    pwm_slice_green = pwm_init_gpio(LED_PIN_GREEN, pwm_wrap);  
}