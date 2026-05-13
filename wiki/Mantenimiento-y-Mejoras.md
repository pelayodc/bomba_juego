# Mantenimiento y Mejoras

## Estado actual

El proyecto funciona como un sketch unico de Arduino con fases secuenciales. La logica esta concentrada en `bomba_juego/bomba_juego.ino` y la documentacion de jugador esta en `manual.docx`.

## Incidencias o detalles a revisar

- En `setup()` aparece `int fallos=0;`, que declara una variable local y no reinicia la global. La global ya empieza en `0`, asi que no rompe el primer arranque, pero puede confundir.
- `laberinto()` declara `int password[13]` con 12 valores y supera la fase con `pos == 12`. Conviene declarar el array con longitud 12 o calcular la longitud automaticamente.
- La variable `pull` en `laberinto()` no se usa.
- `perder()` contiene mucha repeticion manual de `digitalWrite()` y `delay()`. Se podria extraer a una funcion auxiliar de parpadeo.
- El codigo Wi-Fi y servidor web esta comentado. Conviene eliminarlo si no se va a usar o documentarlo como funcionalidad futura.
- `ganar()` se llama en cada iteracion de `loop()` despues de superar todas las fases, pero no bloquea el juego. Si se reinicia el `loop()`, el juego podria volver a empezar salvo que el flujo quede controlado por el estado fisico o por otra condicion externa.
- `ignoreFirst` en la fase de colores es global y no se reinicia dentro de `colores()`. Si se quisiera rejugar sin reiniciar placa, habria que restablecerlo.

## Mejoras recomendadas

- Separar constantes de hardware, claves y tiempos al inicio del archivo para facilitar ajustes.
- Crear una funcion comun para leer codigos de cuatro digitos y reutilizarla en `combinacionNumerica()` y `morse()`.
- Reemplazar secuencias largas de `delay()` por tablas de pasos para LEDs y buzzer.
- Anadir comentarios breves sobre el significado de cada fase y cada secuencia.
- Definir nombres simbolicos para movimientos del laberinto: `ARRIBA`, `IZQUIERDA`, `DERECHA`, `ABAJO`.
- Documentar el tipo exacto de placa usada y el esquema electrico real del montaje.
- Si se reactiva Wi-Fi, crear una pagina separada para configuracion de red y rutas HTTP.

## Pruebas manuales sugeridas

1. Cargar el sketch en la placa.
2. Abrir monitor serie a `115200`.
3. Verificar que el teclado registra todas las teclas.
4. Superar la combinacion `1435*`.
5. Superar el laberinto con `266848686266`.
6. Superar colores soltando en una ventana valida tras el checkpoint.
7. Superar Simon con la secuencia correspondiente al numero de fallos acumulados.
8. Superar Morse con `3532*`.
9. Forzar tres fallos y comprobar que se ejecuta `perder()`.

## Publicacion en GitHub Wiki

GitHub Wiki usa un repositorio Git separado. Para publicar estas paginas, se puede copiar el contenido de `wiki/` al repositorio de la wiki o sincronizarlo con herramientas externas. `Home.md` sera la portada de la wiki.
