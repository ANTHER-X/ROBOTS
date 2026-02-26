/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include "Robot.hpp"

#if defined(__AVR__)
    #include <SoftwareSerial.h>
#endif

#if defined(ESP32)
    #include <BluetoothSerial.h>
#endif

#pragma once

class AutoRemotoBase : public Robot{

    protected:
        uint8_t Vel;
        char tecla;

        #if defined(ESP32)
            BluetoothSerial BTHESP;
        #else
            SoftwareSerial BTH = SoftwareSerial(0,0);
        #endif

        //Metodos privados para el movimiento
        virtual void TeclaMoveMotors(char del, char atr, char der, char izq, char det, char spedMas, char spedMenos);

        //Si usamos arduino y algun modulo BlueThoot
        virtual void BTHMove(unsigned int recSeg, char del, char atr, char der, char izq, char det, char spedMas, char spedMenos);

    public:
        AutoRemotoBase(uint8_t velocidad, uint8_t receivePin = 0, uint8_t transmitPin = 0, MotorDriverType typeMotor = DRIVER_PWM_SEPARATE);

		/*Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER.
        Pero ahora, en este caso, los 2 motores primeros (que serian 2 llantas), seran los que se mueven
        hacia adelante*/
		virtual void Add4Motors(Motor RotIzq1, Motor RotDer1, Motor izq2, Motor der2);

        virtual void Camina(unsigned int recMillis = 1, char del = 'w', char atr = 's', char der = 'd', char izq = 'a', char det = 'x', char spedMas = 'q', char spedMenos = 'e', unsigned int activeTimeMillis = 0);
};