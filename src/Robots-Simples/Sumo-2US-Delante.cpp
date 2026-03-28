#include "Sumo-2US-Delante.hpp"

void Sumo2USDelante::AddUSs(uint8_t trigerLeft, uint8_t echoLeft, uint8_t trigerRight, uint8_t echoRight){
    if(ExistSUS(1) || ExistSUS(2)){
        DBG_PRINTLN("Los sensores ya ah sido agregados");
        return; //No hacemos nada si es que ya puso los pines de los IRs.
    }

    //Agregamos los USs
    AddSUS(0,trigerLeft, echoLeft);
    AddSUS(1,trigerRight, echoRight);
}
void Sumo2USDelante::AddIRsDelante(uint8_t IR1, uint8_t IR2){
    AddInfra(0, IR1);
    AddInfra(1, IR2);
}
void Sumo2USDelante::AddIrAtras(uint8_t pin){ AddInfra(2,pin);}


void Sumo2USDelante::MoverPorInfrarrojos(unsigned long &timer, bool &used){
    //Si hay IRs
    #if USE_IR == 1
        for(int i=0; i< InfrarrojoCount; i++){
            //Si el IR son los de adelante
            if((Infrarrojos[i].ID == 0 || Infrarrojos[i].ID == 1) && Infrarrojos[i].Estado == IR_ACTIVATE){
                DBG_PRINTLN("\n\nNOS SALIMOS!!!.\n\n");
                MDelAtrs(*Motores, CantidadMotores, false);
                timer = millis(); //iniciamos el temporizador de retroceso
                used = true;
            }
            //Si nos salimos por atras vamos hacia adelante
            else if(Infrarrojos[i].ID == 2 && Infrarrojos[i].Estado == IR_ACTIVATE){
                DBG_PRINTLN("\n\nCASI NOS SALIMOS, ANDANDO RECTO\n\n");
                MDelAtrs(*Motores, CantidadMotores, true);
                timer = millis(); //iniciamos el temporizador de retroceso
                used = true;
            }
        }
    #endif
}

void Sumo2USDelante::MoverPorSUS(unsigned long &timer,unsigned long &timerUS, bool &atUsed, bool &usUsed){
    for(int i=0; i<UltraSonicoCount; i++){
        //Si ambos estan cerca nos movemos hacia adelante
        if( (UltraSonicos[i].ID == 0 && UltraSonicos[i].Cerca) && (UltraSonicos[i].ID == 1 && UltraSonicos[i].Cerca) ){
            DBG_PRINTLN("\n\nATACANDO.\n\n");
            ConfigVelocidad(*Motores, CantidadMotores, Vel);
            MDelAtrs(*Motores, CantidadMotores, true);
            timer = millis(); //marcamos el inicio de la accion
            atUsed = true; //decimos que accionamos
        }
        //Si solo detecta el derecho nos vamos a la derecha
        else if(UltraSonicos[i].ID == 1 && UltraSonicos[i].Cerca){
            DBG_PRINTLN("\n\nGIRANDO DERECHA.\n\n");
            ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
            MDerIzq(*Motores, CantidadMotores, true);
            timer = millis(); //marcamos el inicio de la accion
            atUsed = true; //decimos que accionamos
        }
        //Si solo detecta el izquierdo nos vamos a la derecha
        else if(UltraSonicos[i].ID == 0 && UltraSonicos[i].Cerca){
            DBG_PRINTLN("\n\nGIRANDO IZQUIERDA.\n\n");
            ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
            MDerIzq(*Motores, CantidadMotores, false);
            timer = millis(); //marcamos el inicio de la accion
            atUsed = true; //decimos que accionamos
        }
        //Si no hay nada giramos
        else{
            DBG_PRINTLN("\n\nGIRANDO.\n\n");
            ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
            MDerIzq(*Motores, CantidadMotores, RGiro);
            timer = millis(); //marcamos el inicio de la accion
            atUsed = true; //decimos que accionamos
        }
    }

}