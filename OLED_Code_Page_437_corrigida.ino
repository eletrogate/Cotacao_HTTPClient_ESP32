/******************************************************************************
                    Cotação do Dólar em Tempo Real com ESP32
  Sketch Auxiliar: Exemplo de Impressão de caracteres Code page 437 no display OLED

                          Criado em 03 de Junho de 2022
                                por Michel Galvão


  Blog Eletrogate - Veja este e outros projetos e tutoriais no blog Eletrogate
                            https://blog.eletrogate.com/

  Eletrogate - Loja de Arduino \\ Robótica \\ Automação \\ Apostilas \\ Kits
                            https://www.eletrogate.com/
******************************************************************************/

// Inclusão da(s) biblioteca(s)
#include <Wire.h>             // Biblioteca nativa do ESP32
#include <Adafruit_SSD1306.h> // Necessária Instalação

#define SCREEN_WIDTH 128 // Largura da tela OLED, em pixels
#define SCREEN_HEIGHT 64 // Altura da tela OLED, em pixels

#define OLED_RESET     -1 // Pino de Reset (ou -1 se compartilhar o pino de reset do Arduino)

#define SCREEN_ADDRESS 0x3C // Endereço I2C: 0x3D para 128x64 ou 0x3C para 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // objeto para
//                                                              controle do display OLED.

void setup() {

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) // Inicializa o display
  {
    Serial.println("Falha na alocação de SSD1306");
    for (;;); // Não prossiga, faça um loop para sempre
  }

  display.clearDisplay(); // Limpa a tela
  display.setTextColor(SSD1306_WHITE); // define a cor dos objetos
  //                                        (texto, linhas, círculos, etc.) do
  //                                        display para a cor branca equivalente
  //                                        do display (azul).
  display.display(); // Atualiza a tela

  display.cp437(true); // define se usa a versão corrigida de caracteres Code
  //                        Page 437 ou não. true para versão corrigida, false
  //                        para versão errônea.

  for (int c = 0; c <= 0xFF; c++) // Estrutura de repetição para mostrar todos
    //                                 os caracteres Code Page 437.
  {
    display.clearDisplay(); // Limpa a tela
    display.setCursor(0, 0); // configura o cursor para ir na coluna 0 e linha 0
    display.setTextSize(1); // multiplica a escala do texto por 1

    // escreve no display o endereço atual do caractere mostrado
    display.print("0x");
    display.print(c, HEX);
    display.print(": ");

    // escreve no display a quantidade de caracteres já mostrado e o total de
    //  caracteres.
    display.print(int(c));
    display.print(" de ");
    display.print(int(0xFF));

    display.setTextSize(3); // multiplica a escala do texto por 3
    display.setCursor(0, 16); // configura o cursor para ir na coluna 0 e linha 16
    display.write(char(c)); // escreve o caractere Code Page 437
    display.display(); // Atualiza a tela
    delay(200); // pausa de 200 milissegundos
  }

  display.clearDisplay(); // Limpa a tela
  display.setCursor(0, 16); // configura o cursor para ir na coluna 0 e linha 16
  display.setTextSize(3); // multiplica a escala do texto por 3
  display.println("FIM");
  display.display(); // Atualiza a tela

  while (1); // entra em um laço de repetição infinito
}

void loop() {}
