## Fase 1
### Primer avance
- Creación del tablero (`Board`).
- Creacion de las gemas en la clase (`Gem`).
- Interfaz principal de juego con pantalla de inicio y final (`Game`).
- Sistema básico de movimientos y detección de combinaciones.
- Generación aleatoria de gemas.

## Fase 2

### Implementación de clases especializadas de gemas:

NormalGem, BombGem, IceGem, todas heredando de Gem.
La bomba (BombGem) elimina gemas alrededor.
La gema de hielo (IceGem) requiere varios impactos para destruirse.

Sistema de objetivos (Objective):
Permite definir metas por tipo de gema.
Se actualiza con cada combinación (addProgress).
Determina cuándo el nivel está completado (isCompleted).

Manejo de niveles (LevelManager):
Crea niveles con distintas configuraciones: tamaño, movimientos, objetivos, porcentaje de hielo, etc.
advance() permite pasar de nivel cuando se completan los objetivos.
Interfaz de usuario (GameUI):
Panel lateral con objetivos y progreso.
Pantalla de inicio, resultado, final y botones de reinicio o avance.

Transición entre niveles:
Permite avanzar de nivel o reiniciar.
Gestiona las condiciones de victoria y derrota


