/**********************************************************************************************************
                           
                                  Projeto Tira de LEDs RGB com funções
    Neste projeto vamos usar funções para controlar o acionamento de LEDs endereçáveis numa tira de LEDs.
                    A tira de LEDs usada é a WS2812B e o microcontrolador é o ESP32s.

***********************************************************************************************************/
// Carrega a biblioteca
#include <Adafruit_NeoPixel.h>

#define PIN_LED 16      // Pino de controle da tira (GPIO16) pino 27
#define NUM_LED 8       // Numero de LEDs na tira

// Cor Customisada 1: Amarelo
#define RED_VAL_1       255
#define GREEN_VAL_1     255
#define BLUE_VAL_1      0

// Cor Customisada 2: Purpura
#define RED_VAL_2       255
#define GREEN_VAL_2     0
#define BLUE_VAL_2      255

// Cor Customisada 3: Ciano
#define RED_VAL_3       0
#define GREEN_VAL_3     255
#define BLUE_VAL_3      255

// Cor Customisada 4: Branco
#define RED_VAL_4       255
#define GREEN_VAL_4     255
#define BLUE_VAL_4      255

// Cria uma instancia da tira de leds
Adafruit_NeoPixel RGB_Strip = Adafruit_NeoPixel(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  RGB_Strip.begin();              // Inicializa a tira
  RGB_Strip.show();               // Acende os LEDs
  RGB_Strip.setBrightness(80);    // Ajusta o brilho da tira de 0 a 255
}

void loop() {

  // Chama a função passando as informações entre parenteses como parametro
  colorWipe(RGB_Strip.Color(255, 0, 0), 200);  // Vermelho
  colorWipe(RGB_Strip.Color(0, 255, 0), 200);  // Verde
  colorWipe(RGB_Strip.Color(0, 0, 255), 200);  // Azul

  colorWipe(RGB_Strip.Color(RED_VAL_1, GREEN_VAL_1, BLUE_VAL_1), 200);   // Cor Customisada 1: Amarelo
  colorWipe(RGB_Strip.Color(RED_VAL_2, GREEN_VAL_2, BLUE_VAL_2), 200);   // Cor Customisada 2: Purpura
  colorWipe(RGB_Strip.Color(RED_VAL_3, GREEN_VAL_3, BLUE_VAL_3), 200);   // Cor Customisada 3: Ciano
  colorWipe(RGB_Strip.Color(RED_VAL_4, GREEN_VAL_4, BLUE_VAL_4), 200);   // Cor Customisada 4: Branco
  
  // Chama a função arco-iris passando o tempo de duração de cada cor por parametro
  rainbow(50);
}

// Função que acende os LEDs em sequencia, um apos o outro, com a cor passada por parametro
void colorWipe(uint32_t c, uint16_t wait) {
  for (uint16_t i = 0; i < RGB_Strip.numPixels(); i++) {
    RGB_Strip.setPixelColor(i, c);
    RGB_Strip.show();
    delay(wait);
  }
}

// Função arco-iris. Alterna as cores dos LEDs, passando por todas as cores possiveis
void rainbow(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < RGB_Strip.numPixels(); i++) {
      RGB_Strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    RGB_Strip.show();
    delay(wait);
  }
}

// Entre com um valor de 0 a 255 para pegar um valor de cor.
// As cores são uma transição de R - G - B, voltando para R.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return RGB_Strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return RGB_Strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return RGB_Strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
