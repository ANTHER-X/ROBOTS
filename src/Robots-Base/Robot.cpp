#include "Robot.hpp"

/*
Robot::
*/

void Robot::AddMotors(std::vector<Motor> Mtrs) {
    
    //evita demaciados motores
    if(Mtrs.size() > 32){
        DBG_MOTORTEXT_PRINT;
        DBG_PRINTLN("Demaciados motores.");
        return;
    }

    Motores = Mtrs;
    for(unsigned int i=0; i<Motores.size(); i++) SetMotor(Motores[i], Vel);

    //info para debugin
    DBG_MOTORTEXT_PRINT;
    DBG_PRINT("Motores ");
    DBG_PRINT(Motores.size());
    DBG_PRINTLN("Agregados");
}

void Robot::ConfigVelocidad(std::vector<Motor> &M, uint8_t vel){
    //seteamos velocidad
	for(unsigned int i=0; i<M.size(); i++){
		if(motorType == DRIVER_PWM_SEPARATE) analogWrite(M[i].PWM, vel);
        else  analogWrite(M[i].L1, vel);
        //debugin
        DBG_MOTOR_VELOCIDAD(M[i].L1, M[i].L2, M[i].PWM, vel);
        DBG_PRINTLN(". Seteado");
	}
}

//Movimientos de los motores, supongamos 2 motores (6 pines), aunque puede funcionar para mas
void Robot::MDelAtrs(std::vector<Motor> &M, bool delante){
    
    for(uint8_t i=0; i<M.size(); i++){
        digitalWrite(M[i].L1, (delante ? HIGH : LOW));
        digitalWrite(M[i].L2, (delante ? LOW : HIGH));
        //debugin
        DBG_MOTOR(M[i].L1, M[i].L2, M[i].PWM);
        DBG_VALUE_LN(". Camina hacia: ", (delante ? "delante" : "atras"));
    }
    
}

//si usa true va hacia la derecha, si usa false, hacia la izquierda
//deberia funcionar para motores pares en lineas de 2
void Robot::MDerIzq(std::vector<Motor> &M, bool Der){
    
    for(uint8_t i=0; i<M.size(); i++){
        digitalWrite(M[i].L1, Der ? LOW : HIGH);
        digitalWrite(M[i].L2, Der ? HIGH : LOW);
        Der = Der ? false : true;//cambia de direccion del siguiente motor (es el de al lado por lo que guirara)
        
        //debugin
        DBG_MOTOR(M[i].L1, M[i].L2, M[i].PWM);
        DBG_VALUE_LN(". gira hacia: ", (Der ? "derecha" : "izquierda"));
    }
    
}

void Robot::MStop(std::vector<Motor>& M){
    
    for(uint8_t i=0; i<M.size(); i++){
        digitalWrite(M[i].L1, LOW);
        digitalWrite(M[i].L2, LOW);
        
        //debugin
        DBG_MOTOR(M[i].L1, M[i].L2, M[i].PWM);
        DBG_PRINTLN(". Se detiene.");
    }
}

//Para definir los motores
void Robot::SetMotor(Motor &M, uint8_t Vel){
    //Le damos un modo al pines
    pinMode(M.L1, OUTPUT);
    pinMode(M.L2, OUTPUT);
    
    if(motorType == DRIVER_PWM_SEPARATE){
        pinMode(M.PWM, OUTPUT);
        DBG_VALUE_LN("Agregando Velocidad", Vel);
        analogWrite(M.PWM, Vel);
    }
    else{
        DBG_VALUE_LN("Agregando Velocidad", Vel);
        analogWrite(M.L1, Vel);
        M.PWM = M.L1;
    }
    DBG_MOTOR_VELOCIDAD(M.L1, M.L2, M.PWM, Vel);
    DBG_PRINTLN(". Seteado");
}