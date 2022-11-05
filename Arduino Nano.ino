int LDRPines[2] = {A0, A1};
int V5Pines[6] = {8, 9, 6, 5, 4, 3};
int matrizLDR[2][2] = {{0, 0}, {0, 0}};

void loopMatriz() {
  for(int i=0; i<=1; i++) {
    if(i == 0) {
      digitalWrite(V5Pines[0], HIGH);
      digitalWrite(V5Pines[1], LOW);
    }
    else {
      digitalWrite(V5Pines[1], HIGH);
      digitalWrite(V5Pines[0], LOW);
    }
    

    for(int j=0; j<=1; j++) {
      if(analogRead(LDRPines[j]) <= 100) {
        matrizLDR[j][i] = 1;
      }
      else {
        matrizLDR[j][i] = 0;
      }
      delay(10);

    }
  }
}


void setup() {
  pinMode(LDRPines[0], INPUT);
  pinMode(LDRPines[1], INPUT);

  pinMode(V5Pines[0], OUTPUT);
  pinMode(V5Pines[1], OUTPUT);

  pinMode(V5Pines[2], OUTPUT);
  pinMode(V5Pines[3], OUTPUT);
  pinMode(V5Pines[4], OUTPUT);
  pinMode(V5Pines[5], OUTPUT);

  Serial.begin(9600);
}

void loop() {

  loopMatriz();

  for(int j=0; j<=1; j++) {
    for(int i=0; i<=1; i++) {
      if(matrizLDR[i][j] == 1) {
        if (i == 0 && j == 0) {
          digitalWrite(V5Pines[2], HIGH);
        }
        else if (i == 1 && j == 0) {
          digitalWrite(V5Pines[4], HIGH);
        }
        else if (i == 0 && j == 1) {
          digitalWrite(V5Pines[3], HIGH);
        }
        else if (i == 1 && j == 1) {
          digitalWrite(V5Pines[5], HIGH);
        }
      }

      else{
        if (i == 0 && j == 0) {
          digitalWrite(V5Pines[2], LOW);
        }
        else if (i == 1 && j == 0) {
          digitalWrite(V5Pines[4], LOW);
        }
        else if (i == 0 && j == 1) {
          digitalWrite(V5Pines[3], LOW);
        }
        else if (i == 1 && j == 1) {
          digitalWrite(V5Pines[5], LOW);
        }
      }
    }
  }
  delay(15);
}
