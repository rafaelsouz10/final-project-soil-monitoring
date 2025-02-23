#ifndef DISPLAY_SSD1306_H
#define DISPLAY_SSD1306_H

#include "hardware/i2c.h"
#include "ssd1306/ssd1306.h"

// Definição dos pinos dos LEDs
#define LED_PIN_RED 13  
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11

// Função para inicias os LEDs
void setup_gpio_leds(){
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
}

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

bool cor = true;    // Define a cor do display (preto/branco)

ssd1306_t ssd;    // Inicializa a estrutura do display

float umidade = 0.0, temperatura = 0.0, condutividade = 0.0;

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

// Função para exbir as informações iniciais no display
void initial_print_display(){
    ssd1306_fill(&ssd, !cor);  // Limpa o display
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 10);  // Desenha uma string
    ssd1306_draw_string(&ssd, "READ SOIL", 28, 25);  // Exibe a mensagem
    ssd1306_draw_string(&ssd, "PARAMETER", 28, 40);
    ssd1306_send_data(&ssd);  // Atualiza o display
    sleep_ms(3000);

    ssd1306_fill(&ssd, !cor);  // Limpa o display
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 0);  // Desenha uma string
    ssd1306_draw_string(&ssd, "PARA INICIAR", 16, 20);  // Exibe a mensagem
    ssd1306_draw_string(&ssd, "LEITURA", 36, 30);
    ssd1306_draw_string(&ssd, "BOTAO A", 36, 40);  
    ssd1306_send_data(&ssd);  // Atualiza o display
}

void print_display(const char* message, float parametro) {
    char parametro_solo[10];  // Buffer para armazenar a string formatada
    snprintf(parametro_solo, sizeof(parametro_solo), "%.2f", parametro);  // Converte float para string com 2 casas decimais

    ssd1306_fill(&ssd, !cor);  // Limpa o display
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 0);  // Desenha uma string
    ssd1306_draw_string(&ssd, message, 0, 30);  // Exibe a mensagem
    ssd1306_draw_string(&ssd, parametro_solo, 0, 40);  // Exibe o valor do parâmetro
    ssd1306_send_data(&ssd);  // Atualiza o display
}

// Função para exibir os parametros no display
void display_info(float umidade, float temperatura, float condutividade) {
    char buffer[20];  // Buffer para armazenar as strings formatadas

    ssd1306_fill(&ssd, 0); // Limpa o display
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 0);  // Desenha uma string

    // Formata e exibe a umidade
    snprintf(buffer, sizeof(buffer), "Umid. %.2f %%", umidade);
    ssd1306_draw_string(&ssd, buffer, 0, 20);  // Exibe na linha 1 (y = 0)

    // Formata e exibe a temperatura
    snprintf(buffer, sizeof(buffer), "Temp. %.2f C", temperatura);
    ssd1306_draw_string(&ssd, buffer, 0, 30);  // Exibe na linha 2 (y = 10)

    // Formata e exibe a condutividade
    snprintf(buffer, sizeof(buffer), "Cond. %.2f dS/m", condutividade);
    ssd1306_draw_string(&ssd, buffer, 0, 40);  // Exibe na linha 3 (y = 20)

    ssd1306_send_data(&ssd);// Atualiza o display
}

void detail_umi(float umidade){
    char buffer[20];  // Buffer para armazenar as strings formatadas

    ssd1306_fill(&ssd, 0); // Limpa o display
    ssd1306_draw_string(&ssd, "DETALHES UMID", 15, 0);  // Desenha uma string

    // Formata e exibe a umidade
    snprintf(buffer, sizeof(buffer), "Umid. %.2f %%", umidade);
    ssd1306_draw_string(&ssd, buffer, 0, 20);  // Exibe na linha 1 (y = 0)

    if (umidade < 20) {
        gpio_put(LED_PIN_BLUE, true);
        gpio_put(LED_PIN_GREEN, false);
        gpio_put(LED_PIN_RED, false);

        ssd1306_draw_string(&ssd, "Solo seco", 0, 40);
        ssd1306_draw_string(&ssd, "Irrigar", 0, 50);
    } else if (umidade >= 20 && umidade <= 60) {
        gpio_put(LED_PIN_GREEN, true);
        gpio_put(LED_PIN_BLUE, false);
        gpio_put(LED_PIN_RED, true);

        ssd1306_draw_string(&ssd, "Umidade ideal", 0, 40);
    
    } else if (umidade > 60) {
        gpio_put(LED_PIN_RED, true);
        gpio_put(LED_PIN_GREEN, false);
        gpio_put(LED_PIN_BLUE, false);

        ssd1306_draw_string(&ssd, "Solo encharcado", 0, 40);
        ssd1306_draw_string(&ssd, "Reduzir agua", 0, 50);
    }   
    ssd1306_send_data(&ssd);// Atualiza o display
}

