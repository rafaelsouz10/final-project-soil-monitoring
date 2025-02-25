# Projeto Final Embarcatech - Sistema de Monitoramento dos Parâmetros do Solo

---

## Descrição do Projeto

Projeto final do **EmbarcaTech**, que visa implementar um sistema de monitoramento dos parâmetros do solo (umidade, temperatura e condutividade elétrica) utilizando a placa BitDogLab. O sistema é interativo, permitindo ao usuário simular a leitura dos parâmetros e visualizar os resultados no display OLED.

![image](https://github.com/user-attachments/assets/0ec05929-7ebe-445f-ae6b-326197ce245c)

---

## Requisitos

- **Microcontrolador**: Raspberry Pi Pico ou Raspberry Pi Pico W (opcional)
- **Placa de Desenvolvimento:** BitDogLab (opcional).
- **Conta Criada no Wokwi Simulator**: [Wokwi](https://wokwi.com/).
- **Editor de Código**: Visual Studio Code (VS Code).
- **SDK do Raspberry Pi Pico** configurado no sistema.
- Ferramentas de build: **CMake** e **Ninja**.

---

## Instruções de Uso

### 1. Clone o Repositório

Clone o repositório para o seu computador:
```bash
git clone https://github.com/rafaelsouz10/final-project-soil-monitoring.git
cd final-project-soil-monitoring
code .
```
---

### 2. Instale as Dependências

Certifique-se de que o SDK do Raspberry Pi Pico está configurado corretamente no VS Code. As extensões recomendadas são:

- **C/C++** (Microsoft).
- **CMake Tools**.
- **Wokwi Simulator**.
- **Raspberry Pi Pico**.

---

### 3. Configure o VS Code

Abra o projeto no Visual Studio Code e siga as etapas abaixo:

1. Certifique-se de que as extensões mencionadas anteriormente estão instaladas.
2. No terminal do VS Code, compile o código clicando em "Compile Project" na interface da extensão do Raspberry Pi Pico.
3. O processo gerará o arquivo `.uf2` necessário para a execução no hardware real.

---

### 4. Teste no Simulador Wokwi Integrado ao VS Code

Após ter configurado o VS Code conforme descrito no item 3, siga os passos abaixo para simular o projeto:

1. Abra o arquivo `diagram.json` no Visual Studio Code.
2. Clique no botão "Play" disponível na interface.
3. Divirta-se interagindo com os componentes disponíveis no simulador integrado!

---

### 5. Teste no Hardware Real

#### Utilizando a Placa de Desenvolvimento BitDogLab com Raspberry Pi Pico W:

1. Conecte a placa ao computador no modo BOTSEEL:
   - Pressione o botão **BOOTSEL** (localizado na parte de trás da placa de desenvolvimento) e, em seguida, o botão **RESET** (localizado na frente da placa).
   - Após alguns segundos, solte o botão **RESET** e, logo depois, solte o botão **BOOTSEL**.
   - A placa entrará no modo de programação.

2. Compile o projeto no VS Code utilizando a extensão do [Raspberry Pi Pico W](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico):
   - Clique em **Compile Project**.

3. Execute o projeto clicando em **Run Project USB**, localizado abaixo do botão **Compile Project**.

---

### 🔌 6. Conexões e Esquemático
Abaixo está o mapeamento de conexões entre os componentes e a Raspberry Pi Pico W:

| **Componentes**        | **Pino Conectado (GPIO)** |
|------------------------|---------------------------|
| Display SSD1306 (SDA)  | GPIO 14                   |
| Display SSD1306 (SCL)  | GPIO 15                   |
| Joystick VRX           | GPIO 27                   |
| Botão A                | GPIO 5                    |
| Botão B                | GPIO 6                    |
| LED RGB Vermelho       | GPIO 13                   |
| LED RGB Azul           | GPIO 12                   |
| LED RGB Verde          | GPIO 11                   |

#### 🛠️ Hardware Utilizado
- **Microcontrolador:** Raspberry Pi Pico W
- **Display:** OLED SSD1306 (I2C)
- **Joystick Analógico** (VRX)
- **Botões A e B**
- **Led RGB**

### 7. Funcionamento do Sistema

#### 📌 Funcionalidades

**Simulação de parâmetros do solo:**

- **Umidade do solo:** Ajustada via joystick (variação de 0% a 100%).
- **Temperatura do solo:** Ajustada via joystick (variação de 0°C a 50°C).
- **Condutividade elétrica do solo:** Ajustada via joystick (variação de 0 dS/m a 5 dS/m).

**Controle via joystick:**

- O joystick é utilizado para ajustar os valores dos parâmetros utilizando o eixo X.

**Exibição dos valores no display OLED:**

- Os valores dos parâmetros são exibidos em tempo real no display OLED.
- O display também mostra mensagens de status e instruções para o usuário.

**Feedback visual com LEDs RGB:**

- **LED Vermelho:** Indica condições críticas máximas do solo (excesso de umidade, temperatura alta, salinização excessiva).
- **LED Verde:** Indica condições ideais do solo.
- **LED Azul:** Indica condições críticas mínimas do solo (umidade baixa, temperatura baixa e salinização mínima.).

**Interação com botões:**

- **Botão A:** Salva os valores dos parâmetros e avança para a próxima leitura.
- **Botão B:** Exibe detalhes sobre os parâmetros do solo (umidade, temperatura, condutividade elétrica).

#### 📌 Fluxo de Operação

**Inicialização:**

- O sistema inicia a mensagem “EMBARCATECH READ SOIL PARAMETER” no display OLED.
- O usuário pressiona o Botão A para começar a leitura dos parâmetros.

**Leitura dos Parâmetros:**

- O usuário ajusta os valores de umidade, temperatura e condutividade elétrica usando o eixo X do joystick.
- Os valores são exibidos no display OLED e salvos ao pressionar o Botão A.

**Feedback Visual:**

- Os LEDs RGB fornecem feedback visual sobre o status do solo com base nos valores lidos com intensidade configurada de 50%.

**Detalhes dos Parâmetros:**

- Após salvar os parâmetros do solo, o usuário pode pressionar o Botão B para visualizar os detalhes sobre cada parâmetro, como dicas sobre o solo e ações recomendadas.

**Reinicialização:**

- Após visualizar os detalhes, o usuário pode reiniciar o sistema pressionando o Botão A novamente.

### 8. Vídeo Demonstrativo

Click [AQUI](O lindo do vídeo irá aqui) para acessar o link do Vídeo Ensaio
