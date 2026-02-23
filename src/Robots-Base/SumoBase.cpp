/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include "SumoBase.hpp"

//SumoBase::


//metodos privados
//captura la distancia en CM
void SumoBase::MedirSUS(UltraSonico &US){
    digitalWrite(US.Pin[0], HIGH); //mando una senial de sonido
    delayMicroseconds(10);
    digitalWrite(US.Pin[0], LOW); //detengo la senial
    delayMicroseconds(5);
    Distcm = (pulseIn(US.Pin[1], HIGH) / 58.2);//medira en centimetros
    
    DBG_VALUE("Ultrasonico en pines: ", US.Pin[0]);
    DBG_VALUE(", ", US.Pin[1]);
    DBG_VALUE_LN(". La distancia tomada es de: ", Distcm);
        
    //verifica la distancia de esquivado
    if(Distcm <= DistAtaq && Distcm > 0){//si esta muy cerca
        //Serial.println("Encontramos algo muy cerca");
        US.Cerca = true;//activamos el cerca
    }
    //si no todo es false
    else US.Cerca = false;
}

int SumoBase::TomarDistUS(UltraSonico &US){
    MedirSUS(US);
    return US.Cerca;
}

void SumoBase::UsarAllSUS(){
    for(uint8_t i=0; i<UltraSonicoCount; i++)
        MedirSUS(UltraSonicos[i]);
}

//toma el estado de los infrarrojos
void SumoBase::ActivaInfrarrojo(Infrarrojo &INF){
    #if USE_IR == 1
        INF.Estado = digitalRead(INF.Pin) == LOW;
        DBG_VALUE("Pin Usado: ", INF.Pin);
        DBG_VALUE_LN(". Estado tomado: ", INF.Estado);
    #endif
}
bool SumoBase::UsaInfrarrojo(Infrarrojo &INF){
    #if USE_IR == 1
        ActivaInfrarrojo(INF);
        return INF.Estado;
    #else 
        return false;
    #endif
}
void SumoBase::UsaAllInfrarrojo(){
    #if USE_IR == 1
        for(uint8_t i=0; i<InfrarrojoCount; i++)
            ActivaInfrarrojo(Infrarrojos[i]);
    #endif
}


void SumoBase::MoverPorSUS(unsigned long &timer,unsigned long &timerUS, bool &atUsed, bool &usUsed){
    for(uint8_t i=0; i<UltraSonicoCount; i++){

        //Si estamos en el US de delante y hay algo en el punto de ataque y aun no ataca, atacamos
        if(UltraSonicos[i].ID == 0 && UltraSonicos[i].Cerca && !atUsed){
            DBG_PRINTLN("\n\nATACANDO.\n\n");
            ConfigVelocidad(*Motores, CantidadMotores, Vel);
            MDelAtrs(*Motores, CantidadMotores, true);
            timer = millis(); //marcamos el inicio del ataque
            atUsed = true; //decimos que atacamos
        }
    }

    //si esta atacando y finalizo el tiempo del ataque, terminamos el ataque
    if(atUsed && (millis() - timer) >= TRec){
        DBG_PRINTLN("\n\nATAQUE FINALIZADO.\n\n");
        atUsed = false; //terminamos el ataque
        ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
        MDerIzq(*Motores, CantidadMotores, RGiro);
        //MStop(Motores[0], CantidadMotores);
    }
}


void SumoBase::MoverPorInfrarrojos(unsigned long &timer, bool &used){
    #if USE_IR == 1
        for(uint8_t i=0; i<InfrarrojoCount; i++){
            
            //si detecta el borde
            if(Infrarrojos[i].ID == 0 && Infrarrojos[i].Estado == IR_ACTIVATE){
                DBG_PRINTLN("\n\nNOS SALIMOS!!!.\n\n");
                MDelAtrs(*Motores, CantidadMotores, false);//atras
                timer = millis(); //iniciamos donde comenzo hacia atras
                used = true;//decimos que se mueve hacia atras
            }
        }

        //si ya pasaron Nseg moviendose hacia atras
        if(used && (millis() - timer) >= TRec){
            DBG_PRINTLN("\n\nMOVIMIENTO DE IR TERMINADO.\n\n");
            used = false; //decimos que ya no movemos hacia atras
        }
    #endif
}


void SumoBase::FinAtaque(bool &ataque, bool &infAccion, unsigned long timeInfAccion, unsigned long timeAtaque){
    //si ya no hay ataque y ya no vamos a retroceder (o que se haya usado algun infrarrojo) volvemos a girar
    #if USE_IR == 1
        if(!ataque && infAccion && (millis() - timeInfAccion) > TRec){
            ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
            MDerIzq(*Motores, CantidadMotores, RGiro);
            infAccion = false;
            ataque = false;
            DBG_PRINTLN("Buscando");
        }
    #endif

    //si no detectamos la barrera y ya paso el tiempo de accion del ataque, detenemos el ataque
    if(ataque && (millis() - timeAtaque) > TRec){
        ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
        MDerIzq(*Motores, CantidadMotores, RGiro);
        ataque = false;
        DBG_PRINTLN("\n\nATAQUE FINALIZADO\n\n");
    }
}

