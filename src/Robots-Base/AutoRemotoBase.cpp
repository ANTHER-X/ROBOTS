#include "AutoRemotoBase.hpp"

//AutoRemotoBase::

void AutoRemotoBase::TeclaMoveMotors(char del = 'W', char atr = 'S', char der ='D', char izq = 'A', char det = 'Z'){
    //dependiendo de la lectura, nos movemos o no
    if(tecla == del) MDelAtrs(Motores, true);
    if(tecla == atr) MDelAtrs(Motores, false);
    if(tecla == der) MDerIzq(Motores, true);
    if(tecla == izq) MDerIzq(Motores, false);
    if(tecla == det) MStop(Motores);
}

//Si usamos arduino y algun modulo BlueThoot
void AutoRemotoBase::BTHMove(unsigned int recSeg, char del = 'W', char atr = 'S', char der ='D', char izq = 'A', char det = 'Z'){
    //si le llega algun dato
    if(BTH->available()){

        //lo leemos
        tecla = BTH->read();
        
        //Tomamos el recorido real a segundos
        recSeg *= 1000000;

        //Movemos los motores
        TeclaMoveMotors(del,atr,der,izq,det);
        
        //nos mantenemos en movimiento por NSeg
        delayMicroseconds(recSeg);

        //nos detenemos
        MStop(Motores);
    }
}


AutoRemotoBase::AutoRemotoBase(uint8_t receivePin, uint8_t transmitPin, uint8_t velocidad){
    Vel = velocidad;
    SoftwareSerial aux(receivePin, transmitPin);
    BTH = &aux;
}

/*Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER.
Pero ahora, en este caso, los 2 motores primeros (que serian 2 llantas), seran los que se mueven
hacia adelante*/
void AutoRemotoBase::AddMotors(std::vector<Motor> Mtrs) {
    Motores = Mtrs;
    for(unsigned int i=0; i<Motores.size(); i++) SetMotor(Motores[i], Vel); 
}

/*Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER.
Pero ahora, en este caso, los 2 motores primeros (que serian 2 llantas), seran los que se mueven
hacia adelante*/
void AutoRemotoBase::Add4Motors(Motor RotIzq1, Motor RotDer1, Motor izq2, Motor der2){
    SetMotor(RotIzq1,Vel); Motores.push_back(RotIzq1);
    SetMotor(RotDer1,Vel); Motores.push_back(RotDer1);
    SetMotor(izq2,Vel); Motores.push_back(izq2);
    SetMotor(der2,Vel); Motores.push_back(der2);
}

void AutoRemotoBase::Camina(unsigned int recSeg = 2, char del = 'W', char atr = 'S', char der ='D', char izq = 'A', char det = 'Z', unsigned int activeTimeMillis = 0){
    //Si no hay motores o no hay BlueThoot no hacemos nada
    if(Motores.size() < 1 || BTH == nullptr) return;
    
    //Si es que hay motores, configuramos las variables iniciales
    unsigned int initTime = activeTimeMillis ? millis(): 0;//tiempo de inicio si es que agrega (default '0')

    //si si hay motores, nos movemos por medio del blueThoot
    do{
        BTHMove(recSeg,del,atr,der,izq,det);
    
    //si no configura el tiempo se mantendra siempre, si si el bucle terminara cuando el tiempo se acabe
    }while( ( activeTimeMillis == 0 || (initTime > 0 && (millis() - initTime < activeTimeMillis))) );
}