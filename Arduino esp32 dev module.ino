#include <TimeLib.h>

//            LDR
const int V5Pines[2] = {4, 16};
const int LDRPines[2] = {34, 35};

const int filas = 2;
const int columnas = 2;

long estDesc = filas*columnas;
int valuePrint;

int matrizLDR[2][2] = {{0, 0}, 
                       {0, 0}};


//            DISPLAY
const int DIGITOS[10][7] = {
/*0*/ {0,0,0,0,0,0,1},
/*1*/ {1,0,0,1,1,1,1},
/*2*/ {0,0,1,0,0,1,0},
/*3*/ {0,0,0,0,1,1,0},
/*4*/ {1,0,0,1,1,0,0},
/*5*/ {0,1,0,0,1,0,0},
/*6*/ {0,1,0,0,0,0,0},
/*7*/ {0,0,0,1,1,1,1},
/*8*/ {0,0,0,0,0,0,0},
/*9*/ {0,0,0,0,1,0,0}
};

const int OFF = HIGH;

const int A = 32;
const int B = 33;
const int C = 25;
const int D = 26;
const int E = 27;
const int F = 14;
const int G = 12;
 
const int N = 7;
const int SEGMENTOS[N] = {A,B,C,D,E,F,G};

//            SENSOR UTLRASONICO
const int TrigPin = 5;
const int EchoPin = 17;
const int TrigPin2 = 23;
const int EchoPin2 = 22;

void loopLDR(){
  for(int i=0; i < filas; i++){
    if (i == 0){
      digitalWrite(V5Pines[1], HIGH);
      digitalWrite(V5Pines[0], LOW);
    }
    else if(i == 1){
      digitalWrite(V5Pines[1], LOW);
      digitalWrite(V5Pines[0], HIGH);
    }
    
    for(int j = 0; j < columnas; j++){
      if(analogRead(LDRPines[j]) <= 100){
        matrizLDR[i][j] = 1;
      }
      else{
        matrizLDR[i][j] = 0;
      }
      delay(10);
    }
  }
}

int ValueMLDR(){
  int count;

  for(int i=0; i < filas; i++){
    for(int j=0; j < columnas; j++){
      if(matrizLDR[i][j] == 0){
        count = count + 1;
      }
    }
  }
  return count;
}

void print(int d){
  for (int i=0; i<N; i++){
    digitalWrite(SEGMENTOS[i], DIGITOS[d][i]);
  }
}

bool sensorUltra1(){
  
  long difTiempo;
  long distancia;
  
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  
  difTiempo = pulseIn(EchoPin, HIGH);
  distancia = difTiempo / 59;
  delay(100);

  if(distancia <=10 && distancia >= 0){
    return true;
  }
  else{
    return false;
  }
}

bool sensorUltra2(){
  
  long difTiempo2;
  long distancia2;
  
  digitalWrite(TrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin2, LOW);
  
  difTiempo2 = pulseIn(EchoPin2, HIGH);
  distancia2 = difTiempo2 / 59;
  delay(100);

  if(distancia2 <=10 && distancia2 >= 0){
    return true;
  }
  else{
    return false;
  }
}


void setup() {
  pinMode(V5Pines[0], OUTPUT);
  pinMode(V5Pines[1], OUTPUT);
  pinMode(LDRPines[0], INPUT);
  pinMode(LDRPines[1], INPUT);

  for (int i=0; i<N; i++){
    pinMode(SEGMENTOS[i], OUTPUT);
    digitalWrite(SEGMENTOS[i], OFF);
  }

  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  digitalWrite(TrigPin, LOW);
  digitalWrite(TrigPin2, LOW);

  Serial.begin(9600);
}

void loop() {
  
  if(sensorUltra1()){
    estDesc = estDesc -1;
    
    if(estDesc < 0){
      estDesc = 0;
    }
  }

  else if(sensorUltra2()){
    estDesc = estDesc +1;

    if (estDesc > 4){
      estDesc = 4;
    }
  }

  valuePrint = estDesc;

  if(second()%5==0 || second()==0){
    loopLDR();
    
    if(estDesc != ValueMLDR()){
      valuePrint = ValueMLDR();
      estDesc =  ValueMLDR();
    }
  }

  print(valuePrint);
  delay(1000);
}
