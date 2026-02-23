/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include "AutRem-SSS.hpp"

//AutRemSSS::
void AutRemSSS::AddMotors(Motor* Mtrs, uint8_t size){
    if(size < 4){
        DBG_PRINTLN("Pocos motores. Es Necesario mas de 4 Motores. Regresando");
        return;
    }else if((CantidadMotores + size) > MAXMOTORS){
        DBG_PRINTLN("Demaciados Motores. Es Necesario menos de 33 Motores. Regresando");
        return;
    }
    
    for(uint8_t i=CantidadMotores; i<CantidadMotores+size; i++) {
        Motores[i] = &Mtrs[i];
        SetMotor(Motores[i], Vel);
    }
    CantidadMotores += size;
}

void AutRemSSS::MDerIzq(Motor* M, uint8_t size, bool Der){
    //apagamos los motores de delante
    digitalWrite(M[0].L1,LOW);
    digitalWrite(M[0].L2,LOW);
    digitalWrite(M[1].L1,LOW);
    digitalWrite(M[1].L2,LOW);

    //Movemos el Servo dependiendo de a donde quiera ir
    servoControler.write( (Der ? (0):(180)) );

    DBG_VALUE_LN("Giramos hacia: ", (Der ? "derecha" : "izquierda"));
}

//Modificamos un poco
void AutRemSSS::BTHMove(unsigned int recSeg = 1, char del = 'W', char atr = 'S', char der ='D', char izq = 'A', char det = 'Z', char spedMas = 'Q', char spedMenos = 'E'){
    //Tomamos el tiempo en que llego
    startTime = millis();

    //Tomamos el recorido real a segundos
    recSeg *= 1000;

    //Movemos los motores
    TeclaMoveMotors(del,atr,der,izq,det,spedMas,spedMenos);

    //nos detenemos si el tiempo termino
    if((millis() - startTime) > recSeg){
        MStop(*Motores, CantidadMotores);
        servoControler.write(90);
    }
}

AutRemSSS::AutRemSSS(uint8_t pinServo, uint8_t velocidad, uint8_t receivePin = 0, uint8_t transmitPin = 0, MotorDriverType typeMotor = DRIVER_PWM_SEPARATE)
 :AutoRemotoBase(velocidad, receivePin, transmitPin, typeMotor){
    //Tomamos el pin para el servo y lo movemos 90-grados
    servoControler.attach(pinServo);
    servoControler.write(90);
    startTime = 0;
}