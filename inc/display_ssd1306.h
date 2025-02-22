#ifndef DISPLAY_SSD1306_H
#define DISPLAY_SSD1306_H

#include "hardware/i2c.h"
#include "ssd1306/ssd1306.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

bool cor = true;    // Define a cor do display (preto/branco)

ssd1306_t ssd;    // Inicializa a estrutura do display

void display_init(){
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
    
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); //Inicializa o display
    ssd1306_config(&ssd); //Configura o display
    ssd1306_send_data(&ssd); //Envia os dados para o display

    //O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

void print_display(const char* message, float parametro) {
    char parametro_solo[10];  // Buffer para armazenar a string formatada
    snprintf(parametro_solo, sizeof(parametro_solo), "%.2f", parametro);  // Converte float para string com 2 casas decimais

    ssd1306_fill(&ssd, !cor);  // Limpa o display
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 0);  // Desenha uma string
    ssd1306_draw_string(&ssd, message, 0, 20);  // Exibe a mensagem
    ssd1306_draw_string(&ssd, parametro_solo, 40, 40);  // Exibe o valor do parâmetro
    ssd1306_send_data(&ssd);  // Atualiza o display
}

void initial_print_display(){
    ssd1306_fill(&ssd, !cor);  // Limpa o display
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 0);  // Desenha uma string
    ssd1306_draw_string(&ssd, "BOTÃO A", 0, 20);  // Exibe a mensagem
    ssd1306_draw_string(&ssd, "PARA INICIAR", 0, 40);  // Exibe o valor do parâmetro
    ssd1306_send_data(&ssd);  // Atualiza o display
}


#endif