#include <Arduino.h>

enum Estado {
  SEGUIR_LINHA,
  GIRAR_DIREITA,
  GIRAR_ESQUERDA,
  PARAR
};

const int threshold = 1500;


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

Estado estadoAtual = SEGUIR_LINHA;
const int sensorPins[] = { 13, 14, 25, 33};
const int DirecaoDireito[] = { 22, 23};
const int DirecaoEsquerdo[] = {19 , 21};
const int ControleDireiro = 5; 
const int ControleEsquerdo = 16;                                                                                                 
const int numSensors = sizeof(sensorPins) / sizeof(sensorPins[0]);
void setup(){
  Serial.begin(9600);
  for (int i = 0; i< numSensors; i++){
    pinMode(sensorPins[i], INPUT);
  }
  for (int i = 0; i<2; i++){
    pinMode(DirecaoDireito[i], OUTPUT);
    pinMode(DirecaoEsquerdo[i], OUTPUT);
  }
  pinMode(ControleDireito, OUTPUT);
  pinMode(ControleEsquerdo, OUTPUT);
}

void loop(){
  int sensorValues[numSensors];

  for(int i=0; i < numSensors; i++){

  }

switch (estadoAtual){
    case SEGUIR_LINHA:
      if (sensorValues[0] > threshold && sensorValues[1] > threshold &&
          sensorValues[2] > threshold && sensorValues[3] > threshold) {
        // Todos os sensores acima do limiar, seguir a linha
        controlarMotores(motorSpeed, motorSpeed);
      } else if (sensorValues[3] > threshold) {
        // Sensor direito ativado, transicionar para o estado de girar à esquerda
        estadoAtual = GIRAR_ESQUERDA;
      } else if (sensorValues[0] > threshold) {
        // Sensor esquerdo ativado, transicionar para o estado de girar à direita
        estadoAtual = GIRAR_DIREITA;
      }
      break;

    case GIRAR_DIREITA:
      // Girar à direita (correção)
      controlarMotores(motorSpeed, -motorSpeed); // Gira para a direita
      delay(500); // Tempo de giro
      estadoAtual = SEGUIR_LINHA; // Volta a seguir a linha
      break;

    case GIRAR_ESQUERDA:
      // Girar à esquerda (correção)
      controlarMotores(-motorSpeed, motorSpeed); // Gira para a esquerda
      delay(500); // Tempo de giro
      estadoAtual = SEGUIR_LINHA; // Volta a seguir a linha
      break;


    case PARAR:
      controlarMotores(0, 0);
      if (sensorValues[0] > threshold || sensorValues[1] > threshold ||
          sensorValues[2] > threshold || sensorValues[3] > threshold) {
        // Pelo menos um sensor acima do limiar, transicionar de volta para seguir a linha
        estadoAtual = SEGUIR_LINHA;
      }
      break;

}
}
