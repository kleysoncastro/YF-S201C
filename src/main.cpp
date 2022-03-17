#include<SPI.h>
char buf = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI, OUTPUT);
  pinMode(SCK, INPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();  //allows SPI interrupt
}

void loop(void)
{

    Serial.print("buf vindo do SPI: ");
  
    Serial.println(buf, HEX);
    Serial.println(buf);


    Serial.println("=============================================");
  }


ISR (SPI_STC_vect)   //Inerrrput routine function
{
  buf = SPDR;
}