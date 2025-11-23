#include "RLBase.hpp"

//RLBase::

void RLBase::MoveDerIzq(bool derIzq){
    MDerIzq(Motores, derIzq);
    delay(TGiro);
    MDelAtrs(Motores, true);
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

RLBase::RLBase(uint8_t velocidadRecta, uint8_t velocidadGiro, unsigned int timeGiro, unsigned int timeRec){
    TRec = timeRec;
    TGiro = timeGiro;
    VRecta = velocidadRecta;
    VGiro = velocidadGiro;

    DistDerecha = DistIzquierda = 1;
    DistDelante = 2;
}

/*Agregamos motores, puede agregar mas pero todas con la misma Confg*/
void RLBase::AddMotors(std::vector<Motor> Mtrs) {
    Motores = Mtrs;
    for(unsigned int i=0; i<Motores.size(); i++) SetMotor(Motores[i], VRecta); 
}

//Metemos motores, asi ira la configuracion, primero izq, luego derecha
void RLBase::Add4Motors(Motor izq1, Motor der1, Motor izq2, Motor der2){
    SetMotor(izq1,VRecta); Motores.push_back(izq1);
    SetMotor(der1,VRecta); Motores.push_back(der1);
    SetMotor(izq2,VRecta); Motores.push_back(izq2);
    SetMotor(der2,VRecta); Motores.push_back(der2);
}

//Usamos este metodo para movernos, Pienso yo que asi se debe mover asi que de aqui es lo mismo para los RLB
void RLBase::Camina(){
    //Si no hay motores, no hacemos nada
    if(Motores.size() <= 0) return;

    //Tomamos las distancias
    uint8_t Movimiento = RetornaDistanciaMayor();

    //Nos movemos de forma ideterminada en esta funcion.
    bool OnMovement = false;
    unsigned long Time;

    while(1){
        
        //Si no estamos moviendonos, lo hacemos
        if(!OnMovement){    
            //Centro
            if(Movimiento == 1) MDelAtrs(Motores, true);
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
            OnMovement = false;
            MStop(Motores);
            Movimiento = RetornaDistanciaMayor();
        }
    }
}