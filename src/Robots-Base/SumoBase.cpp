#include "SumoBase.hpp"

//SumoBase::


//metodos privados
//captura la distancia en CM
void SumoBase::MedirSUS(UltraSonico &US){
    digitalWrite(US.Pin[0], HIGH); //mando una senial de sonido
    delayMicroseconds(100);
    digitalWrite(US.Pin[0], LOW); //detengo la senial
    delayMicroseconds(50);
    Distcm = (pulseIn(US.Pin[1], HIGH) / 58.2);//medira en centimetros
        
    Serial.print("La distancia tomada es de: ");
    Serial.println(Distcm);
        
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
    for(unsigned int i=0; i<UltraSonicos.size(); i++)
        MedirSUS(UltraSonicos[i]);
}


//toma el estado de los infrarrojos
void SumoBase::ActivaInfrarrojo(Infrarrojo &INF){ INF.Estado = digitalRead(INF.Pin) == LOW;}
bool SumoBase::UsaInfrarrojo(Infrarrojo &INF){
    ActivaInfrarrojo(INF);
    return INF.Estado;
}
void SumoBase::UsaAllInfrarrojo(){
    for(unsigned int i=0; i<Infrarrojos.size(); i++)
        ActivaInfrarrojo(Infrarrojos[i]);
}



void SumoBase::MoverPorSUS(unsigned long &timer,unsigned long &timerUS, bool &atUsed, bool &usUsed){
    for(unsigned int i=0; i<UltraSonicos.size(); i++){

        //Si estamos en el US de delante y hay algo en el punto de ataque y aun no ataca, atacamos
        if(UltraSonicos[i].ID == 0 && UltraSonicos[i].Cerca && !atUsed){
            ConfigVelocidad(Motores, Vel);
            MDelAtrs(Motores,true);
            timer = millis(); //marcamos el inicio del ataque
            atUsed = true; //decimos que atacamos
            Serial.println("Atacando");
        }
    }

    //si esta atacando y finalizo el tiempo del ataque, terminamos el ataque
    if(atUsed && (millis() - timer) >= TRec){
        Serial.println("Ataque finalizado");
    atUsed = false; //terminamos el ataque
        ConfigVelocidad(Motores, VelGiro);
        MDerIzq(Motores, RGiro);
    }
}

void SumoBase::MoverPorInfrarrojos(unsigned long &timer, bool &used){
    for(unsigned int i=0; i<Infrarrojos.size(); i++){
        
        //si detecta el borde
        if(Infrarrojos[i].ID == 0){
            Serial.println("Nos salimos!!!");
            MDelAtrs(Motores,false);//atras
            timer = millis(); //iniciamos donde comenzo hacia atras
            used = true;//decimos que se mueve hacia atras
        } 
    }
    
    //si ya pasaron Nseg moviendose hacia atras
    if(used && (millis() - timer) >= TRec) used = false;//decimos que ya no movemos hacia atras
}


void SumoBase::FinAtaque(bool &ataque, bool &infAccion, unsigned long timeInfAccion, unsigned long timeAtaque){
    //si ya no hay ataque y ya no vamos a retroceder (o que se haya usado algun infrarrojo) volvemos a girar
    if(!ataque && infAccion && (millis() - timeInfAccion) > TRec){
        ConfigVelocidad(Motores, VelGiro);
        MDerIzq(Motores,RGiro);
        infAccion = false;
        ataque = false;
        Serial.println("Buscando");
    }

    //si no detectamos la barrera y ya paso el tiempo de accion del ataque, detenemos el ataque
    if(ataque && (millis() - timeAtaque) > TRec){
        ConfigVelocidad(Motores, VelGiro);
        MDerIzq(Motores,RGiro);
        ataque = false;
        Serial.println("Ataque finalizado");
    }
}

void SumoBase::Ataque(bool &ataque, bool &infUsed, unsigned long &timeAtaque, unsigned long &timeInf){
    //si aun esta atacando y topamos con la barrera detenemos el ataque y retrocedemos
    if(ataque && millis() - timeAtaque > TRec && Infrarrojos[0].Estado == true){
        ConfigVelocidad(Motores, Vel);
        MDelAtrs(Motores,false);
        ataque = false;
        infUsed = true;
        timeInf = millis();
        Serial.println("Atacando... Pero nos salimos!!!");
    }
}



