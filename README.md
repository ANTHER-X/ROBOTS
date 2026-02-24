# ROBOTS

Librería open source en C++ creada por **Anther** para el entorno Arduino, diseñada para gestionar Robots basicos de forma modular y reutilizable.\
Esta libreria esta originalmente creada para ayudar a los alumnos de club de robotica de la instutucion escolar COBAEM, para el plantel Tarimbaro

## Descripción

ROBOTS es una librería escrita en C++ orientada a proyectos embebidos.
Permite implementar el uso de robots de manera facil y clara, manteniendo compatibilidad con Arduino IDE y PlatformIO (Visual Studio Code).

La librería está pensada para ser modificable y extensible según las
necesidades del proyecto.

## Estado del Proyecto

⚠️ Librería en desarrollo.
Aún no ha sido probada en hardware real.

## Arquitecturas soportadas

- AVR
- ESP32

## Instalación

### Arduino IDE

hay varias formas de incluir la libreria en tu entorno de arduino, vamos a ver 2.
- **Forma 1:**

1. Copiar la carpeta de la librería dentro de:
Si es **Windows:** `Documents/Arduino/libraries`  
Si es **MacOS:** `~/Documents/Arduino/libraries/`  
Si es **Linux:** `~/Arduino/libraries/`

2. Abre o reinicia Arduino IDE
3. Incluir la librería en el sketch:

```cpp
#include <Config.hpp>
#include <ROBOTS.hpp>
```

- **Forma 2:**
1. Ya que tengas el archivo comprimido `.zip`, en Arduino IDE vas a:
`Sketch->Include Library->Add .ZIP Library`

2. Seleccionas el archivo comprimido e incluyes la libreria al sketch:
```cpp
#include <Config.hpp>
#include <ROBOTS.hpp>
```

### Visual Studio Code + PlatformIO

En este caso el proceso es facil y practicamente identico en cualquier SO.

1. Copia la carpeta dentro de tu proyecto en: `Proyect/lib/`
2. Incluir la librería en el sketch:

```cpp
#include <Config.hpp>
#include <ROBOTS.hpp>
```

Si por alguna razon no te deja compilar, lo mas sencillo es dejar la carpeta en `Proyect/src` e incluir la libreria

```cpp
#include <Config.hpp>
#include <ROBOTS/src/ROBOTS.hpp>
```

## Estructura del proyecto

La estructura de esta libreria esta por clases, las clases heredan de una clase base **Robot**, esta clase lo que hace es controlar solo los motores, da velocidad, movimiento, agregacion de motores.

Cada clase hija esta en la carpeta **Robots-Base**, cada clase hace una cosa de forma basica y tiene la logica de como funciona el robot dependiendo del tipo.

Las clases que heredan de estas estan en **Robots-Simples** lo unico que hacen es cambiar la forma en que toman los valores o movimientos, o agregan o cambian unas cosas. Ademas robots mas complejos tambien pueden ir aqui.


## Ejemplo Se Uso

Para usar esta libreria tienes que incluirla, despues tomar el tipo de robot, agregar en **Setup** lo que tengas que agregar y en **Loop** solo usar el metodo de **Camina**, metodo al cual le puedes pasar el tiempo que debe estar encendido, esto en caso de tener mas cosas ademas del robot.

Lamentablemente no explicare esto a fondo pero en los siguientes README explicare el funcionamiento de cada clase y estructura y como se usan

```cpp

//Una de las clases base
SumoBase SB1(200,240,15,30,35, DRIVER_PWM_INTEGRATED);

void setup() {

  //Creas motores
  Motor M1 = {3,2,0};
  Motor M2 = {5,4,0};

  //Agregas motores
  SB1.Add2Motors(M1,M2);
  
  //Agregas pines de Ultrasonico
  SB1.AddSUSAdelante(6,7);
}

void loop() {
  //Dejas que camine indefinidamente
  SB1.Camina();
}
```

## Autor
ANTHER-X  
GitHub: https://github.com/ANTHER-X  
email: fernandocisneroslemus@gmail.com

## Licencia
Este proyecto está bajo la licencia MIT. Ver el archivo LICENSE para más detalles.