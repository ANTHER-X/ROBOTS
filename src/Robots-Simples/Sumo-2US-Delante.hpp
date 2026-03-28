#ifndef SUMO_2US_DELANTE_HPP
#define SUMO_2US_DELANTE_HPP

#include "../Robots-Base/SumoBase.hpp"

class Sumo2USDelante : public SumoBase{
    protected:
    virtual void MoverPorSUS(unsigned long &timer,unsigned long &timerUS, bool &atUsed, bool &usUsed) override;
    virtual void MoverPorInfrarrojos(unsigned long &timer, bool &used) override;

    public:
    Sumo2USDelante(uint8_t Velocidad, uint8_t VelocidadGiro, uint8_t _DistAtaq, unsigned int TRecMiliSec, unsigned int TGiroMiliSec, MotorDriverType typeMotor)
    : SumoBase(Velocidad, VelocidadGiro, _DistAtaq, TRecMiliSec, TGiroMiliSec, typeMotor){};

    void AddUSs(uint8_t trigerLeft, uint8_t echoLeft, uint8_t trigerRight, uint8_t echoRight);
    void AddIRsDelante(uint8_t IR1, uint8_t IR2);
    void AddIrAtras(uint8_t pin);
    
    virtual void Camina(unsigned int TimeMinuts = 0) override;

};
#endif