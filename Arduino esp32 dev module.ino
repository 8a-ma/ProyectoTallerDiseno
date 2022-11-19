#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

// sensorUltra1
int TriggPin = 17;
int EcchoPin = 5;
int V5 = 21;

//sensorUltra2
int TriggPin2 = 23;
int EcchoPin2 = 22;

int LDRPines[2] = {12, 13};
int V5Pines[2]  = {14, 27};

int filas = 2;
int columnas = 2;

int matrizLDR[2][2] = {{0, 0}, {0, 0}};

int estDesc = filas + columnas;
int valuePrint;

void loopMatrizLDR(){
  for(int i = 0; i <= columnas -1; i++) // n-1, donde n es el numero de columnas
  {
    if(i == 0) 
    {
      digitalWrite(V5Pines[0], HIGH);
      digitalWrite(V5Pines[1], LOW);
    }
    else {
      digitalWrite(V5Pines[1], HIGH);
      digitalWrite(V5Pines[0], LOW);
    }
     
    //Serial.println(i);
    for(int j = 0; j <= filas -1; j++) //n-1, donde n es el numero de filas
    {

      if(analogRead(LDRPines[j]) <= 100)
      {
        matrizLDR[j][i] = 1;
      }
      else
      {
        matrizLDR[j][i] = 0;
      }
      delay(10);
    }
  }
}


int valueMatrizLDR(){
  int count = 0;
  for(int i=0; i <= filas -1; i++){
    for(int j=0; j <= columnas -1; j++){
      if (matrizLDR[i][j] == 0){
        count = count + 1;
      } 
    }
  }
  return count;
}

bool sensorUltra1(){
  

  int difTiempo;
  int distancia;
  
  digitalWrite(TriggPin, HIGH);
  delay(1);
  digitalWrite(TriggPin, LOW);
  
  difTiempo = pulseIn(EcchoPin, HIGH);
  distancia = difTiempo / 58.2;
  delay(200);

  if(distancia <=200 && distancia >= 0){
    return true;
  }
  else{
    return false;
  }
}

bool sensorUltra2(){

  int difTiempo;
  int distancia;
  
  digitalWrite(TriggPin2, HIGH);
  delay(1);
  digitalWrite(TriggPin2, LOW);
  
  difTiempo = pulseIn(EcchoPin2, HIGH);
  distancia = difTiempo / 58.2;
  delay(200);

  if(distancia <=200 && distancia >= 0){
    return true;
  }
  else{
    return false;
  }
}
void setup(){
  
  pinMode(EcchoPin, INPUT);
  pinMode(TriggPin, OUTPUT);
  pinMode(EcchoPin2, INPUT);
  pinMode(TriggPin2, OUTPUT);
  pinMode(V5, OUTPUT);
  
  pinMode(V5Pines[0], OUTPUT);
  pinMode(V5Pines[1], OUTPUT);

  pinMode(LDRPines[0], INPUT);
  pinMode(LDRPines[1], INPUT);

  lcd.init();
  lcd.backlight();
  lcd.print("Hola Mundo");
  lcd.setCursor(0,1);
  
  delay(10);

  Serial.begin(9600); 
}

void loop(){ 

  digitalWrite(V5, HIGH);
 
  if(sensorUltra1()){

    estDesc = estDesc -1;

    if (estDesc < 0){
      estDesc = 0;
    }
  }

  if(sensorUltra2()){

    estDesc = estDesc +1;

    if (estDesc > 4){
      estDesc = 4;
    }
  }

  valuePrint = estDesc;

  if (second() % 5 == 0 || second() == 0){

    if (estDesc != valueMatrizLDR()){ //Se verifica que sean iguales para luego cambiarlo si es que no son iguales con lo real
      valuePrint = valueMatrizLDR(); //Se print lo que es real
      estDesc = valueMatrizLDR();
    }

   }
 
  Serial.println(valuePrint); //Se print primero los estacionamientos "desocupados"
  lcd.setCursor(0,1);
  lcd.print(String(valuePrint));
  
  
}
