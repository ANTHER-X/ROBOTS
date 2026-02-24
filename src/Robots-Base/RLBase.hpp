/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

//Incluimos el Robot base, esto para poder mover nuestros motores
#include "Robot.hpp"
#include "../Dependencias/Utilidades.hpp"

#pragma once

class RLBase : public Robot{

    protected:
    
    //Datos principales para guardar los datos del movimiento
    unsigned int DistDerecha, DistIzquierda, DistDelante, auxMayorDist, TGiro, TRec;
    uint8_t VRecta, VGiro;

    //no incluimos nada ya que no es necesario, eso lo haran las clases hijas
    inline virtual void TomaDistanciaMayor(){};

    /*Metodos privados que nos ayudan a configurar el movimiento.
    Vamos a retornar un numero dependiendo de que lado es el mayor.
    0->Izqiuerda, 1->Centro, 2->Derecha*/
    virtual uint8_t RetornaDistanciaMayor();

    //este metodo hace que gire cierto tiempo y luego camine
    virtual void MoveDerIzq(bool derIzq);

    public:
    RLBase(uint8_t velocidadRecta, uint8_t velocidadGiro, unsigned int timeGiro, unsigned int timeRec, MotorDriverType typeMotor = DRIVER_PWM_SEPARATE);

    //Metemos motores, asi ira la configuracion, primero izq, luego derecha
    virtual void Add4Motors(Motor izq1, Motor der1, Motor izq2, Motor der2);

    //Usamos este metodo para movernos, Pienso yo que asi se debe mover asi que de aqui es lo mismo para los RLB
    virtual void Camina(unsigned int activeTimeMillis = 0);

};