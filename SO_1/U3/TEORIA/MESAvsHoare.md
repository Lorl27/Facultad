La diferencia entre monitores de Hoare y monitores de Mesa tiene que ver con cómo
se *manejan las variables de condición* y qué hilo tiene el **control** tras una señalización
(**signal**). Ambos modelos son formas de implementar monitores, pero difieren en la
semántica de la señalización. Usaremas MESA, por threads.

# Monitor de Hoare:

* Transferencia inmediata del control al hilo que estaba esperando una
  condición.
* El hilo que hace signal() cede el control al hilo que estaba esperando en esa
  condición.
* Se asegura que la condición sigue siendo verdadera justo después de la
  señalización.

# Características de Hoare:

* Precisión en la sincronización: el hilo despertado actúa inmediatamente.
* Más complejo de implementar.
* Útil cuando es muy importante garantizar el estado del monitor al despertar.

# Monitor de Mesa:

* El hilo que hace signal() continúa ejecutándose.
* El hilo que fue despertado por signal() espera su turno para entrar al monitor
  (va a la cola de entrada).

# Características de Mesa:

* Más fácil de implementar con sistemas de planificación modernos.
* El hilo despertado debe volver a verificar la condición (por eso se usan bucles
  while en lugar de if).
* Puede haber un retraso entre signal() y la ejecución real del hilo despertado.



| MONITOR HOARE                                     | MONITOR MESA                                                           |
| :------------------------------------------------ | :--------------------------------------------------------------------- |
| Hilo A espera en una condición.                   | Hilo A espera en una condición.                                        |
| Hilo B hace signal().                             | Hilo B hace signal().                                                  |
| B se bloquea, y A toma el control inmediatamente. | B sigue ejecutándose.                                                  |
| Cuando A termina, B continúa.                     | A se despierta, pero espera hasta que B salga del monitor para entrar. |