void detail_temp(float temperatura){
    char buffer[20];  // Buffer para armazenar as strings formatadas

    ssd1306_fill(&ssd, 0); // Limpa o display
    ssd1306_draw_string(&ssd, "DETALHES TEMP", 15, 0);  // Desenha uma string

    // Formata e exibe a temperatura
    snprintf(buffer, sizeof(buffer), "Temp. %.2f C", temperatura);
    ssd1306_draw_string(&ssd, buffer, 0, 20);  // Exibe na linha 1 (y = 0)

    if (temperatura < 10) {
        gpio_put(LED_PIN_BLUE, true);
        gpio_put(LED_PIN_GREEN, false);
        gpio_put(LED_PIN_RED, false);

        ssd1306_draw_string(&ssd, "Solo frio", 0, 40);
        ssd1306_draw_string(&ssd, "Cobrir solo", 0, 50);
    } else if (temperatura >= 10 && temperatura <= 30) {
        gpio_put(LED_PIN_GREEN, true);
        gpio_put(LED_PIN_BLUE, false);
        gpio_put(LED_PIN_RED, false);

        ssd1306_draw_string(&ssd, "Temperatura", 0, 40);
        ssd1306_draw_string(&ssd, "ideal", 0, 50);
    } else if (temperatura > 30) {
        gpio_put(LED_PIN_RED, true);
        gpio_put(LED_PIN_GREEN, false);
        gpio_put(LED_PIN_BLUE, false);

        ssd1306_draw_string(&ssd, "Solo quente", 0, 40);
        ssd1306_draw_string(&ssd, "Proteger plantas", 0, 50);
    } 
    ssd1306_send_data(&ssd);// Atualiza o display
}

void detail_cond(float condutividade){
    char buffer[20];  // Buffer para armazenar as strings formatadas

    ssd1306_fill(&ssd, 0); // Limpa o display
    ssd1306_draw_string(&ssd, "DETALHES COND", 15, 0);  // Desenha uma string

    // Formata e exibe a condutividade
    snprintf(buffer, sizeof(buffer), "Cond. %.2f dS/m", condutividade);
    ssd1306_draw_string(&ssd, buffer, 0, 20);  // Exibe na linha 1 (y = 0)

    if (condutividade < 0.5) {
        gpio_put(LED_PIN_BLUE, true);
        gpio_put(LED_PIN_GREEN, false);
        gpio_put(LED_PIN_RED, false);

        ssd1306_draw_string(&ssd, "Pouco nutriente", 0, 40);
        ssd1306_draw_string(&ssd, "Adubar solo", 0, 50);
    } else if (condutividade >= 0.5 && condutividade <= 3.0) {
        gpio_put(LED_PIN_GREEN, true);
        gpio_put(LED_PIN_BLUE, false);
        gpio_put(LED_PIN_RED, false);

        ssd1306_draw_string(&ssd, "Condutividade", 0, 40);
        ssd1306_draw_string(&ssd, "ideal", 0, 50);
    } else if (condutividade > 3.0) {
        gpio_put(LED_PIN_RED, true);
        gpio_put(LED_PIN_GREEN, false);
        gpio_put(LED_PIN_BLUE, false);

        ssd1306_draw_string(&ssd, "Salinidade alta", 0, 40);
        ssd1306_draw_string(&ssd, "Lavar solo", 0, 50);
    }  
    ssd1306_send_data(&ssd);// Atualiza o display
}

#endif