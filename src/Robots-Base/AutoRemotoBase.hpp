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
            SoftwareSerial *BTH = nullptr;
        #endif

        //Metodos privados para el movimiento

        virtual void TeclaMoveMotors(char del, char atr, char der, char izq, char det, char spedMas, char spedMenos);

        //Si usamos arduino y algun modulo BlueThoot
        virtual void BTHMove(unsigned int recSeg, char del, char atr, char der, char izq, char det, char spedMas, char spedMenos);

    public:
        AutoRemotoBase(uint8_t velocidad, uint8_t receivePin, uint8_t transmitPin, MotorDriverType typeMotor);
        /*~AutoRemotoBase(){
            #if defined(__AVR__)
                if(BTH != nullptr) delete BTH;
            #endif
        }*/
    
		/*Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER.
        Pero ahora, en este caso, los 2 motores primeros (que serian 2 llantas), seran los que se mueven
        hacia adelante*/
		virtual void AddMotors(std::vector<Motor> Mtrs);

		/*Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER.
        Pero ahora, en este caso, los 2 motores primeros (que serian 2 llantas), seran los que se mueven
        hacia adelante*/
		virtual void Add4Motors(Motor RotIzq1, Motor RotDer1, Motor izq2, Motor der2);

        virtual void Camina(unsigned int recSeg, char del, char atr, char der, char izq, char det, char spedMas, char spedMenos, unsigned int activeTimeMillis);
};