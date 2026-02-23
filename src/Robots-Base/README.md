# Robots-Base
Esta carpeta contiene todo lo referente a las clases base de los robots, las clases base son clases de un tipo de robot la cual contiene lalogica y una forma sencilla de capturar los parametros del ambiente. Ademas, todas las clases dependen de una clase base **Robot**, esta clase contiene los controladores basicos para mover motores asi como un vector para almacenarlos, ademas, los motores son en este orden de indexacion: **index par -> motor de lado Izquierdo, index impar -> motor de lado Derecho**


## Robot
Esta clase maneja los motores, no hace nada mas que eso, es basico si, pero es lo que todo robot necesita. Todos los robots heredan de esta clase. Los metodos son:

| Metodo | Descripcion 
|-----------|-----------
|  ConfigVelocidad   | Este metodo toma una lista de motores y les da una velodidad inidcada
|  SetMotor   |   Este metodo inicializa un motor y le agrega velocidad en caso de que se pueda     |
| AddMotors | Este metodo toma una lista de motores y los guarda en la lista de la clase, despues inicializa los motores
| MStop | Detiene los motores
| MDelAtrs | Moeve una lista de motores hacia adelante o atras dependiendo de un boleano
| MDerIzq | Gira los motores sobre su propio eje hacia los lados, esto depende de un boleano para dar hacia donde girar
| Camina | No hace nada pero forzamos a que los herederos la usen para accionar su logica de movimiento, cada clase que herede de esta usara este metodo para poder moverse


## AutoRemotoBase

| Metodo | Descripcion
|--------|-----------
| Add4Motors | pide y agrega 4 motores a la lista de motores
| AutoRemotoBase | Pide una **velocidad** para los motores, pide el pin **receivePin** del modulo bluethoot para tomar datos, si el mocrocontrolador es un ESP32 NO usaras este pin, Pide el **transmitPin** del modulo bluethoot, al igual NO lo usaras si USAS ESP32, Pide **typeMotor**, esta es para poder saber que tipo de controlador de motor tienes, se explica mas en el README de depencencias. Ademas si necesitas usarlo y usas el ESP32 se ignoraran los datos del Recive y Transmite pin.


## RLBase (Resuelve Laberinto base)

| Metodo | Descripcion
|--------|-----------
| Add4Motors | pide y agrega 4 motores a la lista de motores
| RLBase | Pide la **velocidadRecta** que es la velocidad al andar, Pide la **velocidadGiro** que es la velocidad al girar, pide **timeGiro** que es el tiempo de giro antes de Accionar sus demas controles y logica, Pide el **timeRec** que es el tiempo para poder caminar antes de accionar sus demas sensores, Pide el **typeMotor** Para el tipo de controlador de motor.


## SumoBase

| Metodo | Descripcion
|--------|-----------
| Add2Motors | pide y agrega 2 motores a la lista de motores
| AddInfraAdelante | Pide el pin del Sensor infrarrojo delantero
| AddSUSAdelante | Pide los pines para el sensor ultrasonico delantero
| SumoBase | pide la **Velocidad** de recta, Pide la **VelocidadGiro**, Pide la **_DistAtaq**, que es la distancia maxima en centimetros para atacar, Pide el **TRecMiliSec** para poder caminar/atacar antes de accionar lo demas, Pide el **TGiroMiliSec** que es el tiempo de giro antes de accionar sus demas sensores, Pide el **typeMotor** para ver que tipo de controlador tiene