/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include "RLBase.hpp"

//RLBase::

void RLBase::MoveDerIzq(bool derIzq){
    MDerIzq(*Motores, CantidadMotores, derIzq);
    delay(TGiro);
    MDelAtrs(*Motores, CantidadMotores, true);
}

/*Metodos privados que nos ayudan a configurar el movimiento.
Vamos a retornar un numero dependiendo de que lado es el mayor.
0->Izqiuerda, 1->Centro, 2->Derecha*/
uint8_t RLBase::RetornaDistanciaMayor(){

    TomaDistanciaMayor();

    //"auxMayorDist" es un auxiliar para tomar la distancia mayor
    auxMayorDist = DistDerecha;

    //Vemos cual es mayor
    if(DistDelante >= auxMayorDist) auxMayorDist = DistDelante;
    else if(DistIzquierda >= auxMayorDist) auxMayorDist = DistIzquierda;
    
    //Damos la distancia mayor
    if(auxMayorDist == DistIzquierda) return 0;
    else if(auxMayorDist == DistDelante) return 1;
    else return 2;
}

RLBase::RLBase(uint8_t velocidadRecta, uint8_t velocidadGiro, unsigned int timeGiro, unsigned int timeRec, MotorDriverType typeMotor){
    TRec = timeRec;
    TGiro = timeGiro;
    VRecta = velocidadRecta;
    VGiro = velocidadGiro;
    motorType = typeMotor;

    DistDerecha = DistIzquierda = 1;
    DistDelante = 2;
}

//Metemos motores, asi ira la configuracion, primero izq, luego derecha
void RLBase::Add4Motors(Motor izq1, Motor der1, Motor izq2, Motor der2){

    if(CantidadMotores + 4 > MAXMOTORS){
        DBG_PRINTLN("No se pueden agregar mas motores, se supero el limite establecido.");
        return;
    }

    //Agregamos los motores
    SetMotor(&izq1,VRecta); Motores[CantidadMotores++] = &izq1;
    SetMotor(&der1,VRecta); Motores[CantidadMotores++] = &der1;
    SetMotor(&izq2,VRecta); Motores[CantidadMotores++] = &izq2;
    SetMotor(&der2,VRecta); Motores[CantidadMotores++] = &der2;
}

//Usamos este metodo para movernos, Pienso yo que asi se debe mover asi que de aqui es lo mismo para los RLB
void RLBase::Camina(unsigned int activeTimeMillis){
    //Si no hay motores, no hacemos nada
    if(CantidadMotores < 0){
        DBG_PRINTLN("Sin motores. Regresando.");
        return;
    }

    //Tomamos las distancias
    uint8_t Movimiento = RetornaDistanciaMayor();
    DBG_VALUE_LN("Distancia mayor tomada, retorno: ", Movimiento);

    //Nos movemos de forma ideterminada en esta funcion.
    bool OnMovement = false;
    unsigned long Time;
    unsigned int initTime = activeTimeMillis ? millis(): 0;

    do{
        
        //Si no estamos moviendonos, lo hacemos
        if(!OnMovement){    

            DBG_PRINTLN("\n\nMoviendo.\n\n");

            //Centro
            if(Movimiento == 1) MDelAtrs(*Motores, CantidadMotores, true);
            //Izquierda
            else if(Movimiento == 0) MoveDerIzq(true);
            //Derecha si no hay mas
            else MoveDerIzq(false);

            //En este punto, es obio que nos tenemos que mover, asi que lo hacemos
            Time = millis();
            OnMovement = true;
        }
        //Si se esta moviendo y termino su tiempo, nos detenemos y volvemos a tomar tiempos
        else if( (millis() - Time) > TRec){
            
            DBG_PRINTLN("\n\nMoviento terminado.\n\n");

            OnMovement = false;
            MStop(*Motores, CantidadMotores);
            Movimiento = RetornaDistanciaMayor();
        }
    }while( ( activeTimeMillis == 0 || (initTime > 0 && (millis() - initTime < activeTimeMillis))) );
}