//#include "../Robots-Base/AutoRemotoBase.hpp"
#include "AutRem-SSS.hpp"

//AutRemSSS::
void AutRemSSS::AddMotors(std::vector<Motor> Mtrs){
    if(Mtrs.size() < 4){
        Serial.println("Es Necesario mas de 4 Motores");
        return;
    }
    Motores = Mtrs;
    for(unsigned int i=0; i<Motores.size(); i++) SetMotor(Motores[i], Vel); 
}

void AutRemSSS::MDerIzq(std::vector<Motor> &M, bool Der){
    //apagamos los motores de delante
    digitalWrite(M[0].L1,LOW);
    digitalWrite(M[0].L2,LOW);
    digitalWrite(M[1].L1,LOW);
    digitalWrite(M[1].L2,LOW);

    //Movemos el Servo dependiendo de a donde quiera ir
    servoControler.write( (Der ? (0):(180)) );
}

//Modificamos un poco
void AutRemSSS::BTHMove(unsigned int recSeg = 1, char del = 'W', char atr = 'S', char der ='D', char izq = 'A', char det = 'Z'){
    //si le llega algun dato
    if(BTH->available()){

        //Tomamos el tiempo en que llego
        startTime = millis();
        
        //Tomamos el recorido real a segundos
        recSeg *= 1000;

        //lo leemos
        tecla = BTH->read();
        
        //Movemos los motores
        TeclaMoveMotors(del,atr,der,izq,det);
    }

    //nos detenemos si el tiempo termino
    if((millis() - startTime) > recSeg){
        MStop(Motores);
        servoControler.write(90);
    }
}

AutRemSSS::AutRemSSS(uint8_t receivePin, uint8_t transmitPin, uint8_t pinServo, uint8_t velocidad) : AutoRemotoBase(receivePin, transmitPin, velocidad){
    //Tomamos el pin para el servo y lo movemos 90-grados
    servoControler.attach(pinServo);
    servoControler.write(90);
    startTime = 0;
}