#include "Robot.hpp"

/*
Robot::
*/

void Robot::ConfigVelocidad(std::vector<Motor> &M, uint8_t vel){
	for(unsigned int i=0; i<M.size(); i++){
		if(M[i].PWM > 0) analogWrite(M[i].PWM, vel);
	}
}

//Movimientos de los motores, supongamos 2 motores (6 pines), aunque puede funcionar para mas
void Robot::MDelAtrs(std::vector<Motor> &M, bool delante){
    
    for(uint8_t i=0; i<M.size(); i++){
        digitalWrite(M[i].L1, (delante ? HIGH : LOW));
        digitalWrite(M[i].L2, (delante ? LOW : HIGH));
    }
    
}

//si usa true va hacia la derecha, si usa false, hacia la izquierda
//deberia funcionar para motores pares en lineas de 2
void Robot::MDerIzq(std::vector<Motor> &M, bool Der){
    
    for(uint8_t i=0; i<M.size(); i++){
        digitalWrite(M[i].L1, Der ? LOW : HIGH);
        digitalWrite(M[i].L2, Der ? HIGH : LOW);
        Der = Der ? false : true;//cambia de direccion del siguiente motor (es el de al lado por lo que guirara)
    }
    
}

void Robot::MStop(std::vector<Motor>& M){
    
    for(uint8_t i=0; i<M.size(); i++){
        digitalWrite(M[i].L1, LOW);
        digitalWrite(M[i].L2, LOW);
    }
}

//Para definir los motores
void Robot::SetMotor(Motor &M, uint8_t Vel){
    //Le damos un modo al pines
    pinMode(M.L1, OUTPUT);
    pinMode(M.L2, OUTPUT);
    //SetSpeed de los motores, si el pin es real, aplicamos la Vel, si no... pues no
    if(M.PWM > 0){
        pinMode(M.PWM, OUTPUT);
        Serial.println("Agregando Velocidad" + Vel);
        analogWrite(M.PWM, Vel);
    }
    Serial.println("Motor seteado");
}