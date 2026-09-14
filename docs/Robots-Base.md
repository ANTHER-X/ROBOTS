# Robots-Base

Esta carpeta contiene todo lo referente a las clases base de los robots. Las clases base son clases de un tipo de robot que contienen la lógica y una forma sencilla de capturar los parámetros del ambiente.

Además, todas las clases dependen de una clase base **Robot**, la cual contiene los controladores básicos para mover motores, así como un vector para almacenarlos. Los motores siguen este orden de indexación:

- **Índice par** → motor del lado izquierdo.
- **Índice impar** → motor del lado derecho.

## Robot

Esta clase maneja los motores; no hace nada más que eso. Es básica, sí, pero es lo que todo robot necesita. Todos los robots heredan de esta clase.

| Método | Descripción |
|--------|-------------|
| `ConfigVelocidad` | Toma una lista de motores y les asigna la velocidad indicada. |
| `SetMotor` | Inicializa un motor y le agrega velocidad, en caso de que se pueda. |
| `AddMotors` | Toma una lista de motores y los guarda en la lista de la clase; después inicializa los motores. |
| `MStop` | Detiene los motores. |
| `MDelAtrs` | Mueve una lista de motores hacia adelante o hacia atrás, dependiendo de un booleano. |
| `MDerIzq` | Gira los motores sobre su propio eje hacia los lados; depende de un booleano para indicar hacia dónde girar. |
| `Camina` | No hace nada por sí misma, pero se fuerza a que los herederos la implementen para ejecutar su lógica de movimiento. Cada clase que herede de esta usará este método para poder moverse. |

## AutoRemotoBase

| Método | Descripción |
|--------|-------------|
| `begin` | Inicializa el Bluetooth y permite cambiar el nombre y la contraseña del módulo. |
| `Add4Motors` | Pide y agrega 4 motores a la lista de motores. |
| `AutoRemotoBase` | Pide una **velocidad** para los motores. Pide el pin **receivePin** del módulo Bluetooth para recibir datos (si el microcontrolador es un ESP32, no se usará este pin). Pide el **transmitPin** del módulo Bluetooth (tampoco se usará si usas ESP32). Pide **typeMotor**, que indica el tipo de controlador de motor que tienes (se explica más a fondo en el README de Dependencias). Si usas ESP32, los datos de `receivePin` y `transmitPin` se ignoran. |
| `Camina` | El robot pide, opcionalmente, varios caracteres que actúan como "teclas" con las que puede moverse hacia los lados, detenerse, o aumentar/disminuir su velocidad. |

## RLBase (Resuelve Laberinto Base)

| Método | Descripción |
|--------|-------------|
| `Add4Motors` | Pide y agrega 4 motores a la lista de motores. |
| `RLBase` | Pide la **velocidadRecta**, que es la velocidad al andar. Pide la **velocidadGiro**, que es la velocidad al girar. Pide **timeGiro**, que es el tiempo de giro antes de accionar sus demás controles y lógica. Pide **timeRec**, que es el tiempo para caminar antes de accionar sus demás sensores. Pide **typeMotor**, para indicar el tipo de controlador de motor. |