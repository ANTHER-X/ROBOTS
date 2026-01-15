#include "SumoSimple.hpp"

//SumoSimple::

void SumoSimple::SimpleAccion(bool &accion, unsigned long &Time){
    accion = true;
    Time = millis();
}

void SumoSimple::MoverPorSUS(unsigned long &timer,unsigned long &timerUS, bool &atUsed, bool &usUsed){
    
    //si no esta en ataque
    if(!atUsed){
        for(unsigned int i=0; i<UltraSonicos.size(); i++){

            //Si estamos en el US de delante y hay algo en el punto de ataque y aun no ataca, atacamos
            if(UltraSonicos[i].ID == 0 && UltraSonicos[i].Cerca){
                ConfigVelocidad(Motores, Vel);
                MDelAtrs(Motores,true);
                SimpleAccion(atUsed, timer);
                DBG_PRINTLN("Atacando");
            }

            //Si encontramos algo por atras giramos
            else if(UltraSonicos[i].ID == 1 && UltraSonicos[i].Cerca){
                MDerIzq(Motores, RGiro);
                SimpleAccion(usUsed, timerUS);
                DBG_PRINTLN("Girando");
            }

            //Si encontramos algo por la izquierda giramos
            else if(UltraSonicos[i].ID == 2 && UltraSonicos[i].Cerca){
                MDerIzq(Motores,false);
                SimpleAccion(usUsed, timerUS);
                DBG_PRINTLN("Girando a la izquierda");
            }

            //Si encontramos algo por la derecha giramos
            else if(UltraSonicos[i].ID == 3 && UltraSonicos[i].Cerca){
                MDerIzq(Motores,true);
                SimpleAccion(usUsed, timerUS);
                DBG_PRINTLN("Girando a la derecha");
            }
        }
    }
    
    //si estaba girando y termino de girar
    if(usUsed && (millis() - TGiro) >= timerUS){
        DBG_PRINTLN("Giro Finalizado");
        usUsed = false;
        MDerIzq(Motores, RGiro);
    }
}

void SumoSimple::MoverPorInfrarrojos(unsigned long &timer, bool &used){

    //Si hay sensores ultrasonicos o si los esta usando
    #if USE_IR == 1
        if(!used){
            for(unsigned int i=0; i<Infrarrojos.size(); i++){

                //Si detecta el borde quiere decir que nos "Salimos"
                //si detecta por delante, nos movemos hacia atras
                if(Infrarrojos[i].ID == 0 && Infrarrojos[i].Estado){
                    SimpleAccion(used, timer);
                    MDelAtrs(Motores, false);
                    DBG_PRINTLN("Topamos con un borde delante, moviendo hacia Atras");
                }
                //si detecta por Atras, nos movemos hacia Adelante
                else if(Infrarrojos[i].ID == 1 && Infrarrojos[i].Estado){
                    SimpleAccion(used, timer);
                    MDelAtrs(Motores, true);
                    DBG_PRINTLN("Topamos con un borde Atras, moviendo hacia Delante");
                }
                //si detecta por la Izquierda, giramos hacia la derecha
                else if(Infrarrojos[i].ID == 2 && Infrarrojos[i].Estado){
                    SimpleAccion(used, timer);
                    MDerIzq(Motores, true);
                    DBG_PRINTLN("Topamos con un borde Izquierdo, Girando hacia la Derecha");
                }
                //si detecta por la Derecha, giramos hacia la Izquierda
                else if(Infrarrojos[i].ID == 3 && Infrarrojos[i].Estado){
                    SimpleAccion(used, timer);
                    MDerIzq(Motores, false);
                    DBG_PRINTLN("Topamos con un borde Derecho, Girando hacia la Izquierda");
                }
            }
        }
        else if( (millis() - timer) >= (TGiro/4) ){
            DBG_PRINTLN("Movimiento Finalizado");
            used = false;
            MDerIzq(Motores, RGiro);
        }
    #endif
}


SumoSimple::SumoSimple(uint8_t Velocidad, uint8_t VelocidadGiro, uint8_t _DistAtaq, unsigned int TRecMiliSec,
    unsigned int TGiroMiliSec, MotorDriverType typeMotor = DRIVER_PWM_SEPARATE):
    SumoBase(Velocidad, VelocidadGiro, _DistAtaq, TRecMiliSec, TGiroMiliSec, typeMotor){}

//Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER
void SumoSimple::Add4Motors(Motor izq1, Motor der1, Motor izq2, Motor der2){
    SetMotor(izq1,Vel); Motores.push_back(izq1);
    SetMotor(der1,Vel); Motores.push_back(der1);
    SetMotor(izq2,Vel); Motores.push_back(izq2);
    SetMotor(der2,Vel); Motores.push_back(der2);
}



