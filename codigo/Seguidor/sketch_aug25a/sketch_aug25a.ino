#include <Arduino.h>

enum Estado {
  SEGUIR_LINHA,
  GIRAR_DIREITA,
  GIRAR_DIREITA_POUCO,
  GIRAR_ESQUERDA_POUCO,
  GIRAR_ESQUERDA,
  PARAR
};


Estado estadoAtual = SEGUIR_LINHA;
const int sensorPins[] = { 33, 25, 35, 32}; //(33) e 25 DD | 35 e (32) EE
const int DirecaoDireito[] = { 15, 4 };
const int DirecaoEsquerdo[] = { 16, 5 };
const int ControleDireito = 2;
const int ControleEsquerdo = 17;
const int numSensors = sizeof(sensorPins) / sizeof(sensorPins[0]);


const int threshold = 500;
const int motorSpeed = 80;


void controlarMotores(int velocidadeDireita, int velocidadeEsquerda) {
  analogWrite(ControleDireito, velocidadeDireita);
  analogWrite(ControleEsquerdo, velocidadeEsquerda);

  if (velocidadeDireita > 0) {
    digitalWrite(DirecaoDireito[0], HIGH);
    digitalWrite(DirecaoDireito[1], LOW);
  } else {
    digitalWrite(DirecaoDireito[0], LOW);
    digitalWrite(DirecaoDireito[1], HIGH);
  }

  if (velocidadeEsquerda > 0) {
    digitalWrite(DirecaoEsquerdo[0], HIGH);
    digitalWrite(DirecaoEsquerdo[1], LOW);
  } else {
    digitalWrite(DirecaoEsquerdo[0], LOW);
    digitalWrite(DirecaoEsquerdo[1], HIGH);
  }
}


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numSensors; i++) {
    pinMode(sensorPins[i], INPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(DirecaoDireito[i], OUTPUT);
    pinMode(DirecaoEsquerdo[i], OUTPUT);
  }
  pinMode(ControleDireito, OUTPUT);
  pinMode(ControleEsquerdo, OUTPUT);
}

void loop() {
  // bool new = false;
  int readed[4] = {0, 0, 0, 0};
  int sensorValues[numSensors];

  for (int i = 0; i < numSensors; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
  }
  // if (readed != sensorValues)
  
  if((sensorValues[1] > threshold) && (sensorValues[2] > threshold) && sensorValues[3] > threshold){
    controlarMotores(80, 80);
    Serial.println("Frente");

  }
 if((sensorValues[1] < threshold) && (sensorValues[2] > threshold) && (sensorValues[3] > threshold)){
    controlarMotores(-70, 70);
    Serial.println("Direita pouco");
    // delay(100); //Direita
  }
   if((sensorValues[1] > threshold) && (sensorValues[2] < threshold) && (sensorValues[3] > threshold)){
    controlarMotores(70, -70);
    Serial.println("Esquerda pouco");
    // delay(100); //Esquerda
  }
  if((sensorValues[3] < threshold) && (sensorValues[1] > threshold) && (sensorValues[2] > threshold)){
    controlarMotores(90, -90);
    Serial.println("Esquerda Muito");
  }
  
}
