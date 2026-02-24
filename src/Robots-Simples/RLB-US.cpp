/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include "RLB-US.hpp"

void RLBUS::TomaDistanciaMayor(){
    //Tomamos datos
    DistDelante = ActivateUS(USDelante); delayMicroseconds(20);
    DistDerecha = ActivateUS(USDerecha); delayMicroseconds(20);
    DistIzquierda = ActivateUS(USIzquierda);
}


RLBUS::RLBUS(uint8_t velocidadRecta, uint8_t velocidadGiro, unsigned int timeGiro, unsigned int timeRec,
    UltraSonico _USDelante, UltraSonico _USDerecha, UltraSonico _USIzquierda, MotorDriverType typeMotor)
    : RLBase(velocidadRecta, velocidadGiro, timeGiro, timeRec, typeMotor){
    //Tomamos
    USDelante = _USDelante;
    USDerecha = _USDerecha;
    USIzquierda = _USIzquierda;
}