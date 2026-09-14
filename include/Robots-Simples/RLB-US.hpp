/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

//Incluimos lo necesario
#include "../Robots-Base/RLBase.hpp"
#include <Servo.h>

#pragma once

class RLBUS : public RLBase{

    protected:

    UltraSonico USDelante, USDerecha, USIzquierda;

    //Metodos para la toma de estadisticas
    virtual void TomaDistanciaMayor() override;

    public:
    RLBUS(uint8_t velocidadRecta, uint8_t velocidadGiro, unsigned int timeGiro, unsigned int timeRec,
        UltraSonico _USDelante, UltraSonico _USDerecha, UltraSonico _USIzquierda, MotorDriverType typeMotor = DRIVER_PWM_SEPARATE);

};