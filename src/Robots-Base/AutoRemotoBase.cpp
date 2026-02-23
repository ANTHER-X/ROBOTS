/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include "AutoRemotoBase.hpp"

//AutoRemotoBase::

void AutoRemotoBase::TeclaMoveMotors(char del = 'W', char atr = 'S', char der ='D', char izq = 'A', char det = 'Z', char spedMas = 'Q', char spedMenos = 'E'){
    //dependiendo de la lectura, nos movemos o no
    if     (tecla == del) MDelAtrs(*Motores, CantidadMotores, true);
    else if(tecla == atr) MDelAtrs(*Motores, CantidadMotores, false);
    else if(tecla == der) MDerIzq(*Motores, CantidadMotores, true);
    else if(tecla == izq) MDerIzq(*Motores, CantidadMotores, false);
    else if(tecla == spedMas){
        Vel += 10;
        ConfigVelocidad(*Motores, CantidadMotores, Vel);
    }
    else if(tecla == spedMenos){
        Vel -= 10;
        ConfigVelocidad(*Motores, CantidadMotores, Vel);
    }
    else if(tecla == det) MStop(*Motores, CantidadMotores);
}

//Si usamos arduino y algun modulo BlueThoot
void AutoRemotoBase::BTHMove(unsigned int recSeg, char del = 'W', char atr = 'S', char der ='D', char izq = 'A', char det = 'Z', char spedMas = 'Q', char spedMenos = 'E'){
    //Tomamos el recorido real a segundos
    recSeg *= 1000000;

    //Movemos los motores
    TeclaMoveMotors(del,atr,der,izq,det,spedMas,spedMenos);
    
    //nos mantenemos en movimiento por NSeg
    delayMicroseconds(recSeg);

    //nos detenemos
    Robot::MStop(*Motores, CantidadMotores);
}

//Aqui podemos usar ya sea modulos BlueThoot de arduino como HC05 o el de ESP32
AutoRemotoBase::AutoRemotoBase(uint8_t velocidad, uint8_t HCreceivePin = 0, uint8_t HCtransmitPin = 0, MotorDriverType typeMotor = DRIVER_PWM_SEPARATE){
    Vel = velocidad;
    motorType = typeMotor;
    #if defined(ESP32)
        BTHESP.begin(115200);
        DBG_PRINTLN("BlueThoot de ESP32 Iniciado.");
    #else
        if(HCreceivePin < 1 || HCtransmitPin < 1) return;
        BTH = new SoftwareSerial(HCreceivePin, HCtransmitPin);
        BTH->begin(9600);
        DBG_PRINTLN("BlueThoot de Arduino Iniciado.");
    #endif
}

/*Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER.
Pero ahora, en este caso, los 2 motores primeros (que serian 2 llantas), seran los que se mueven
hacia adelante*/
void AutoRemotoBase::Add4Motors(Motor RotIzq1, Motor RotDer1, Motor izq2, Motor der2){

    //Verificamos que no se supere el limite de motores
    if(CantidadMotores + 4 > MAXMOTORS){
        DBG_PRINTLN("No se pueden agregar mas motores, se supero el limite establecido.");
        return;
    }

    //Agregamos los motores
    SetMotor(&RotIzq1,Vel); Motores[CantidadMotores++] = &RotIzq1;
    SetMotor(&RotDer1,Vel); Motores[CantidadMotores++] = &RotDer1;
    SetMotor(&izq2,Vel); Motores[CantidadMotores++] = &izq2;
    SetMotor(&der2,Vel); Motores[CantidadMotores++] = &der2;
}

void AutoRemotoBase::Camina(unsigned int recSeg = 2, char del = 'W', char atr = 'S', char der ='D', char izq = 'A', char det = 'Z', char spedMas = 'Q', char spedMenos = 'E', unsigned int activeTimeMillis = 0){
    //Si no hay motores o no hay BlueThoot no hacemos nada
    if(CantidadMotores == 0){
        DBG_PRINTLN("Sin motores. Regresando.");
        return;
    }
    //si usa el modulo de arduino
    #if defined(__AVR__)
        if(BTH == nullptr){
            DBG_PRINTLN("Sin BlueThoot. Regresando.");
            return;
        }
    #endif
    
    //en caso de que no esten inicializados, no se como hacerlo asi que al rato veo
    
    //Si es que hay motores, configuramos las variables iniciales
    unsigned int initTime = activeTimeMillis ? millis(): 0;//tiempo de inicio si es que agrega (default '0')

    //si si hay motores, nos movemos por medio del blueThoot
    do{
        //lo leemos dependiendo el BTH
        #if defined(ESP32) //ESP
            if(BTHESP.available()){
                tecla = BTHESP.read();
                BTHMove(recSeg,del,atr,der,izq,det,spedMas,spedMenos);
            }
        #else   //Arduino
            if(BTH->available()){
                tecla = BTH->read();
                BTHMove(recSeg,del,atr,der,izq,det,spedMas,spedMenos);
            }
        #endif
    //si no configura el tiempo se mantendra siempre, si si el bucle terminara cuando el tiempo se acabe
    }while( ( activeTimeMillis == 0 || (initTime > 0 && (millis() - initTime < activeTimeMillis))) );

    DBG_PRINTLN("Tiempo Agotado. Movimiento terminado.");
}