#include <Servo.h>

#define SERVOPINH  5 // orizontal servo
#define SERVOPINV  6 // vertical servo

Servo horizontal;
Servo vertical;

int servoh = 90;
int servov = 120;

const int servohLimitHigh = 180;
const int servohLimitLow = -60;
const int servovLimitHigh = 180;
const int servovLimitLow = 45;

const int ldrlt = A0; // top left
const int ldrrt = A1; // top right
const int ldrld = A2; // bottom left
const int ldrrd = A3; // bottom right

void setup() {
   Serial.begin(115200);
  horizontal.attach(SERVOPINH);
  vertical.attach(SERVOPINV);
  horizontal.write(servoh);
  vertical.write(servov);
  delay(0);
}

void loop() {
  // Citirea valorilor de la senzorii de lumină
  int lt = analogRead(ldrlt);
  int rt = analogRead(ldrrt);
  int ld = analogRead(ldrld);
  int rd = analogRead(ldrrd);

    // Calcularea directă a diferențelor de lumină
  int dvert = ((lt + rt) - (ld + rd)) / 2;
  int dhoriz = ((lt + ld) - (rt + rd)) / 2;

  // Ajustarea servo-ului vertical
  if (abs(dvert) > 100) { // Dacă diferența de lumină pe verticală este mai mare decât 100
    servov = constrain(servov + (dvert > 0 ? 1 : -1), servovLimitLow, servovLimitHigh);  // Ajustează unghiul vertical în limitele permise
    vertical.write(servov); // Aplică noul unghi la servo-ul vertical
  }

  // Ajustarea servo-ului orizontal
  if (abs(dhoriz) > 100) { // Dacă diferența de lumină pe orizontală este mai mare decât 100
    servoh = constrain(servoh + (dhoriz > 0 ? 1 : -1), servohLimitLow, servohLimitHigh); // Ajustează unghiul orizontal în limitele permise
    horizontal.write(servoh); // Aplică noul unghi la servo-ul orizontal
  }

  delay(50); // Mică întârziere pentru a stabiliza mișcările
}
