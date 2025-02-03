#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//******* CONFIGURACAO DO PROJETO *********

#define pinBotao 13
#define BuzinaLED 4
#define SensorBobina 12
#define Bobina 8
#define FotoSensores 6

#define tempoDebounce 50 //tempo em milisegundos para filtro do efeito bouncing

int ledPin, estado, partida, i, T, TempoLed=50, TempoMorto=0, modo = 1, modoanterior;
unsigned long TT[8];

LiquidCrystal_I2C lcd(0x3F, 16, 2);

bool estadoBotao = false;
bool estadoBotaoAnt = false;
unsigned long delayBotao;


void setup() { 
  pinMode(pinBotao, INPUT_PULLUP);
  pinMode( BuzinaLED, OUTPUT);
  digitalWrite(BuzinaLED, LOW);
  pinMode(SensorBobina, INPUT);
  pinMode(Bobina, OUTPUT);
  digitalWrite(Bobina, LOW);
  pinMode(FotoSensores, INPUT);

  lcd.init(); // INICIA A COMUNICAÇÃO COM O DISPLAY
  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY
  lcd.clear(); // LIMPA O DISPLAY
   
  lcd.setCursor(1, 0);
  lcd.print("PLANO INCLINADO");
  lcd.setCursor(3, 1);
  lcd.print("BEM VINDO!");
  delay(1000);

}

void loop() {

    

  switch (modo) {
    case 1: 
     lcd.display();    
     loop_modo1();
     break;
     
    case 2: 
     lcd.display();    
     loop_modo2();
     break;
     
    case 3: 
     lcd.display();    
     loop_modo3();
     break;
     
  }
}

//******************************************************************
void loop_modo1() { 

  if(modoanterior != modo) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("6 SENSORES");
    lcd.setCursor(3, 1);
    lcd.print("TEMPO TOTAL");
    modoanterior = modo;
  }
  partida = LOW;

  while(partida == LOW && modo == modoanterior){
    partida = digitalRead(SensorBobina);

    estadoBotao = !digitalRead(pinBotao);
    if ((millis() - delayBotao) > tempoDebounce) {
     if (estadoBotao && !estadoBotaoAnt) {
        modo++;
        if (modo > 3) modo = 1;
        
        delayBotao = millis();
      } else if (!estadoBotao && estadoBotaoAnt) {
        delayBotao = millis();
        }
    }
  estadoBotaoAnt = estadoBotao;
  }
     
 if( partida == HIGH){
    digitalWrite(Bobina, HIGH);
    digitalWrite(BuzinaLED, HIGH);
    delay(2000);
    digitalWrite(BuzinaLED, LOW);
    delay(1000);
    digitalWrite(Bobina,LOW);
    TT[0] = millis();
    digitalWrite(BuzinaLED, HIGH);
    delay(TempoLed);
    digitalWrite(BuzinaLED,LOW);
    delay(TempoMorto);
        lcd.clear();
  
    for(i=1; i<7; i++){
      estado = LOW;
      while(estado == LOW){
        estado = digitalRead(FotoSensores);
      }
      TT[i] = millis();
      digitalWrite(BuzinaLED,HIGH);
      delay(TempoLed);
      digitalWrite(BuzinaLED,LOW);
      delay(TempoMorto);

      if(i<4){      
        if(TT[i] - TT[0]<1000)  { 
          lcd.print("0");
          lcd.print((TT[i] - TT[0]));
          lcd.print(" ");
        } else {
            lcd.print((TT[i] - TT[0]));
            lcd.print(" ");
          }
      }
      if(i==4)  {
        if(TT[i] - TT[0]<1000)  { 
          lcd.setCursor(0, 1);
          lcd.print("0");
          lcd.print((TT[i] - TT[0]));
          lcd.print(" ");
        } else {
            lcd.setCursor(0, 1);
            lcd.print((TT[i] - TT[0]));
            lcd.print(" ");
          }
      }
     if(i>4)  {  
      if(TT[i] - TT[0]<1000)  { 
          lcd.print("0");
          lcd.print((TT[i] - TT[0]));
          lcd.print(" ");
        }  else {
            lcd.print((TT[i] - TT[0]));
            lcd.print(" ");
          }   
      }
  
    }
  }
    
}

