/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include "RLB-Servo.hpp"

void RLBServo::TomaDistanciaMayor(){
    //Tomamos las distancias moviendonos ciertos grados con el servoMotor
    servo.write(180); delay(100); DistIzquierda = ActivateUS(US); delay(200);
    servo.write(90);  delay(100); DistDelante = ActivateUS(US); delay(200);
    servo.write(0);   delay(100); DistDerecha = ActivateUS(US); delay(200);
    servo.write(90);  delay(200);
}

RLBServo::RLBServo(uint8_t velocidadRecta, uint8_t velocidadGiro, unsigned int timeGiro, unsigned int timeRec, UltraSonico us, uint8_t pinServo, MotorDriverType typeMotor)
: RLBase(velocidadRecta, velocidadGiro, timeGiro, timeRec, typeMotor){
    US = us;
    servo.attach(pinServo);
    servo.write(90);
}
