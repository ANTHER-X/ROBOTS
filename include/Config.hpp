/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/


/*
    Configuracion del proyecto, cada macro sera para definir el uso del codigo.
    Desable = 0
    Enable = 1
*/

#ifndef CONFIG_HPP
#define CONFIG_HPP

#define SERIAL_DEBUG          0 //para imprimir datos de depuracion en el monitor serial
#define USE_IR                1 //para sensores infrarrojos
#define USE_OLD_V             0 //para usar los modelos antiguos de robots

#define IR_ACTIVATE HIGH //para activar la accion de los infrarrojos al detectar algo

//Cantidades maximas de sensores
#define MAXNOTAS 4
#define MAXMOTORS 8
#define MAXIRSEGUIDOR 16
#define MAXSUS 4
#define MAXIR 4

//Mas macros para depuracion:
#if (SERIAL_DEBUG == 1)

    #define DBG_PRINT_Var(x)    Serial.print(x)
    #define DBG_PRINT_LN_Var(x)    Serial.println(x)
    #define DBG_PRINT(x)    Serial.print(F(x))
    #define DBG_PRINTLN(x)  Serial.println(F(x))
    #define DBG_MOTORTEXT_PRINT Serial.print(F("[Motor]: "));

    #define DBG_MOTOR(L1, L2) \
        do { \
            Serial.print(F("L1: ")); Serial.print(L1); \
            Serial.print(F(" L2: ")); Serial.print(L2); \
        } while (0)

    #define DBG_MOTOR_VELOCIDAD(L1, L2, VEL) \
        do { \
            DBG_MOTOR(L1, L2); \
            Serial.print(F(" Vel: ")); Serial.println(VEL); \
        } while (0)
    
    #define DBG_VALUE_LN(T,V) \
        do { \
            Serial.print(F(T)); \
            Serial.println(V); \
        } while (0)

    #define DBG_VALUE(T,V) \
        do { \
            Serial.print(F(T)); \
            Serial.print(V); \
        } while (0)
    
#else
    #define DBG_PRINT_Var(x)
    #define DBG_PRINT_LN_Var(x)
    #define DBG_PRINT(x)
    #define DBG_PRINTLN(x)
    #define DBG_MOTORTEXT_PRINT
    #define DBG_MOTOR(L1, L2)
    #define DBG_MOTOR_VELOCIDAD(L1, L2, VEL)
    #define DBG_VALUE_LN(T,V)
    #define DBG_VALUE(T,V)
#endif


#endif