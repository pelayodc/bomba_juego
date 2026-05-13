# Arquitectura del Codigo

## Archivo principal

Todo el juego esta implementado en:

```text
bomba_juego/bomba_juego.ino
```

El sketch usa una estructura secuencial. No hay clases propias ni modulos separados; las fases son funciones independientes llamadas desde `loop()`.

## Estados globales principales

| Variable | Tipo | Uso |
| --- | --- | --- |
| `fallos` | `int` | Numero de errores acumulados. Al llegar a 3 se pierde. |
| `jugando` | `bool` | Controla el bucle interno de cada fase. |
| `reiniciar` | `bool` | Reinicia rondas en Simon. |
| `pos` | `int` | Posicion actual en respuestas o secuencias. |
| `started` | `bool` | Indica si hay una tecla mantenida en la fase de colores. |
| `checkPoint` | `bool` | Marca si la fase de colores ya alcanzo el punto necesario. |
| `fase` | `int` | Paso actual en secuencias temporizadas de colores o Morse. |
| `timerMorse` | `long` | Referencia temporal para secuencias no bloqueantes. |

## Funciones de ciclo

### `setup()`

Inicializa el puerto serie, configura pines de salida y deja el sistema en estado inicial. Tambien conserva codigo Wi-Fi comentado para una posible version con punto de acceso y servidor web.

### `loop()`

Ejecuta todas las fases en orden. Como cada fase bloquea hasta terminar, el flujo es lineal.

## Funciones de fases

| Funcion | Responsabilidad |
| --- | --- |
| `combinacionNumerica()` | Lee la clave inicial de cuatro digitos. |
| `laberinto()` | Valida una ruta con teclas de direccion. |
| `colores()` | Controla la prueba de mantener y soltar en una ventana de color. |
| `simon()` | Ejecuta rondas de memoria con colores y teclas. |
| `morse()` | Muestra destellos y valida una clave de cuatro digitos. |

## Funciones auxiliares

| Funcion | Responsabilidad |
| --- | --- |
| `mostrarLuz()` | Avanza la secuencia RGB de la prueba de colores. |
| `checkPress()` | Detecta cambios de estado en teclas durante colores. |
| `checkValid()` | Decide si la liberacion de tecla supera o falla colores. |
| `mostrarSimon()` | Muestra la secuencia visual de Simon. |
| `comprobarSimon(char key)` | Valida cada tecla de Simon segun `pos` y `fallos`. |
| `mostrarMorse()` | Avanza la secuencia de destellos Morse. |
| `encenderLuz()` | Enciende el RGB en azul para Morse. |
| `apagarLuz()` | Apaga el RGB. |
| `fallar()` | Registra fallos, actualiza LEDs rojos y dispara derrota si corresponde. |
| `perder()` | Ejecuta la animacion de derrota y bloquea la placa. |
| `superado()` | Senaliza exito de fase y sale del bucle actual. |
| `ganar()` | Deja la bomba en estado final de victoria. |

## Gestion de entradas

Las fases numericas usan `keypad.getKey()`, que devuelve una tecla cuando se detecta una pulsacion. La fase de colores usa `keypad.getKeys()` para leer cambios de estado (`PRESSED` y `RELEASED`), porque necesita saber cuanto tiempo se mantiene pulsada una tecla.

## Comportamiento bloqueante

Varias funciones usan `while(jugando)` y `delay()`. Esto simplifica el flujo, pero impide ejecutar varias tareas a la vez. En la version actual es aceptable porque el juego es lineal.
