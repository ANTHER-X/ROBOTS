//Incluimos el Robot base, esto para poder mover nuestros motores
#include "../Robots-Base/RLBase.hpp"
#include <Servo.h>

#pragma once

/*Como no tengo idea de como es que se haria uno de estos, hare solo la base
de 2 ya funcionales pero con distinto.

En esta ocacion tendra una cabeza que se mueve y captura el movimiento*/
class RLBServo : public RLBase{

    protected:
    
    //Para capturar los movimientos
    UltraSonico US;
    //Para mover el US
    Servo servo;

    /*Metodos privados que nos ayudan a configurar el movimiento.
    Vamos a retornar un numero dependiendo de que lado es el mayor.
    0->Izqiuerda, 1->Centro, 2->Derecha*/
    virtual void TomaDistanciaMayor() override;

    public:
    //para tener el Servo
    RLBServo(uint8_t velocidadRecta, uint8_t velocidadGiro, unsigned int timeGiro, unsigned int timeRec, UltraSonico us, uint8_t pinServo, MotorDriverType typeMotor);

};