//Los Ultrasonicos para los ojos
void SumoBase::AddSUS(uint8_t id, uint8_t triger, uint8_t echo){
    if(TomaUltrasonicoByID(id) != nullptr) return; //si ya existe el ID, no hacemos nada
    Serial.println("Sensor US agregado");
    UltraSonico US = {0};
    US.ID = id;
    US.Pin[0] = triger; pinMode(US.Pin[0], OUTPUT);
    US.Pin[1] = echo; pinMode(US.Pin[1], INPUT);

    UltraSonicos.push_back(US);
}

//Define los infrarrojos
void SumoBase::AddInfra(uint8_t id, uint8_t pin){
    if(TomaInfrarrojoByID(id) != nullptr) return; //si ya existe el ID, no hacemos nada
    Serial.println("Sensor INF agregado");
    Infrarrojo IF = {0};
    IF.ID = id;
    IF.Pin = pin; pinMode(IF.Pin, INPUT);
}

Infrarrojo *SumoBase::TomaInfrarrojoByID(int ID){
    Infrarrojo *infraPTR = nullptr;
    auto itinfraPTR = std::find_if(Infrarrojos.begin(), Infrarrojos.end(), [ID](const Infrarrojo &inf){ return inf.ID == ID;});

    if(itinfraPTR != Infrarrojos.end()) infraPTR = &(*itinfraPTR);

    return infraPTR;
}

UltraSonico *SumoBase::TomaUltrasonicoByID(int ID){
    UltraSonico *susPTR = nullptr;
    auto itsusPTR = std::find_if(UltraSonicos.begin(), UltraSonicos.end(), [ID](const UltraSonico &SUS){ return SUS.ID == ID;});

    if(itsusPTR != UltraSonicos.end()) susPTR = &(*itsusPTR);

    return susPTR;
}

SumoBase::SumoBase(uint8_t Velocidad, uint8_t VelocidadGiro, uint8_t _DistAtaq, unsigned int TRecMiliSec, unsigned int TGiroMiliSec){
    
    TGiro = TGiroMiliSec;
    TRec = TRecMiliSec;
    Vel = Velocidad;
    VelGiro = VelocidadGiro;
    DistAtaq = _DistAtaq;
    RGiro = random(0,2);
}

void SumoBase::AddInfraAdelante(uint8_t pin){ AddInfra(0,pin);}

void SumoBase::AddSUSAdelante(uint8_t triger, uint8_t echo){ AddSUS(0, triger, echo);}

void SumoBase::Add2Motors(Motor L1, Motor L2){
    SetMotor(L1,Vel); Motores.push_back(L1);
    SetMotor(L2,Vel); Motores.push_back(L2);
}

void SumoBase::Camina(unsigned int TimeMinuts = 0){
    if(Motores.size() != 0){
        
        //tomamos un puntero al elemento deceado
        /*UltraSonico *USDelantes = TomaUltrasonicoByID(0);
        Infrarrojo *infDelantes = TomaInfrarrojoByID(0);*/

        //Movimiento aleatorio
        RGiro = random(0,2);
        
        //variables locales que se que solo se inician minimo una vez
        unsigned long Time = 0, inicio = millis();
        
        //para accionar los Infra
        unsigned long InicioAtras = 0;
        bool Atras = false;

        //Para accionar los USU
        unsigned long InicioAtaque = 0, usAccion = 0;
        bool ataque = false, usDetected = false;

        //ConfigVelocidad(Motores, VelGiro);
        //MDerIzq(Motores,RGiro); //giramos

        while(1){
            Serial.println("...");

            //para controlar el temporizador de actividad
            if(TimeMinuts > 0 && (millis() - inicio) >= (TimeMinuts*60000)) return;

            //comenzamos a contar
            Time = millis();

            //Vemos los infrarrojos
            //Tomamos todos los sensores Infrarojos
            UsaAllInfrarrojo();
            MoverPorInfrarrojos(InicioAtras, Atras);

            //buscamos por un tiempo definido, esto para que no gire todo el rato en caso que no encuentre nada
            while((millis() - Time ) <= TGiro){
                UsarAllSUS();
                Extras();
                MoverPorSUS(InicioAtaque, usAccion, ataque, usDetected);
                Ataque(ataque, Atras, InicioAtaque, InicioAtras);
                FinAtaque(ataque, Atras, InicioAtras, InicioAtaque);
            }
        }
    }
}