# ROBOTS

Librería open source en C++ creada por **Anther-X** para el entorno Arduino, diseñada para gestionar robots básicos de forma modular y reutilizable.

## Descripción

ROBOTS es una librería en C++ para proyectos de robótica básica embebida. Permite implementar el uso de robots de manera mucho más fácil, manteniendo compatibilidad con Arduino IDE y PlatformIO (Visual Studio Code).

La librería está pensada para ser modificable y extensible según las necesidades del proyecto.

## Arquitecturas soportadas

- AVR
- ESP32

## Instalación
Para mayor comodidad, la sección **Releases** contiene versiones listas para usar tanto para Arduino IDE como para Visual Studio Code + PlatformIO.

### Arduino IDE

Hay varias formas de incluir la librería en tu entorno de Arduino; veremos 2.

**Forma 1:**

1. Copia la carpeta de la librería dentro de:
   - **Windows:** `Documents/Arduino/libraries`
   - **macOS:** `~/Documents/Arduino/libraries/`
   - **Linux:** `~/Arduino/libraries/`
2. Abre o reinicia Arduino IDE.
3. Incluye la librería en el sketch:

```cpp
#include <Config.hpp>
#include <ROBOTS.hpp>
```

**Forma 2:**

1. Ya que tengas el archivo comprimido `.zip`, en Arduino IDE ve a:
   `Sketch -> Include Library -> Add .ZIP Library`
2. Selecciona el archivo comprimido e incluye la librería en el sketch:

```cpp
#include <Config.hpp>
#include <ROBOTS.hpp>
```

### Visual Studio Code + PlatformIO

En este caso, el proceso es fácil y prácticamente idéntico en cualquier sistema operativo.

1. Copia la carpeta dentro de tu proyecto en: `Project/lib/`
2. Incluye la librería en el sketch:

```cpp
#include <ROBOTS.hpp>
```

## Estructura del proyecto

La estructura de esta librería está organizada por clases. Las clases heredan de una clase base **Robot**, que se encarga de controlar solo los motores: velocidad, movimiento y agregación de motores.

Cada clase hija está en la carpeta **Robots-Base**; cada una hace algo básico y contiene la lógica de cómo funciona el robot según su tipo.

Las clases que heredan de estas están en **Robots-Simples**; lo único que hacen es cambiar la forma en que toman los valores o movimientos, o agregar/cambiar algunas cosas. Además, robots más complejos también pueden ir aquí.

## Ejemplo de uso

Para usar esta librería, primero debes incluirla; después, elige el tipo de robot, agrega en **Setup** lo que necesites, y en **Loop** solo usa el método **Camina**, al cual puedes pasarle el tiempo que debe estar encendido, en caso de tener más cosas además del robot.

No se explicará esto a fondo aquí, pero en la documentación está detallado el funcionamiento de cada clase y estructura, y cómo se usan.

```cpp
// Potencia para los motores.
uint8_t VelocidadRecta = 220;
uint8_t VelocidadGiro = 180;

// Distancia mínima para que comience a atacar
uint8_t DistanciaAtaque_CM = 20;

// Diámetro del Sumo en CM
uint16_t diametro = 7;

// Velocidad de recorrido maxima de recta en centrimetros por segundo (CM/S)
uint16_t Velocidad_CM_seg = 28;

// Tiempo en MS que durará su recorrido en recta si detecta solo al enemigo o nada más
unsigned int TRecorridoRectaMS = 620;

Sumo SB(VelocidadRecta, VelocidadGiro, DistanciaAtaque_CM, diametro, Velocidad_CM_seg, TRecorridoRectaMS, MotorDriverType::DRIVER_PWM_INTEGRATED);

void setup(){

    // Iniciamos seed aleatoria para los numeros
    RSeed;

    // Pines de los 2 motores
    Motor Mtrs[] = {{2, 3, 0}, {4, 5, 0}};
    // Agregamos sensores y motores
    SB.AddMotors(Mtrs, 2);

    // Infrarrojo atras (180 grados) y ultrasonico minimo para detectar al enemigo (0 grados)
    SB.AddSUS(0, 6, 7);
    SB.AddIR(180, 8);
}

void loop(){
    SB.Camina();
}
```

## Autor

**ANTHER-X**
GitHub: https://github.com/ANTHER-X  
Email: fernandocisneroslemus@gmail.com

## Licencia

Este proyecto está bajo la licencia MIT. Ver el archivo `LICENSE` para más detalles.