//********************************************************************
void loop_modo2() {
  
if(modoanterior != modo) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("6 SENSORES");
    lcd.setCursor(1, 1);
    lcd.print("TEMPO PARCIAL");
    modoanterior = modo;
  }
  partida = LOW;

  while(partida == LOW && modo == modoanterior){
    partida = digitalRead(SensorBobina);

    estadoBotao = !digitalRead(pinBotao);
    if ((millis() - delayBotao) > tempoDebounce) {
     if (estadoBotao && !estadoBotaoAnt) {
        modo++;
        if (modo > 3) modo = 1;
        
        delayBotao = millis();
      } else if (!estadoBotao && estadoBotaoAnt) {
        delayBotao = millis();
        }
    }
  estadoBotaoAnt = estadoBotao;
  }
     
 if( partida == HIGH){
    digitalWrite(Bobina, HIGH);
    digitalWrite(BuzinaLED, HIGH);
    delay(2000);
    digitalWrite(BuzinaLED, LOW);
    delay(1000);
    digitalWrite(Bobina,LOW);
    TT[0] = millis();
    digitalWrite(BuzinaLED, HIGH);
    delay(TempoLed);
    digitalWrite(BuzinaLED,LOW);
     delay(TempoMorto);
    lcd.clear();
  
    for(i=1; i<7; i++){
      estado = LOW;
      while(estado == LOW){
        estado = digitalRead(FotoSensores);
      }
      TT[i] = millis();
      digitalWrite(BuzinaLED,HIGH);
      delay(TempoLed);
      digitalWrite(BuzinaLED,LOW);
      delay(TempoMorto);

      if(i<4){      
        if(TT[i] - TT[i-1]<1000)  { 
          lcd.print("0");
          lcd.print((TT[i] - TT[i-1]));
          lcd.print(" ");
        } else {
            lcd.print((TT[i] - TT[i-1]));
            lcd.print(" ");
          }
      }
      if(i==4)  {
        if(TT[i] - TT[i-1] < 1000)  { 
          lcd.setCursor(0, 1);
          lcd.print("0");
          lcd.print((TT[i] - TT[i-1]));
          lcd.print(" ");
        } else {
            lcd.setCursor(0, 1);
            lcd.print((TT[i] - TT[i-1]));
            lcd.print(" ");
          }
      }
     if(i>4)  {  
      if(TT[i] - TT[i-1] < 1000)  { 
          lcd.print("0");
          lcd.print((TT[i] - TT[i-1]));
          lcd.print(" ");
        }  else {
            lcd.print((TT[i] - TT[i-1]));
            lcd.print(" ");
          }   
      }
    }
  }
    
}

void loop_modo3() {
 
 if(modoanterior != modo) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("1 SENSOR");
    lcd.setCursor(3, 1);
    lcd.print("TEMPO TOTAL");
    modoanterior = modo;
  }
  partida = LOW;

  while(partida == LOW && modo == modoanterior){
    partida = digitalRead(SensorBobina);

    estadoBotao = !digitalRead(pinBotao);
    if ((millis() - delayBotao) > tempoDebounce) {
     if (estadoBotao && !estadoBotaoAnt) {
        modo++;
        if (modo > 3) modo = 1;
        
        delayBotao = millis();
      } else if (!estadoBotao && estadoBotaoAnt) {
        delayBotao = millis();
        }
    }
  estadoBotaoAnt = estadoBotao;
  }
     
 if( partida == HIGH){
    digitalWrite(Bobina, HIGH);
    digitalWrite(BuzinaLED, HIGH);
    delay(2000);
    digitalWrite(BuzinaLED, LOW);
    delay(1000);
    digitalWrite(Bobina,LOW);
    TT[0] = millis();
    digitalWrite(BuzinaLED, HIGH);
    delay(TempoLed);
    digitalWrite(BuzinaLED,LOW);
     delay(TempoMorto);
    lcd.clear();
  
    for(i=1; i<7; i++){
      estado = LOW;
      while(estado == LOW){
        estado = digitalRead(FotoSensores);
      }
      TT[i] = millis();
      digitalWrite(BuzinaLED,HIGH);
      delay(TempoLed);
      digitalWrite(BuzinaLED,LOW);
       delay(TempoMorto);

      if(i == 6){ 
        lcd.setCursor(2, 0);     
        lcd.print("TEMPO TOTAL");
        lcd.setCursor(5, 1);
        if(TT[i] - TT[0]<1000)  { 
          lcd.print("0");
          lcd.print((TT[i] - TT[0]));
          lcd.print(" ");
        }  else {
            lcd.print((TT[i] - TT[0]));
            lcd.print(" ");
          }   
          
        
        
      }
      
      }
  
    }
  
    
  
}
