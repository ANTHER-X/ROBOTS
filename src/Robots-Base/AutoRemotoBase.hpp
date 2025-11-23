#include "Robot.hpp"
#include <SoftwareSerial.h>

#pragma once

class AutoRemotoBase : public Robot{

    protected:
        uint8_t Vel;
        char tecla;
        SoftwareSerial *BTH = nullptr;

        //Metodos privados para el movimiento

        virtual void TeclaMoveMotors(char del, char atr, char der, char izq, char det);

        //Si usamos arduino y algun modulo BlueThoot
        virtual void BTHMove(unsigned int recSeg, char del, char atr, char der, char izq, char det);

    public:
        AutoRemotoBase(uint8_t receivePin, uint8_t transmitPin, uint8_t velocidad);
    
		/*Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER.
        Pero ahora, en este caso, los 2 motores primeros (que serian 2 llantas), seran los que se mueven
        hacia adelante*/
		virtual void AddMotors(std::vector<Motor> Mtrs);

		/*Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER.
        Pero ahora, en este caso, los 2 motores primeros (que serian 2 llantas), seran los que se mueven
        hacia adelante*/
		virtual void Add4Motors(Motor RotIzq1, Motor RotDer1, Motor izq2, Motor der2);

        virtual void Camina(unsigned int recSeg, char del, char atr, char der, char izq, char det, unsigned int activeTimeMillis);
};