# ROBOTS

Librería open source en C++ creada por **Anther** para el entorno Arduino, diseñada para gestionar Robots basicos de forma modular y reutilizable.\
Esta libreria esta originalmente creada para ayudar a los alumnos de club de robotica de la instutucion escolar COBAEM, para el plantel Tarimbaro

## Descripción

ROBOTS es una librería escrita en C++ orientada a proyectos embebidos.
Permite implementar el uso de robots de manera facil y clara, manteniendo compatibilidad con Arduino IDE y PlatformIO (Visual Studio Code).

La librería está pensada para ser modificable y extensible según las
necesidades del proyecto.

## Arquitecturas soportadas

- AVR
- ESP32

## Instalación

### Arduino IDE

hay varias formas de incluir la libreria en tu entorno de arduino, vamos a ver 2.
- **Forma 1:**

1. Copiar la carpeta de la librería dentro de:
Si es **Windows:** `Documents/Arduino/libraries`\
Si es **MacOS:** `~/Documents/Arduino/libraries/`\
Si es **Linux:** `~/Arduino/libraries/`

2. Abre o reinicia Arduino IDE
3. Incluir la librería en el sketch:

```cpp
#include <ROBOTS.hpp>
```

- **Forma 2:**
1. Ya que tengas el archivo comprimido `.zip`, en Arduino IDE vas a:
`Sketch->Include Library->Add .ZIP Library`

2. Seleccionas el archivo comprimido e incluyes la libreria al sketch:
```cpp
#include <ROBOTS.hpp>
```

### Visual Studio Code + PlatformIO

En este caso el proceso es facil y practicamente identico en cualquier SO.

1. Copia la carpeta dentro de tu proyecto en: `Proyect/lib/`
2. Incluir la librería en el sketch:

```cpp
#include <ROBOTS.hpp>
```

## Licensia
Esta libreria esta bajo la licencia del MIT, consulta `LICENSE` para mas informacion