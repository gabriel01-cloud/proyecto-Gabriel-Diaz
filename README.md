# Zombie Match-3

Juego tipo Match-3 desarrollado en **C++** con **SFML 2.6.2**, como proyecto académico dividido en tres fases.

El objetivo es combinar gemas del mismo tipo para cumplir metas por nivel, desbloquear nuevos escenarios y obtener el mejor puntaje posible.  
En fases posteriores se implementará carga de niveles desde XML y sistema de ranking con progreso guardado.

---

## Objetivo del Proyecto

- Aplicar Programación Orientada a Objetos (POO) en C++  
- Implementar manejo de archivos y estructuras de datos  
- Desarrollar un sistema modular con distintas clases (`Gem`, `BoardLogic`, `Game`, etc.)  
- Consolidar las tres fases con control de versiones en GitHub  

---

## Instrucciones de Instalación

### Requisitos
- **Sistema operativo:** Windows 10 / 11  
- **Compilador:** MinGW o Visual Studio 2022  
- **Librería gráfica:** [SFML 2.6.2](https://www.sfml-dev.org/download.php)

### Compilación
1. Clona el repositorio:
   ```bash
   git clone https://github.com/gabriel01-cloud/proyecto-Gabriel-Diaz.git

Abre el proyecto en tu IDE o entorno (Code::Blocks o Visual Studio).

Asegúrate de vincular SFML correctamente:

sfml-graphics

sfml-window

sfml-system

Compila y ejecuta el programa.

# Controles del Juego

| Acción                          | Descripción                         |
| ------------------------------- | ----------------------------------- |
|  Click izquierdo                | Selecciona una gema                 |
|  Click izquierdo (segunda gema) | Intercambia dos gemas adyacentes    |

# Estructura Del Proyecto
 proyecto-Gabriel-Diaz
 ├──  main.cpp
 ├──  Game.h / Game.cpp
 ├──  BoardLogic.h / BoardLogic.cpp
 ├──  BoardRender.h / BoardRender.cpp
 ├──  Gem.h / Gem.cpp
 ├──  NormalGem.h
 ├──  BombGem.h
 ├──  IceGem.h
 ├──  Objective.h / Objective.cpp
 ├──  GameUI.h / GameUI.cpp
 ├──  LevelManager.h / LevelManager.cpp
 ├──  imagenes/   ← recursos gráficos (gemas, fondo, etc.)
 ├──  assets/     ← carpeta final del ejecutable
 ├──  README.md
 ├──  CHANGELOG.md

# Clases Principales

| Clase                            | Descripción                                                                 |
| -------------------------------- | --------------------------------------------------------------------------- |
| `Game`                           | Control principal del juego, ciclo de ejecución, niveles y UI               |
| `BoardLogic`                     | Lógica del tablero: detección de combinaciones, caída de gemas, promociones |
| `BoardRender`                    | Renderizado gráfico del tablero y las gemas                                 |
| `Gem`                            | Clase base para todos los tipos de gemas                                    |
| `NormalGem`, `BombGem`, `IceGem` | Subclases que representan comportamientos distintos                         |
| `Objective`                      | Define y controla los objetivos de cada nivel                               |
| `GameUI`                         | Muestra panel lateral, menús y botones interactivos                         |
| `LevelManager`                   | Configura niveles y metas (se reemplazará por XML en Fase 3)                |

# Flujo del Programa

Se muestra el menú inicial.
Se carga el nivel actual con sus objetivos.
El jugador realiza movimientos válidos → genera matches.
El tablero resuelve combinaciones y cae automáticamente.
Al completar los objetivos o agotar movimientos → pantalla de resultados.
Posibilidad de avanzar al siguiente nivel o volver al menu.

# Fases del Proyecto

| Fase       | Contenido                                             |
| ---------- | ----------------------------------------------------- |
| **Fase 1** | Motor base del juego, tablero y gemas normales        |
| **Fase 2** | Manejo de errores, mejora visual y menús interactivos |
| **Fase 3** | Sistema de guardado XML, ranking y progreso           |

## Diagrama de Clases

classDiagram
    direction LR

    class Game
    class BoardLogic
    class BoardRender
    class GameUI
    class Objective
    class LevelManager
    class LevelDef
    class Gem
    class NormalGem
    class BombGem
    class IceGem

    Gem <|-- NormalGem
    Gem <|-- BombGem
    Gem <|-- IceGem

    Game --> BoardLogic
    Game --> BoardRender
    Game --> GameUI
    Game --> Objective
    Game --> LevelManager

    BoardLogic --> Gem
    BoardRender --> BoardLogic
    GameUI --> Objective
    LevelManager --> LevelDef
