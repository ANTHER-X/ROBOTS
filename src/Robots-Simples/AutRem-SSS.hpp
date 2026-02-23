/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

/* Servo steering system for remote-control car (Sistema de dirección servo para auto remoto) */

#include "../Robots-Base/AutoRemotoBase.hpp"
#include <Servo.h>

#pragma once

class AutRemSSS : public AutoRemotoBase{
    protected:
        Servo servoControler;
        unsigned long startTime;
    
        virtual void MDerIzq(Motor* M, uint8_t size, bool Der) override;
        
        //Modificamos un poco
        virtual void BTHMove(unsigned int recSeg, char del, char atr, char der, char izq, char det, char spedMas, char spedMenos) override;

    public:
    AutRemSSS(uint8_t pinServo, uint8_t velocidad, uint8_t receivePin, uint8_t transmitPin, MotorDriverType typeMotor);
    virtual void AddMotors(Motor* Mtrs, uint8_t size) override;

};