/*

DADO QUE SE CAMBIO DE ENFOQUE, ESTO YA NO SE USARA PERO LO DEJO EN CASO DE QUE A ALGUIEN LE
INTERESE O QUIERA CAMBIAR A LA FORMA ORIGINAL
private:

public:
void SumoSimple::Camina(unsigned int TimeMinuts = -1){

    //si no tiene motores no hacemos nadaS
    if(Motores.size() == 0) return;

    SensoresBusquedaSimpleSumo SBSS = {
        TomaInfrarrojoByID(0), TomaInfrarrojoByID(1), TomaInfrarrojoByID(2), TomaInfrarrojoByID(3),
        TomaUltrasonicoByID(0), TomaUltrasonicoByID(1), TomaUltrasonicoByID(2), TomaUltrasonicoByID(3) 
    };

    //variables locales utiles
    unsigned long Timer = millis();

    unsigned long TAtaque, TInfEsqu, TSUSGiro;
    bool EnAtaque = false, EnRetroseso = false, infEsquiv = false, SUSGiros = false;


    //Giramos si solo tenemos el sensor US de adelnte
    if(SBSS.susAtras == nullptr && SBSS.susDerecha == nullptr && SBSS.susIzqueirda == nullptr && SBSS.susDelante != nullptr) MDerIzq(Motores, RGiro);
    
    //buscamos
    while(1){
        
        //para controlar el temporizador de actividad
        if(TimeMinuts > 0 && (millis() - Timer) >= (TimeMinuts*60000)) return;

        //Si estamos buascando, revisamos los demas sensores
        if(!SUSGiros && !EnAtaque && !EnRetroseso && !infEsquiv){
                
            //verificamos el sensor US de atras
            if(SBSS.susAtras != nullptr && TomarDistUS(SBSS.susAtras) <= DistAtaq){
                MDerIzq(Motores, RGiro);
                GiraCompruebaSensor(SUSGiros, TSUSGiro);
            }

            //Verificamos el sensor US de la derecha
            if(SBSS.susDerecha != nullptr && TomarDistUS(SBSS.susDerecha) <= DistAtaq){
                MDerIzq(Motores, false);
                GiraCompruebaSensor(SUSGiros, TSUSGiro);
            }
                
            //Verificamos el sensor US de la Izquierda
            if(SBSS.susIzqueirda != nullptr && TomarDistUS(SBSS.susIzqueirda) <= DistAtaq){
                MDerIzq(Motores, true);
                GiraCompruebaSensor(SUSGiros, TSUSGiro);
            }

        }

        //Si el robot esta girando gracias a los sensores ultrasonicos y el tiempo de giro se termino, paramos
        if(SUSGiros && (millis() - TSUSGiro) >= TGiro){
            MDelAtrs(Motores,true);
            SUSGiros = false;
        }



        //si no estamos atacando y si encontramos algo a que atacar
        if(SBSS.susDelante != nullptr && TomarDistUS(SBSS.susDelante) <= DistAtaq && !SUSGiros && !EnAtaque && !EnRetroseso && !infEsquiv){
            MDelAtrs(Motores, true);//nos movemos hacia adelante y atacamos
            EnAtaque = true;
            TAtaque = millis();
        }

        //si mientras estamos atacando, topamos con el borde
        else if(EnAtaque && SBSS.infDelante != nullptr && UsaInfrarrojo(SBSS.infDelante)){
            MDelAtrs(Motores, false);//nos movemos hacia atras
            EnAtaque = false;
            EnRetroseso = true;
            TInfEsqu = millis();
        }

        //O si termino el ataque o si estaba retroseciendo, volvemos a buscar
        else if((EnAtaque && (millis() - TAtaque) > (TRec/8)) || (EnRetroseso && (millis() - TInfEsqu) >= (TRec/12))){
            MDerIzq(Motores, RGiro);
            EnAtaque = false;
            EnRetroseso = false;
        }

        

        //si esta buscando verificamos que no nos salgamos del borde
        if(TomarDistUS(SBSS.susDelante) > DistAtaq && !EnAtaque && !EnRetroseso && !SUSGiros){
        
            //si detecta que nos estamos saliendo por atras
            if(SBSS.infAtras != nullptr && UsaInfrarrojo(SBSS.infAtras) && !infEsquiv){
                MDelAtrs(Motores, true);// nos movemos hacia adelante
                GiraCompruebaSensor(infEsquiv, TInfEsqu);
            }
                
            //si nos salimos por la dercha, damos vuelta contraria
            if(SBSS.infDerecha != nullptr && UsaInfrarrojo(SBSS.infDerecha) && !infEsquiv){
                MDerIzq(Motores,false);
                GiraCompruebaSensor(infEsquiv, TInfEsqu);
            }
            //si nos salimos por la Izquieda, damos vuelta contraria
            if(SBSS.infIzquierda != nullptr && UsaInfrarrojo(SBSS.infIzquierda) && !infEsquiv){
                MDerIzq(Motores,true);
                GiraCompruebaSensor(infEsquiv, TInfEsqu);
            }

            //Si ya no nos estamos saliendo, volvemos a buscar
            if(infEsquiv && (millis() - TInfEsqu) > (TGiro/12)){
                MDerIzq(Motores, RGiro);
                infEsquiv = false;
            }

        }

    }

}*/