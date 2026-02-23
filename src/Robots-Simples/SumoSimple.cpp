/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include "SumoSimple.hpp"

//SumoSimple::

void SumoSimple::SimpleAccion(bool &accion, unsigned long &Time){
    accion = true;
    Time = millis();
}

void SumoSimple::MoverPorSUS(unsigned long &timer,unsigned long &timerUS, bool &atUsed, bool &usUsed){
    
    //si no esta en ataque
    if(!atUsed){
        for(uint8_t i=0; i<UltraSonicoCount; i++){

            //Si estamos en el US de delante y hay algo en el punto de ataque y aun no ataca, atacamos
            if(UltraSonicos[i].ID == 0 && UltraSonicos[i].Cerca){
                ConfigVelocidad(*Motores, CantidadMotores, Vel);
                MDelAtrs(*Motores, CantidadMotores, false);
                SimpleAccion(atUsed, timer);
                DBG_PRINTLN("Atacando");
            }

            //Si encontramos algo por atras giramos
            else if(UltraSonicos[i].ID == 1 && UltraSonicos[i].Cerca){
                MDerIzq(*Motores, CantidadMotores, RGiro);
                SimpleAccion(usUsed, timerUS);
                DBG_PRINTLN("Girando");
            }

            //Si encontramos algo por la izquierda giramos
            else if(UltraSonicos[i].ID == 2 && UltraSonicos[i].Cerca){
                MDerIzq(*Motores, CantidadMotores, false);
                SimpleAccion(usUsed, timerUS);
                DBG_PRINTLN("Girando a la izquierda");
            }

            //Si encontramos algo por la derecha giramos
            else if(UltraSonicos[i].ID == 3 && UltraSonicos[i].Cerca){
                MDerIzq(*Motores, CantidadMotores, true);
                SimpleAccion(usUsed, timerUS);
                DBG_PRINTLN("Girando a la derecha");
            }
        }
    }
    
    //si estaba girando y termino de girar
    if(usUsed && (millis() - TGiro) >= timerUS){
        DBG_PRINTLN("Giro Finalizado");
        usUsed = false;
        MDerIzq(*Motores, CantidadMotores, RGiro);
    }
}

void SumoSimple::MoverPorInfrarrojos(unsigned long &timer, bool &used){

    //Si hay sensores ultrasonicos o si los esta usando
    #if USE_IR == 1
        if(!used){
            for(uint8_t i=0; i<InfrarrojoCount; i++){

                //Si detecta el borde quiere decir que nos "Salimos"
                //si detecta por delante, nos movemos hacia atras
                if(Infrarrojos[i].ID == 0 && Infrarrojos[i].Estado == IR_ACTIVATE){
                    SimpleAccion(used, timer);
                    MDelAtrs(*Motores, CantidadMotores, false);
                    DBG_PRINTLN("Topamos con un borde delante, moviendo hacia Atras");
                }
                //si detecta por Atras, nos movemos hacia Adelante
                else if(Infrarrojos[i].ID == 1 && Infrarrojos[i].Estado == IR_ACTIVATE){
                    SimpleAccion(used, timer);
                    MDelAtrs(*Motores, CantidadMotores, true);
                    DBG_PRINTLN("Topamos con un borde Atras, moviendo hacia Delante");
                }
                //si detecta por la Izquierda, giramos hacia la derecha
                else if(Infrarrojos[i].ID == 2 && Infrarrojos[i].Estado == IR_ACTIVATE){
                    SimpleAccion(used, timer);
                    MDerIzq(*Motores, CantidadMotores, true);
                    DBG_PRINTLN("Topamos con un borde Izquierdo, Girando hacia la Derecha");
                }
                //si detecta por la Derecha, giramos hacia la Izquierda
                else if(Infrarrojos[i].ID == 3 && Infrarrojos[i].Estado == IR_ACTIVATE){
                    SimpleAccion(used, timer);
                    MDerIzq(*Motores, CantidadMotores, false);
                    DBG_PRINTLN("Topamos con un borde Derecho, Girando hacia la Izquierda");
                }
            }
        }
        else if( (millis() - timer) >= (TGiro/4) ){
            DBG_PRINTLN("Movimiento Finalizado");
            used = false;
            MDerIzq(*Motores, CantidadMotores, RGiro);
        }
    #endif
}


SumoSimple::SumoSimple(uint8_t Velocidad, uint8_t VelocidadGiro, uint8_t _DistAtaq, unsigned int TRecMiliSec,
    unsigned int TGiroMiliSec, MotorDriverType typeMotor = DRIVER_PWM_SEPARATE):
    SumoBase(Velocidad, VelocidadGiro, _DistAtaq, TRecMiliSec, TGiroMiliSec, typeMotor){}

//Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER
void SumoSimple::Add4Motors(Motor izq1, Motor der1, Motor izq2, Motor der2){
    //Verificamos que no se supere el limite de motores
    if (CantidadMotores + 4 > MAXMOTORS){
        DBG_PRINTLN("No se pueden agregar mas motores, se supero el limite establecido.");
        return;
    }
    //Agregamos los motores
    SetMotor(&izq1,Vel); Motores[CantidadMotores++] = &izq1;
    SetMotor(&der1,Vel); Motores[CantidadMotores++] = &der1;
    SetMotor(&izq2,Vel); Motores[CantidadMotores++] = &izq2;
    SetMotor(&der2,Vel); Motores[CantidadMotores++] = &der2;
}