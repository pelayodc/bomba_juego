# Juego Desactivar Bomba

Wiki tecnica del proyecto `bomba_juego`, un juego de desactivacion de bomba hecho con Arduino/ESP32, teclado matricial 4x4, LEDs y buzzer.

El juego propone una secuencia de pruebas que deben resolverse en orden. Cada error aumenta el contador de fallos; al llegar a tres fallos se ejecuta la secuencia de derrota. Al superar todas las pruebas, se activa la victoria.

## Contenido

- [Instalacion y Hardware](Instalacion-y-Hardware): requisitos, librerias, pines y cableado.
- [Funcionamiento del Juego](Funcionamiento-del-Juego): flujo de fases y comportamiento para jugadores.
- [Soluciones y Secuencias](Soluciones-y-Secuencias): codigos, rutas y respuestas internas del juego.
- [Arquitectura del Codigo](Arquitectura-del-Codigo): estructura del sketch, estados globales y funciones principales.
- [Manual del Jugador](Manual-del-Jugador): resumen del manual narrativo incluido en `manual.docx`.
- [Mantenimiento y Mejoras](Mantenimiento-y-Mejoras): incidencias conocidas y mejoras recomendadas.

## Archivos del proyecto

- `bomba_juego.ino`: sketch principal de Arduino.
- `manual.docx`: manual narrativo para los jugadores.
- `README.md`: descripcion breve del proyecto.

## Resumen del flujo

1. Combinacion numerica.
2. Laberinto.
3. Prueba de colores.
4. Simon.
5. Morse.
6. Victoria.

El codigo ejecuta estas fases de forma secuencial desde `loop()`. Cada fase bloquea la ejecucion hasta que se supera o hasta que se alcanza la derrota por fallos.
