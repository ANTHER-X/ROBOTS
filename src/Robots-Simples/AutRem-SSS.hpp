/* Servo steering system for remote-control car (Sistema de dirección servo para auto remoto) */

#include "../Robots-Base/AutoRemotoBase.hpp"
#include <Servo.h>

#pragma once

class AutRemSSS : public AutoRemotoBase{
    protected:
        Servo servoControler;
        unsigned long startTime;

        virtual void AddMotors(std::vector<Motor> Mtrs) override;

        virtual void MDerIzq(std::vector<Motor> &M, bool Der) override;
        
        //Modificamos un poco
        virtual void BTHMove(unsigned int recSeg, char del, char atr, char der, char izq, char det) override;

    public:
    AutRemSSS(uint8_t receivePin, uint8_t transmitPin, uint8_t pinServo, uint8_t velocidad);

};