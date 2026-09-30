/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include <Robots-Simples/SeguidorLinea.hpp>

SeguidorLinea::SeguidorLinea(uint8_t velocidadMedia, uint8_t velocidadMaxima, MotorDriverType motorDriverType, BuzzerType buzzerType){
    this->motorType = motorDriverType;
    this->timeMove = 40;
    this->Vel = velocidadMedia;
    this->vMax = velocidadMaxima;
}

//Vamos a leer un pin digital que actuara como indicador de colicion
void SeguidorLinea::AddIRColicion(uint8_t pin){
    
    //Salimos en caso de error
    if(pin == 0){
        DBG_PRINTLN("Pin invalido, por favor agrega un pin valido");
        return;
    }

    //Agregamos e inicializamos el pin
    IRColicioner.Pin = pin;
    pinMode(IRColicioner.Pin, INPUT);

    DBG_VALUE_LN("IR de colision agregado, pin: ", IRColicioner.Pin);

}

// Iniciamos el sonido de colicion
void SeguidorLinea::StarSoundColicion(bool isColitioned){
    // Si no ah colicionado detenemos sonido si es que se reprodujo alguno
    if(!isColitioned){
        if(Sound != nullptr) Sound->Stop();
        DBG_PRINTLN("No se ha colicionado");
        Sound->Stop();
        Sound->ResetSounds();
        return;
    }

    // Si se ah colicionado con algo reproducimos melodia
    Sound->Play();
}


/*
 * Vamos a sacar el sensor del centro y asignar los pesos para la potencia de los motores
*/
void SeguidorLinea::AddIRs(uint8_t IRpines[], uint8_t tamIR){

    if(tamIR == 0 || tamIR + tamIrs > MAXIRSEGUIDOR){
        DBG_PRINTLN("Agregaste mas de los IR soportados, por favor agrega menos :)");
        return;
    }

    //Agregamos los IR sin nada nadita
    uint8_t aux = tamIrs;
    DBG_VALUE_LN("Tam actual: ", tamIrs);
    for(uint8_t i=tamIrs; i< (tamIR+aux); i++){

        irs[tamIrs] = {{IRpines[i-aux], false, 0}, 0};
        tamIrs++;

        DBG_VALUE_LN("Agredando IR's. Index", (tamIrs-1));
        DBG_VALUE_LN("Agregando IR's. Pin: ", irs[tamIrs-1].IR.Pin);
    }

    //Reinicializamos las estadisticas de los IRs
    InitStatsIRs();
}

void SeguidorLinea::InitStatsIRs(){
    DBG_VALUE_LN("Inicializando IR's. Tam. de IRs: ", tamIrs);
    //Vemos si es o no par
    isPar = (tamIrs%2 == 0);
    //El centro de la linea
    centro = (tamIrs/2);
    //sacamos el verdadero centro en caso de que sea impar
    centro += isPar ? 0:1;

    //Agregamos los IR y el pero-potencia de cada uno
    for(short i=centro-tamIrs; i < centro; i++){
        /*En el caso de los impares, la potencia automaticamente esta ajustada ya que el centro es impar
        y solo este tendra valor 0.
        En caso de los pares, habra 2 IR con cero, por lo que a todos los IR detras
        del que ya tenga 0 se les sumara 1*/
        irs[i+ (isPar? (centro):(centro-1))].pesoPotencia = (isPar ? ((i <= centro-(centro+1)) ? i+1 : i) : i);
        DBG_VALUE_LN("Registrando indices de acceso para IR, index: ", (i+ (isPar? (centro):(centro-1))));
        DBG_VALUE_LN("Valor potencia: ", irs[i+ (isPar? (centro):(centro-1))].pesoPotencia);
    }

    /*Ahora iniciamos cada pin IR*/
    for(uint8_t i=0; i < tamIrs; i++){
        DBG_VALUE_LN("IR Inicializado, pin: ", irs[i].IR.Pin);
        pinMode(irs[i].IR.Pin, INPUT);
    }

}


// Actualizamos el estado a lectura de los IRs
void SeguidorLinea::AccionaAllIR(){
    for(uint8_t i=0; i<tamIrs; i++){
        irs[i].IR.Estado = digitalRead(irs[i].IR.Pin);
        
        //debugin
        DBG_VALUE_LN("Pin: ",irs[i].IR.Pin);
        DBG_VALUE_LN(": Estado: ", irs[i].IR.Estado);
    }
}

