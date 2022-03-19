/* 
  main file conication slave spi

 */

#include <Arduino.h>
#include <SPI.h>
#define PIN3_INT_1 3
#define SLAVE 10

void incpulso1();
char buf = 15;
unsigned char  vazao1;                                              // declara variáveis para leitura das vazões
int contaPulso1;                                           // declara as funções para contagem dos pulsos de cada rotâmetro

void setup() {

  digitalWrite(SLAVE, HIGH);
  SPI.begin();


  Serial.begin(9600);                         // habilita serial 0 e sua taxa de trabalho
  pinMode(PIN3_INT_1, INPUT);                          // configura pino 3 para receber sinal e chamar interrupção 1
  pinMode(21, INPUT);                         // configura pino 21 para receber sinal e chamar interrupção 2

  attachInterrupt(1, incpulso1, RISING);      // habilita chamada à primeira interrupção (rotâmetro 1)

}

void loop() {
  
  contaPulso1 = 0;               // zera os contadores de pulsos
  sei();          // habilita interrupção
  delay(1000);                                    // aguarda 1 segundo entre leituras
  cli();          // desabilita interrupção

  vazao1 = contaPulso1 / 10.7;                     // equação para conversão da contagem de pulsos em fluxo (L/min) para rot. 1
                                                  // espera-se que os fluxos não passem de 500 L/min
  Serial.println(vazao1);                         // envia fluxo 1 para receptor MEGA

  digitalWrite(SLAVE, LOW);
  SPI.transfer(buf);
  delay(100);

}
// rotina chamada pela interrupção provocada pelo rotâmetro 1
void incpulso1() {
  contaPulso1++;        // incrementa variável contando os pulsos do sensor 1
}
