# Robots-Simples

Esta carpeta contiene los robots simples, estas clases son solamente expanciones de las clases base, es decir que usan la misma logica, solo que agregan sensores, formas de tomar los datos o cambiar un poco la logica u otro tipo de complemento o cambio a las clases base o tipo de robot.
Si el tipo de robot es complicado o no muy extenso puede ir aqui

Las clases son hijas de las clase base asi que si no ves gran cambio es por eso pero internamente cambian las cosas, cabe decir que en el codigo esta explicado todo lo que se hace.


## AutRem-SSS (Auto Remoto Servo steering system)

| Metodo | Descripcion
|--------|-----------
| AutRemSSS | Pide **pinServo**, es... El pin para el servo motor, pide la **velocidad**, pide el **receivePin** para el bluethoot, cabe decir que si usas ESP32 NO usaras esto, pide el **transmitPin**, si uesas el ESP32 NO daras pin, pide el **typeMotor** para ver que controlador de motores tienes, si usas ESP32, los pines de transmit y recive seran ignorados.



## RLB-Servo (Resuelve laberinto con Servo motor)

| Metodo | Descripcion
|--------|-----------
| RLBServo | Pide la **velocidadRecta**, Pide la **velocidadGiro**, pide el **timeGiro** que es el tiempo maximo para girar antes de accionar sus otros controles en caso de no pasar nada, Pide el **timeRec** que es el tiempo maximo para recorrer la recta antes de accionar sus otros controles en caso de no pasar nada, Pide **us**, es decir, la estructura **UltraSonico** para manejar el sensor ultrasonico, pide el **pinServo**, finalmente pide **typeMotor** para el tipo de controlador de motores.



## RLB-US (Resuelve laberinto con sensores ultrasonicos)

| Metodo | Descripcion
|--------|-----------
| RLBUS | Pide la **velocidadRecta**, es la velocidad de los motores el andar, pide **velocidadGiro**, que es la velocidad al girar, pide el **timeGiro** que es el tiempo maximo de giro antes de accionar sus controles en caso de que no pase nada, pide el **timeRec** que es el tiempo de recorrido antes de hacer otra cosa en caso de que no pase nada, nos pide 3 sensores tipo **UltraSonico** que son **_USDelante**, **_USDerecha** y **_USIzquierda**, finalmente nos pide **typeMotor**, que es para el tipo de controlador de motores usado.



## SumoSimple
el IR y el SUS no estan ya que ya estan explicados en el sumo base y este solo los hereda

| Metodo | Descripcion
|--------|-----------
| SumoSimple | pide la **Velocidad** de recta, Pide la **VelocidadGiro**, Pide la **_DistAtaq**, que es la distancia maxima en centimetros para atacar, Pide el **TRecMiliSec** para poder caminar/atacar antes de accionar lo demas, Pide el **TGiroMiliSec** que es el tiempo de giro antes de accionar sus demas sensores, Pide el **typeMotor** para ver que tipo de controlador tiene
| AddInfraAtras | Agrega el Sensor IR de la parte trasera
| AddInfraIzquierda | Agrega el Sensor IR de la parte izquierda
| AddInfraDerecha | Agrega el Sensor IR de la parte derecha
| AddSUSAtras |  Agrega el Sensor Ultrasonico de la parte trasera, pide solo los pines
| AddSUSIzquierda | Agrega el Sensor Ultrasonico de la parte izquierda, pide solo los pines
| AddSUSDerecha | Agrega el Sensor Ultrasonico de la parte derecha, pide solo los pines
| Add4Motors | pide, Agrega e inicializa 4 motores que das



## SeguidorLinea

| Metodo | Descripcion
|--------|-----------
| SeguidorLinea | pide la **velocidadMedia**, asi como opcionalmente la **velocidadMaxima** y el  **motorDriverType** que es el tipo de controlador de motores
| AddIRs | Este metodo pide un ARRAY de pines de los sensores IR, asi como the size exacto de este array. La lista es para detectar y la forma es una linea recta que comienza de izquierda con index 0 hacia la derecha.
| AddIRColicion | De forma opcional agregas el pin del sensor para detectar una colicion, el detectro es digital y se piensa usar con sensores IR
| AddBuzzerPin | De forma opcional agregas el pin de tu buzzer digital, puede ser ya sea pasivo o activo
| AddNotas | De forma opcional agregas un array de tipo **SoundBuzzer** para poder meter la melodia que quieras que suene al momento de colicionar, si necesitas mas notas modifica **MAXNOTAS** en configuracion