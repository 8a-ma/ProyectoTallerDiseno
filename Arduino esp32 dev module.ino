int TriggPin = 17;
int EcchoPin = 5;
int V5 = 23;

int LDRPines[2] = {12, 13};
int V5Pines[2]  = {14, 27};

int filas = 2;
int columnas = 2;

int matrizLDR[2][2] = {{0, 0}, {0, 0}};


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


void setup()
{
  
  pinMode(EcchoPin, INPUT);
  pinMode(TriggPin, OUTPUT);
  pinMode(V5, OUTPUT);
  
  pinMode(V5Pines[0], OUTPUT);
  pinMode(V5Pines[1], OUTPUT);

  pinMode(LDRPines[0], INPUT);
  pinMode(LDRPines[1], INPUT);
  
  Serial.begin(9600); 
}

void loop()
{ 
  
  digitalWrite(V5, HIGH);

  int difTiempo;
  int distancia;
  
  digitalWrite(TriggPin, HIGH);
  delay(1);
  digitalWrite(TriggPin, LOW);
  
  difTiempo = pulseIn(EcchoPin, HIGH);
  distancia = difTiempo / 58.2;
  delay(200);
  
  if(distancia <=200 && distancia >= 0){

    int matrizCopy[2][2];

    memcpy(matrizCopy, matrizLDR, sizeof(matrizLDR));    

    for(int t = 0; t <= 5; t++)
    {
      loopMatrizLDR();

      if(memcmp(matrizLDR, matrizCopy, sizeof(matrizLDR)) != 0)
      {
        break;
      }
      else
      {
        delay(60000);
      }      
    }
  }

  Serial.println(valueMatrizLDR());
  delay(1500);
  
}