void SumoBase::Ataque(bool &ataque, bool &infUsed, unsigned long &timeAtaque, unsigned long &timeInf){
    
    //si aun esta atacando y topamos con la barrera detenemos el ataque y retrocedemos
    #if USE_IR == 1
        if(ataque && millis() - timeAtaque > TRec && Infrarrojos[0].Estado == true){
            ConfigVelocidad(*Motores, CantidadMotores, Vel);
            MDelAtrs(*Motores, CantidadMotores,false);
            ataque = false;
            infUsed = true;
            timeInf = millis();
            DBG_PRINTLN("\n\nATACANDO... PERO NOS SALIMOS!!!\n\n");
        }
    #endif
}


//Los Ultrasonicos para los ojos
void SumoBase::AddSUS(uint8_t id, uint8_t triger, uint8_t echo){
    if(ExistSUS(id) || UltraSonicoCount > MAXSUS){
        DBG_VALUE("El sensor ultrasonico ya existe o se supero el limite establecido. Pin triger:", triger);
        DBG_VALUE_LN(". Pin Echo: ", echo);
        return; //si ya existe el ID, no hacemos nada
    }
    DBG_PRINTLN("Sensor US agregado");
    UltraSonico US = {0};
    US.ID = id;
    US.Pin[0] = triger; pinMode(US.Pin[0], OUTPUT);
    US.Pin[1] = echo; pinMode(US.Pin[1], INPUT);

    UltraSonicoCount++;
    UltraSonicos[UltraSonicoCount-1] = US;
}

//Define los infrarrojos
void SumoBase::AddInfra(uint8_t id, uint8_t pin){
    #if USE_IR == 1
        if(ExistIR(id) || InfrarrojoCount > MAXIR){
            DBG_VALUE_LN("El sensor infrarrojo ya existe o se supero el maximo. Pin:", pin);
            return; //si ya existe el ID, no hacemos nada
        }

        //Seteamos el nuevo sensor
        DBG_PRINTLN("Sensor INF agregado");
        Infrarrojo IF = {0};
        IF.ID = id;
        IF.Pin = pin; pinMode(IF.Pin, INPUT);

        //Lo agregamos a
        InfrarrojoCount++;
        Infrarrojos[InfrarrojoCount-1] = IF;
    #endif
}

bool SumoBase::ExistIR(int ID){

    #if USE_IR == 1
        for(uint8_t i=0; i<InfrarrojoCount; i++){
            if(Infrarrojos[i].ID == ID) return true;
        }
    #endif

    return false;
}

bool SumoBase::ExistSUS(int ID){
    for(uint8_t i=0; i<UltraSonicoCount; i++){
        if(UltraSonicos[i].ID == ID) return true;
    }
    return false;
}

SumoBase::SumoBase(uint8_t Velocidad, uint8_t VelocidadGiro, uint8_t _DistAtaq, unsigned int TRecMiliSec, unsigned int TGiroMiliSec, MotorDriverType typeMotor = DRIVER_PWM_SEPARATE){
    
    TGiro = TGiroMiliSec;
    TRec = TRecMiliSec;
    Vel = Velocidad;
    VelGiro = VelocidadGiro;
    DistAtaq = _DistAtaq;
    motorType = typeMotor;
}

void SumoBase::AddInfraAdelante(uint8_t pin){ AddInfra(0,pin);}
void SumoBase::AddSUSAdelante(uint8_t triger, uint8_t echo){ AddSUS(0, triger, echo);}

void SumoBase::Add2Motors(Motor L1, Motor L2){
    //Verificamos que no se supere el limite de motores
    if (CantidadMotores + 2 > MAXMOTORS){
        DBG_PRINTLN("No se pueden agregar mas motores, se supero el limite establecido.");
        return;
    }

    //Agregamos los motores
    SetMotor(&L1,Vel); Motores[CantidadMotores++] = &L1;
    SetMotor(&L2,Vel); Motores[CantidadMotores++] = &L2;
}

void SumoBase::Camina(unsigned int activeTimeMillis = 0){
    if(CantidadMotores != 0){

        //Movimiento aleatorio
        RGiro = random(0,2);
        
        //variables locales que se que solo se inician minimo una vez
        
        //para accionar los Infra
        unsigned long InicioAtras = 0;
        bool Atras = false;

        //Para accionar los USU
        unsigned long InicioAtaque = 0, usAccion = 0;
        bool ataque = false, usDetected = false;
        unsigned int initTime = activeTimeMillis ? millis(): 0;

        ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
        MDerIzq(*Motores, CantidadMotores ,RGiro); //giramos

        do{

            //comenzamos a contar

            //Movimiento completo del robot
            UsaAllInfrarrojo();
            MoverPorInfrarrojos(InicioAtras, Atras);
            UsarAllSUS();
            Extras();
            MoverPorSUS(InicioAtaque, usAccion, ataque, usDetected);
            Ataque(ataque, Atras, InicioAtaque, InicioAtras);
            FinAtaque(ataque, Atras, InicioAtras, InicioAtaque);

        }while( ( activeTimeMillis == 0 || (initTime > 0 && (millis() - initTime < activeTimeMillis))) );
    }
}