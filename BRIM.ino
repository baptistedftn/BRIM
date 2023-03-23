#include <Servo.h>
#include <SoftwareSerial.h>
Servo servob;   //base
Servo servoc;   //coude
Servo servod1;  //doigt 1
Servo servod2;  //doigt 2

SoftwareSerial BTserial(2, 3);  // RX | TX

int doigt1 = 90;  //gauche
int doigt2 = 90;  //droite
int coude = 90;
int base = 90;
unsigned long tBaseGauche, tCoudeDroite, tGrip, tBaseDroite, tCoudeGauche, tOpen, tDelay;

unsigned long lastMove, currentTime;
int angle;
int isDemo = false;

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  servob.attach(6);
  servoc.attach(7);
  servod1.attach(4);
  servod2.attach(5);
  servob.write(base);
  servoc.write(coude);
  servod1.write(doigt1);
  servod2.write(doigt2);
  delay(5000);
  Serial.println("Let's GOOOOO!");
}

void loop() {
  demo();
  while (BTserial.available() != 0) {
    switch (BTserial.read()) {
      case 'A':
        isDemo = !isDemo;
        break;
      case 'B':
        base = BTserial.readStringUntil('*').toInt();
        Serial.println("base");
        currentTime = millis();
        if ((currentTime - lastMove) > 50) {
          lastMove = currentTime;
          servob.write(base);
        }
        break;
      case 'C':
        coude = BTserial.readStringUntil('*').toInt();
        Serial.println("coude");
        currentTime = millis();
        if ((currentTime - lastMove) > 50) {
          lastMove = currentTime;
          servoc.write(coude);
        }
        break;
      case 'D':
        angle = BTserial.readStringUntil('*').toInt();
        doigt1 = 60 + angle;
        doigt2 = 120 - angle;
        Serial.println("doigts");
        currentTime = millis();
        if ((currentTime - lastMove) > 50) {
          lastMove = currentTime;
          servod1.write(doigt1);
          servod2.write(doigt2);
        }
        break;
    }
  }
}

void demo() {
  if (!isDemo) return;
  if (millis() - tBaseGauche > 0) {
    baseGauche();
    tBaseGauche = millis() + 3000;
  }
  if (millis() - tCoudeDroite > 0) {
    coudeDroite();
    tCoudeDroite = millis() + 3000;
  }
  if (millis() - tGrip > 0) {
    grip();
    tGrip = millis() + 3000;
  }
  if (millis() - tBaseDroite > 0) {
    baseDroite();
    tBaseDroite = millis() + 3000;
  }
  if (millis() - tCoudeGauche > 0) {
    coudeGauche();
    tCoudeGauche = millis() + 3000;
  }
  if (millis() - tOpen > 0) {
    open();
    tOpen = millis() + 1000;
  }
  // if (millis() - tDelay > 0) {
  //   grip();
  //   tDelay = millis() + 5000;
  // }
}

void baseGauche() {
  servob.write(base + 90);
}
void baseDroite() {
  servob.write(base - 90);
}
void baseMilieu() {
  servob.write(base);
}
void coudeDroite() {
  servoc.write(coude - 40);
}
void coudeMilieu() {
  servoc.write(coude);
}
void coudeGauche() {
  servoc.write(coude + 40);
}
void grip() {
  servod1.write(doigt1 - 30);
  servod2.write(doigt2 + 30);
}
void open() {
  servod1.write(doigt1 + 70);
  servod2.write(doigt2 - 70);
}
void doigtsMilieu() {
  servod1.write(doigt1);
  servod2.write(doigt2);
}