void SeguidorLinea::PotenciaEquilibrio(){
    DBG_PRINTLN("Tomando potencias");
    //Vemos cual lado tiene mayor lectura igual respecto al centro
    pIzq = 0;
    pDer = 0;

    /*
    * Aumentamos en uno si N sensor tiene el mismo estado que el centro y que el anterior, es decir, que vaya en forma lineal
    * eh incremental hacia un lado, si es par, el centro derecho sera el centro-2 por la pocicion inicial que fue desde 1 y
    * no desde 0, en caso de impar el verdadero centro es centro-1
    */
    DBG_VALUE_LN("Index central: ", (centro-1));
    for(short i = (centro-2); i>=0; i--){
        DBG_VALUE_LN("Index de valor Izquierda: ", i);
        DBG_VALUE_LN("Estado de index a actual: ", irs[i].IR.Estado);
        DBG_VALUE_LN("Estado anterior a actual: ", irs[i+1].IR.Estado);
        DBG_VALUE_LN("Estado del centro: ", irs[centro-1].IR.Estado);

        pIzq += (irs[i].IR.Estado == irs[i+1].IR.Estado && irs[i].IR.Estado == irs[centro-1].IR.Estado) ? (1):(0);
    }
    DBG_VALUE_LN("Valor de potencia a Izquierda: ", pIzq);
    

    //Hacemos lo mismo para el lado derecho
    for(uint8_t i= isPar ? (centro+1):(centro); i<tamIrs; i++){
        DBG_VALUE_LN("Index de valor Derecha tomado: ", i);
        DBG_VALUE_LN("Estado de index a actual: ", irs[i].IR.Estado);
        DBG_VALUE_LN("Estado anterior a actual: ", irs[i-1].IR.Estado);
        DBG_VALUE_LN("Estado del centro: ", irs[isPar ? (centro):(centro-1)].IR.Estado);

        pDer +=(irs[i].IR.Estado == irs[i-1].IR.Estado && irs[i].IR.Estado == irs[isPar ? (centro):(centro-1)].IR.Estado) ? (1):(0);
    }

    DBG_VALUE_LN("Valor de potencia a Derecha: ", pDer);
}


void SeguidorLinea::ConfigVelocidad(Motor* M, uint8_t size,uint8_t vDer, uint8_t vIzq){
    //seteamos velocidad
	for(uint8_t i=0; i<size; i++){
        /*Vemos el tipo de motor y agregamos al pin correspondiente,
        para agregar velocidad vemos cuales son los motores de la
        izquierda -> Pares, y cuales los de la derecha -> Impares*/
        analogWrite((motorType == DRIVER_PWM_SEPARATE) ? (M[i].PWM) : (M[i].L1), ((i & 1) == 0) ? (vIzq):(vDer));
        //debugin
        DBG_PRINT("Velocidad de motores izquierdos:  ");
        DBG_MOTOR_VELOCIDAD(M[i].L1, M[i].L2, vIzq);
        DBG_PRINT("Velocidad de motores derechos:  ");
        DBG_MOTOR_VELOCIDAD(M[i].L1, M[i].L2, vDer);
	}
}

void SeguidorLinea::MoveMotorsForIR(){
    bool colitioned = false;

    //Si coliciono con algo paramos, damos el sonido si es que hagrega y salimos
    if(IRColicioner.Pin != 0 && IRColicion() == IR_ACTIVATE){
        DBG_PRINTLN("Colision detectada, deteniendo...");
        MStop(*Motores, CantidadMotores);
        colitioned = true;
    }

    //Reproducimos o no las notas musicales dependiendo de la colicion
    StarSoundColicion(colitioned);
    if(colitioned) return;

    //Si los lados quedaron iguales, vamos hacia adelante
    if(pDer == pIzq){
        //Caminando hacia adelante
        ConfigVelocidad(*Motores, CantidadMotores, Vel);
        MDelAtrs(*Motores, CantidadMotores, true);
        return;
    }
    /*
     * si uno quedo mayor que el otro, vamos hacia ese lado, pero la velocidad sera proporcional
     * a la potencia asignada
    */
    //Damos la diferencia de velocidad
    DBG_VALUE_LN("Peso potencia maximo: ", irs[tamIrs-1].pesoPotencia);
    short dif = (vMax/irs[tamIrs-1].pesoPotencia)* (pDer - pIzq);
    dif = constrain(dif,(-vMax),vMax);
    DBG_VALUE_LN("Valor del diferencial: ", dif);

    //velocidades de cada motor
    short vDer = Vel + (dif);
    short vIzq = Vel - (dif);
    
    ConfigVelocidad(*Motores, CantidadMotores, constrain(vDer,0,vMax), constrain(vIzq,0,vMax));
}

void SeguidorLinea::Camina(unsigned int activeTimeMillis){
    //Vemos que tenga cosas
    if(tamIrs < 1 || CantidadMotores == 0){
        DBG_PRINTLN("Sensores/Motores Incompletos, No puedo continuar asi");
        return;
    }

    unsigned int initTime = activeTimeMillis ? millis(): 0;
    do {
        //Accionamos todos los IR
        AccionaAllIR();
        PotenciaEquilibrio();
        //Movemos
        MoveMotorsForIR();
    }while( ( activeTimeMillis == 0 || (initTime > 0 && (millis() - initTime < activeTimeMillis))) );
}
