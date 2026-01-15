
#pragma once

#include <Arduino.h>

//Archivo de Confguracion
#include "Config.hpp"

#ifndef USE_OLD_V
    //Dependencias
    #include "Dependencias/Sensores.hpp"
    #include "Dependencias/Utilidades.hpp"

    //Robot Base
    #include "Robots-Base/Robot.hpp"

    //Sumos
    #include "Robots-Base/SumoBase.hpp"
    #include "Robots-Simples/SumoSimple.hpp"

    //RLB (Resuelve Laberintos Base)
    #include "Robots-Base/RLBase.hpp"
    #include "Robots-Simples/RLB-Servo.hpp"
    #include "Robots-Simples/RLB-US.hpp"

    //Autos Remoto (por BlueThoot)
    #include "Robots-Base/AutoRemotoBase.hpp"
    #include "Robots-Simples/AutRem-SSS.hpp"
#else
    /*Incluimos los antiguos modelos para re-tocarlos*/
    #include "Old-Version-Concept V-0.0.1/Dependencias-Old/Sensores.hpp"

    #include "Old-Version-Concept V-0.0.1/Robot.hpp"

    #include "Old-Version-Concept V-0.0.1/Sumo.hpp"
    #include "Old-Version-Concept V-0.0.1/Seguidor.hpp"
    #include "Old-Version-Concept V-0.0.1/ResuelveLaberinto.hpp"
    #include "Old-Version-Concept V-0.0.1/Insecto.hpp"
    #include "Old-Version-Concept V-0.0.1/AutoRemoto.hpp"
#endif