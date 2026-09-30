/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include <Robots-Simples/Sumo.hpp>

//Sumo::


//metodos privados
//captura la distancia en CM
void Sumo::MedirSUS(UltraSonico &US){
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

int Sumo::TomarDistUS(UltraSonico &US){
    MedirSUS(US);
    return US.Cerca;
}

void Sumo::UsarAllSUS(){
    for(uint8_t i=0; i<UltraSonicoCount; i++)
        MedirSUS(UltraSonicos[i]);
}

//toma el estado de los infrarrojos
void Sumo::ActivaIR(Infrarrojo &INF){
    #if USE_IR == 1
        INF.Estado = digitalRead(INF.Pin) == LOW;
        DBG_VALUE("Pin Usado: ", INF.Pin);
        DBG_VALUE_LN(". Estado tomado: ", INF.Estado);
    #endif
}
bool Sumo::UsaIR(Infrarrojo &INF){
    #if USE_IR == 1
        ActivaIR(INF);
        return INF.Estado;
    #else 
        return false;
    #endif
}
void Sumo::UsaAllIR(){
    #if USE_IR == 1
        for(uint8_t i=0; i<InfrarrojoCount; i++)
            ActivaIR(Infrarrojos[i]);
    #endif
}


void Sumo::MoverPorSUS(unsigned long &timer, unsigned long &timerUS, bool &atUsed, bool &usUsed){
    for(uint8_t i=0; i<UltraSonicoCount; i++){

        //Si estamos en el US de delante y hay algo en el punto de ataque y aun no ataca, atacamos
        if(!atUsed && UltraSonicos[i].angle == 0 && UltraSonicos[i].Cerca){
            DBG_PRINTLN("\n\nATACANDO.\n\n");
            ConfigVelocidad(*Motores, CantidadMotores, Vel);
            MDelAtrs(*Motores, CantidadMotores, true);
            timer = millis(); //marcamos el inicio del ataque
            atUsed = true; //decimos que atacamos
            // Reproducimos sonido de ataque
            Sound->Play(MusicIndex[0]);
            return;
        }

        // Si no vamos a detectar los demas sensores
        if (!usUsed && !atUsed && UltraSonicos[i].Cerca){
            DBG_PRINTLN("\nGirando.\n");

            // Configuramos la velodicidad de giro y giramos
            ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
            MDerIzq(*Motores, CantidadMotores, !(UltraSonicos[i].angle > 0));

            timer = millis(); //marcamos el inicio del ataque
            usUsed = true; //decimos que estamos girando

            // Damos el tiempo de giro de acuerdo al angulo que tiene el sensor
            timerUS = (abs(UltraSonicos[i].angle) * TGiro) / 180;

            return;
        }
    }

    // En caso de que este termine de girar, paramos todo
    if(usUsed && (millis() - timer) >= timerUS){
        DBG_PRINTLN("Giro Finalizado");
        usUsed = false;
        MStop(*Motores, CantidadMotores);
    }
}


void Sumo::MoverPorIR(unsigned long &timer, bool &used, unsigned long timerIR_Uso){
    #if USE_IR == 1
        for(uint8_t i=0; i<InfrarrojoCount; i++){
            
            // Si los IR esta delante o atras el IR no giramos, sino que movemos hacia atras o adelante

            //si detecta el borde giramos
            if(!used && Infrarrojos[i].Estado == IR_ACTIVATE){
                DBG_PRINTLN("\n\nNOS SALIMOS!!!.\n\n");
                timer = millis(); //iniciamos donde comenzo hacia atras
                used = true;//decimos que se mueve hacia atras

                // Si los IR detectan salida por delante, nos movemos hacia atras
                if(Infrarrojos[i].angle > (-21) || Infrarrojos[i].angle < 21){

                    MDelAtrs(*Motores, CantidadMotores, false);
                    timerIR_Uso = TRec;
                    // Reproducimos sonido de back
                    Sound->Play(MusicIndex[1]);
                    break;
                }

                // Contrario, atras -> Mueves adelante
                if(Infrarrojos[i].angle > 159 || Infrarrojos[i].angle < (-159)){

                    MDelAtrs(*Motores, CantidadMotores, true);
                    timerIR_Uso = TRec;
                    break;
                }

                ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
                MDerIzq(*Motores, CantidadMotores, (Infrarrojos[i].angle > 0)); // Giramos de acuerdo a donde esta
                // Sacamos el timer para ver el tiempo de giro
                timerIR_Uso = (abs(UltraSonicos[i].angle) * TGiro) / 180;
                
                // Reproducimos sonido en caso de que se salga
                Sound->Play(MusicIndex[2]);
                break;
            }
        }

        // Si termina de girar paramos y detenemos todo
        if(used && (millis() - timer) >= timerIR_Uso){
            DBG_PRINTLN("Giro Finalizado");
            used = false;
            MStop(*Motores, CantidadMotores);
            Sound->Stop();
            Sound->ResetSounds();
        }
    #endif
}


void Sumo::FinAtaque(bool &ataque, bool &infAccion, unsigned long timeInfAccion, unsigned long timeAtaque){
    //si ya no hay ataque y ya no vamos a retroceder (o que se haya usado algun infrarrojo) volvemos a girar
    #if USE_IR == 1
        if(!ataque && infAccion && (millis() - timeInfAccion) > TRec){
            ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
            MDerIzq(*Motores, CantidadMotores, RGiro);
            infAccion = false;
            ataque = false;
            Sound->Stop();
            DBG_PRINTLN("Buscando");
        }
    #endif

    //si no detectamos la barrera y ya paso el tiempo de accion del ataque, detenemos el ataque
    if(ataque && (millis() - timeAtaque) > TRec){
        ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
        MDerIzq(*Motores, CantidadMotores, RGiro);
        ataque = false;
        Sound->Stop();
        Sound->ResetSounds();
        DBG_PRINTLN("\n\nATAQUE FINALIZADO\n\n");
    }
}

//Los Ultrasonicos para los ojos
void Sumo::AddSUS(int16_t angle, uint8_t triger, uint8_t echo){
    if(ExistSUS(angle) || UltraSonicoCount > MAXSUS){
        DBG_VALUE("El sensor ultrasonico ya existe o se supero el limite establecido. Pin triger:", triger);
        DBG_VALUE_LN(". Pin Echo: ", echo);
        return; //si ya existe el ID, no hacemos nada
    }
    DBG_PRINTLN("Sensor US agregado");
    UltraSonico US = {0};
    US.angle = angle;
    US.Pin[0] = triger; pinMode(US.Pin[0], OUTPUT);
    US.Pin[1] = echo; pinMode(US.Pin[1], INPUT);

    UltraSonicoCount++;
    UltraSonicos[UltraSonicoCount-1] = US;
}

//Define los infrarrojos
void Sumo::AddIR(int16_t angle, uint8_t pin){
    #if USE_IR == 1
        if(ExistIR(angle) || InfrarrojoCount > MAXIR){
            DBG_VALUE_LN("El sensor infrarrojo ya existe o se supero el maximo. Pin:", pin);
            return; //si ya existe el ID, no hacemos nada
        }

        //Seteamos el nuevo sensor
        DBG_PRINTLN("Sensor INF agregado");
        Infrarrojo IF = {0};
        IF.angle = angle;
        IF.Pin = pin; pinMode(IF.Pin, INPUT);

        //Lo agregamos a
        InfrarrojoCount++;
        Infrarrojos[InfrarrojoCount-1] = IF;
    #endif
}

bool Sumo::ExistIR(int16_t angle){

    #if USE_IR == 1
        for(uint8_t i=0; i<InfrarrojoCount; i++){
            if(Infrarrojos[i].angle == angle) return true;
        }
    #endif

    return false;
}

bool Sumo::ExistSUS(int16_t angle){
    for(uint8_t i=0; i<UltraSonicoCount; i++){
        if(UltraSonicos[i].angle == angle) return true;
    }
    return false;
}

Sumo::Sumo(uint8_t Velocidad, uint8_t VelocidadGiro, uint8_t DistAtaqCM, uint16_t DiametroCM, uint16_t Vel_CMS, unsigned int TRecRect, MotorDriverType typeMotor){
    
    motorType = typeMotor;
    VelGiro = VelocidadGiro;
    DistAtaq = DistAtaqCM;
    
    // Si el motor permite PWM
    if(motorType != MotorDriverType::NO_SETTER_SPEED){
        TRec = TRecRect;
        Vel = Velocidad;
    }
    // Si no hay PWM ponemos potencia maxima
    else TRec = Vel = 255;

    /* Sacamos El tiempo de giro para 180 grados ya que es el maximo giro (por eso 2UL).
       Escalamos para evitar decimales subiendo 4 decimales a entero y guardamos el tiempo en milisegundos.
       Tomamos el porcentaje de velocidad de acuerdo a la potencia ingresada, Vel_CMS representa potencia 255 maxima*/
    if(VelGiro > 0){ // Si hay potencia de giro
        TGiro = (31416UL * DiametroCM * 255UL * 1000UL) /
            (2UL * Vel_CMS * VelGiro * 10000UL);    
    }
    // Si no hay potencia no hacemos nada.
    else TGiro = 0;
}

void Sumo::Camina(unsigned int activeTimeMillis){
    if(CantidadMotores != 0){

        //Movimiento aleatorio
        RGiro = random(0,2);
        
        //variables locales que se que solo se inician minimo una vez
        
        //para accionar los IR
        unsigned long TimeIRUsed = 0, InicioIR = 0;
        bool Atras = false;

        //Para accionar los USU
        unsigned long InicioUS = 0, usAccion = 0;
        bool ataque = false, usDetected = false;

        unsigned int initTime = activeTimeMillis ? millis(): 0;

        ConfigVelocidad(*Motores, CantidadMotores, VelGiro);
        MDerIzq(*Motores, CantidadMotores, RGiro); //giramos

        do{
            //Movimiento completo del robot
            UsaAllIR();
            MoverPorIR(InicioIR, Atras, TimeIRUsed);
            UsarAllSUS();
            Extras();
            MoverPorSUS(InicioUS, usAccion, ataque, usDetected);
            FinAtaque(ataque, Atras, InicioIR, InicioUS);

        }while( ( activeTimeMillis == 0 || (initTime > 0 && (millis() - initTime < activeTimeMillis))) );
    }
}