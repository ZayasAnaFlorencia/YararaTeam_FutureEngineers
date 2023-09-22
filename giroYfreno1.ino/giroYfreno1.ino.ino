#include <Servo.h>
#include <NewPing.h>
#define MA 2
#define MB 4
#define MPWM 3

int cm1, cm2 , cm3 = 0;
int tiempo = 0;
int ultimogiro = 0;
int modo = 0;
int comp = 0;


NewPing s_Izq(7, 8, 400);
NewPing s_Der(9, 10, 400);
NewPing s_Cen(11, 12, 400);
int giro = 0;
Servo direccion;

int velocidad = 180;

void setup() {
  // put your setup code here, to run once:
  pinMode(MA, OUTPUT);
  pinMode(MB, OUTPUT);
  pinMode(MPWM, OUTPUT);
  direccion.attach(6);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

 cm1 = s_Izq.ping_cm();
  cm3 = s_Der.ping_cm();
  cm2 = s_Cen.ping_cm();

  direccion.write(centrar(cm1, cm3));

  
  Serial.print(cm1);
  Serial.print("  ");
  Serial.print(cm3);
Serial.print("  ");
  Serial.print(cm2);
Serial.print("  ");
  Serial.print(giro);
Serial.print("  ");

  Serial.println(centrar(cm1, cm3));

digitalWrite(MA, HIGH);
digitalWrite(MB, LOW);
digitalWrite(MPWM, 100);
if (cm2 < 10 && cm2 > 1){
  digitalWrite(MA, LOW);
digitalWrite(MB, HIGH);
digitalWrite(MPWM, 190);
direccion.write(arreglo(cm1, cm3));
delay(1000);
direccion.write(90);
digitalWrite(MA, HIGH);
digitalWrite(MB, LOW);
digitalWrite(MPWM, 90);
delay(600);
}

  //  direccion.write(60);
  //  delay(1500);
  //  direccion.write(90);
  //  delay(1500);
  //  direccion.write(130);
  //  delay(1500);
  if (giro > 11){
    while(1){
      delay(1000);
      digitalWrite(MA, LOW);
      digitalWrite(MB, LOW);
      digitalWrite(MPWM, 0);
    }
  }

}


int centrar(int sen3, int sen1)
{
  if (sen1 < 1 || sen1 > 400){
    sen1 = 110;
  }
  if (sen3 < 1 || sen3 > 400){
    sen3 = 110;
  }
  int pos = sen1 + -sen3;
  int res = map(pos, -110, 110, 60, 120);
  if (res < 50){ res = 50; if (comp == 0 && tiempo > millis()) giro = giro + 1; comp = 1; tiempo = millis() + 700;}
  if (res > 130){ res = 130;if (comp == 0 && tiempo > millis()) giro = giro + 1; comp = 1; tiempo = millis() + 700;}
  if (res < 100 && res > 80 && tiempo < millis()) comp = 0;
  return res;
}
int arreglo(int sen3, int sen1)
{
  int pos = -sen1 + sen3;
  int res = map(pos, -50, 80, 60, 130);
  if (res < 60)  res = 60; 
  if (res > 130) res = 130;
  return res;
}
