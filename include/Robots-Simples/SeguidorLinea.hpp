/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/


#ifndef SEGUIDORLINEA_HPP
#define SEGUIDORLINEA_HPP

#include <Robots-Base/Robot.hpp>
#include <modules/SoundSystem.hpp>

class SeguidorLinea : public Robot{
protected:

    IRSeguidorLinea irs[MAXIRSEGUIDOR];
    uint8_t tamIrs = 0, vMax;
    unsigned long timeMove;
    bool isPar; // Ver si la cantidad es par o impar en los IRs y determinar el centro
    short centro, pIzq = 0, pDer = 0; // Dice el IR central, asi como los pesos totales para derecha e izquierda

    bool colitioned;

    //Cosas para coliciones
    //IR para detectar coliciones
    Infrarrojo IRColicioner = {0};

    // Sistema de sonido
    SoundSystem* Sound = nullptr;

    void AccionaAllIR();
    void MoveMotorsForIR();
    void PotenciaEquilibrio();
    //Para variar la velocidad de los motores
	void ConfigVelocidad(Motor* M, uint8_t size, uint8_t vDer, uint8_t vIzq);

    //Para poder saber si el sensor de colision se activo
    inline bool IRColicion(){return (digitalRead(IRColicioner.Pin) == IR_ACTIVATE); }
    void StartSoundColicion(bool isColitioned);

    //Iniciamos las Stats de los IRs
    void InitStatsIRs();

    // Para ver la colicion
    bool Colition();

    //Para no ocultar el metodo de la clase base y evitar errores de metodos no existentes
    using Robot::ConfigVelocidad;

public:
    SeguidorLinea(uint8_t velocidadMedia, uint8_t velocidadMaxima = 255, MotorDriverType motorDriverType = DRIVER_PWM_SEPARATE, BuzzerType buzzerType = BUZZER_ACTIVE);

    void AddIRColicion(uint8_t pin);
    inline void AddSoundSystem(SoundSystem* soundSystem){Sound = soundSystem; }
    void AddIRs(uint8_t IRpines[], uint8_t tamIR);
    virtual void Camina(unsigned int TimeMinuts = 0) override;

};




#endif